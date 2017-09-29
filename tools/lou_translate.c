/*

LibLouisAPH Braille Translation and Back-Translation Library

Copyright (C) 2017 American Printing House for the Blind, Inc.

This file is part of LibLouisAPH.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "utf-convert.h"
#include "translate.h"
#include "lookup.h"
#include "log.h"

#define INPUT_BUFFER_MAX  0x1000

static enum rule_direction direction;
static int opt_echo_no_processed;

/******************************************************************************/

static void log_callback(const int level, const char *message)
{
	if(opt_echo_no_processed)
	if(level == LOG_WARNING)
	if(!strncmp(message, "no processing done", 19))
		return;

	switch(level)
	{
	case LOG_ALL:      fprintf(stderr, "ALL:  ");      break;
	case LOG_TRACE:    fprintf(stderr, "TRACE:  ");    break;
	case LOG_DEBUG:    fprintf(stderr, "DEBUG:  ");    break;
	case LOG_INFO:     fprintf(stderr, "INFO:  ");     break;
	case LOG_WARNING:  fprintf(stderr, "WARNING:  ");  break;
	case LOG_ERROR:    fprintf(stderr, "ERROR:  ");    break;
	case LOG_FATAL:    fprintf(stderr, "FATAL:  ");    break;
	}

	fprintf(stderr, "%s\n", message);
	fflush(stderr);
}

static void print_usage(void)
{
	const char *txt[] =
	{
		"Usage: lou_translate [-b] TABLE_FILE_LIST [CONVERSION_FILE]",
		"Options:",
		"   -b         do back translation",
		"   -p PATHS   add PATHS to table paths",
		"   -v         print version",
		"   -h         print this message",
		NULL
	};
	int i;

	for(i = 0; txt[i]; i++)
		puts(txt[i]);
}

static void print_version(void)
{
	const char *txt[] =
	{
		"lou_translate (LibLouisAPH) " VERSION,
		"Copyright (C) 2017 American Printing House for the Blind, Inc. <www.aph.org>",
		"License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>.",
		"This is free software: you are free to change and redistribute it.",
		"There is NO WARRANTY, to the extent permitted by law.",
		NULL
	};
	int i;

	for(i = 0; txt[i]; i++)
		puts(txt[i]);
}

static char** scan_arguments(char **args, const int argn)
{
	if(   argn == 1
	   || (args[1][0] == '-'
	   && (!strncmp(args[1], "-h", 2) || !strncmp(args[1], "--help", 6))))
	{
		print_usage();
		exit(0);
	}

	if(   argn == 1
	   || (args[1][0] == '-'
	   && (!strncmp(args[1], "-v", 2) || !strncmp(args[1], "--version", 9))))
	{
		print_version();
		exit(0);
	}

	for(args++; *args && **args == '-'; args++)
	switch((*args)[1])
	{
	case 'b':  direction = BACKWARD;  break;

	case 'p':  add_paths:

		args++;
		lookup_add_paths(*args);
		break;

	/*   read long arguments   */
	case '-':

		if((*args)[2] == 0)
			return ++args;
		else if(!strncmp(&((*args)[2]), "back-translation", 16))
			direction = BACKWARD;
		else if(!strncmp(&((*args)[2]), "paths", 6))
			goto add_paths;
		else if(!strncmp(&((*args)[2]), "echo-no-processed", 18))
			opt_echo_no_processed = 1;
		else
			goto on_error;
		break;

	default:  on_error:

		fprintf(stderr, "unknown option %s", *args);
		return NULL;
	}

	return args;
}

int main(int argn, char **args)
{
	struct table **tables;
	int table_cnt;
	struct conversion *conversion;
	char *cchars;
	Unicode *uchars, *trans;
	int cchars_len, uchars_len, trans_len, max_len;

	direction = FORWARD;
	opt_echo_no_processed = 0;

	args = scan_arguments(args, argn);
	if(!args)
		return 1;
	if(!args[0])
	{
		print_usage();
		return 1;
	}

	log_set_callback(log_callback);

	tables = lookup_tables(&table_cnt, args[0]);
	if(!tables)
		return 1;

	if(args[1])
	{
		conversion = lookup_conversion(args[1]);
		 if(!conversion)
			return 1;
	}
	else
		conversion = NULL;

	max_len = INPUT_BUFFER_MAX;
	cchars = malloc(max_len);
	uchars = malloc(max_len * sizeof(Unicode));
	trans  = malloc(max_len * sizeof(Unicode));
	memset(cchars, 0, max_len);
	memset(uchars, 0, max_len * sizeof(Unicode));
	memset(trans, 0, max_len * sizeof(Unicode));

	while(fgets(cchars, INPUT_BUFFER_MAX, stdin))
	{
		/*   check if entire line was read   */
		cchars_len = strlen(cchars);
		if(cchars[cchars_len - 1] != '\n' && cchars[cchars_len - 1] != '\r')
		{
			max_len += INPUT_BUFFER_MAX;
			cchars = realloc(cchars, max_len);
			if(!cchars)
			{
				fprintf(stderr, "FATAL:  out of memory\n");
				return 1;
			}

			while(fgets(&cchars[cchars_len], INPUT_BUFFER_MAX, stdin))
			{
				cchars_len = strlen(cchars);
				if(cchars[cchars_len - 1] == '\n' || cchars[cchars_len - 1] == '\r')
					break;

				max_len += INPUT_BUFFER_MAX;
				cchars = realloc(cchars, max_len);
				if(!cchars)
				{
					fprintf(stderr, "FATAL:  out of memory\n");
					return 1;
				}
			}

			uchars = realloc(uchars, max_len * sizeof(Unicode));
			if(!uchars)
			{
				fprintf(stderr, "FATAL:  out of memory\n");
				return 1;
			}

			trans = realloc(trans,  max_len * sizeof(Unicode));
			if(!trans)
			{
				fprintf(stderr, "FATAL:  out of memory\n");
				return 1;
			}
		}

		/*   trim return whitespace at end   */
		for(cchars_len = strlen(cchars); cchars_len > 0; cchars_len--)
		if(cchars[cchars_len - 1] == '\n' || cchars[cchars_len - 1] == '\r')
			cchars[cchars_len - 1] = 0;
		else
			break;
		if(cchars_len < 0)
		{
			puts("");
			continue;
		}

		uchars_len = utf8_convert_to_utf16le(uchars, max_len, cchars, cchars_len);
		trans_len = translate_start(
			trans, max_len, uchars, uchars_len,
			(const struct table * const*)tables, table_cnt, conversion, direction,
			NULL, NULL, NULL);
		if(trans_len <= 0)
		{
			if(opt_echo_no_processed)
				printf("%s\n", cchars);
			else
				puts("");
			continue;
		}

		/*   check that there should be enough room
		     for UTF conversion   */
		if(trans_len * 3 >= max_len)
		{
			max_len = trans_len * 3 + 1;

			cchars = realloc(cchars, max_len);
			if(!cchars)
			{
				fprintf(stderr, "FATAL:  out of memory\n");
				return 1;
			}

			uchars = realloc(uchars, max_len * sizeof(Unicode));
			if(!uchars)
			{
				fprintf(stderr, "FATAL:  out of memory\n");
				return 1;
			}

			trans = realloc(trans,  max_len * sizeof(Unicode));
			if(!trans)
			{
				fprintf(stderr, "FATAL:  out of memory\n");
				return 1;
			}
		}

		utf16le_convert_to_utf8(cchars, max_len, trans, trans_len);
		printf("%s\n", cchars);
	}

	free(tables);
	free(cchars);
	free(uchars);
	free(trans);
	lookup_fini();

	return 0;
}

/******************************************************************************/
