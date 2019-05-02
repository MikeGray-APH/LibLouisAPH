/*

   Copyright 2017 American Printing House for the Blind Inc.

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.

*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "utf-convert.h"
#include "translate.h"
#include "lookup.h"
#include "log.h"


#ifndef BUFFER_MAX
#define BUFFER_MAX  0x1000
#endif

//#define PREALLOCATE

static enum rule_direction direction;
static int opt_echo_no_processed, opt_output_mapped;

/******************************************************************************/

static int string_strip_newlines(char *cchars)
{
	int cchars_len;

	cchars_len = strlen(cchars);
	while(cchars_len > 0)
	{
		if(cchars[cchars_len - 1] == '\n' || cchars[cchars_len - 1] == '\r')
			cchars[cchars_len - 1] = 0;
		else
			break;
		cchars_len--;
	}

	return cchars_len;
}

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
		"   -m         output mappings",
		"   -M         output mappings as list",
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
		"Licensed under the Apache License, Version 2.0 <http://www.apache.org/licenses/LICENSE-2.0>.",
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
	   && (!strncmp(args[1], "-h", 3) || !strncmp(args[1], "--help", 7))))
	{
		print_usage();
		exit(0);
	}

	if(   argn == 1
	   || (args[1][0] == '-'
	   && (!strncmp(args[1], "-v", 3) || !strncmp(args[1], "--version", 10))))
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

	case 'm':  opt_output_mapped = 1;  break;
	case 'M':  opt_output_mapped = 2;  break;

	/*   read long arguments   */
	case '-':

		if((*args)[2] == 0)
			return ++args;
		else if(!strncmp(&((*args)[2]), "back-translation", 17))
			direction = BACKWARD;
		else if(!strncmp(&((*args)[2]), "paths", 6))
			goto add_paths;
		else if(!strncmp(&((*args)[2]), "output-mappings-as-list", 24))
			opt_output_mapped = 2;
		else if(!strncmp(&((*args)[2]), "output-mappings", 16))
			opt_output_mapped = 1;
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
	char *cinput, *coutput, cchar[15];
	unichar *uinput, *uoutput;
	int cinput_len, cinput_max, cinput_crs;
	int coutput_len, coutput_max;
	int uinput_len, uinput_max;
	int uoutput_len, uoutput_max, uoutput_crs;
	int *chars_to_cells, *cells_to_chars;
	int tens, ten;

	direction = FORWARD;
	opt_output_mapped =
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

	cinput_max = BUFFER_MAX;
	cinput = malloc(cinput_max);
	memset(cinput, 0, cinput_max);

	coutput_max = BUFFER_MAX;
	coutput = malloc(coutput_max);
	memset(coutput, 0, coutput_max);

	uinput_max = BUFFER_MAX;
	uinput = malloc(uinput_max * sizeof(unichar));
	memset(uinput, 0, uinput_max);

	uoutput_max = BUFFER_MAX;
	//uoutput_len = 0;
	uoutput = malloc(uoutput_max * sizeof(unichar));
	memset(uoutput, 0, uoutput_max);

	chars_to_cells =
	cells_to_chars = NULL;

	while(fgets(cinput, cinput_max, stdin))
	{
		/*   check if entire line was read   */
		cinput_len = string_strip_newlines(cinput);
		if(cinput_len >= cinput_max - 1)
		{
			cinput_max += BUFFER_MAX;
			cinput = realloc(cinput, cinput_max);
			if(!cinput)
			{
				fprintf(stderr, "FATAL:  out of memory\n");
				return 1;
			}
			ASSERT(cinput[cinput_len] == 0)

			while(fgets(&cinput[cinput_len], cinput_max - cinput_len, stdin))
			{
				cinput_len = string_strip_newlines(cinput);
				if(cinput_len < cinput_max - 1)
					break;

				cinput_max += BUFFER_MAX;
				cinput = realloc(cinput, cinput_max);
				if(!cinput)
				{
					fprintf(stderr, "FATAL:  out of memory\n");
					return 1;
				}
				ASSERT(cinput[cinput_len] == 0)
			}
		}

		/*   empty string   */
		if(cinput_len == 0)
		{
			puts("");
			continue;
		}

#ifdef PREALLOCATE
		if(uinput_max < cinput_max)
		{
			uinput_max = cinput_max;
			uinput = realloc(uinput, uinput_max * sizeof(unichar));
			if(!uinput)
			{
				fprintf(stderr, "FATAL:  out of memory\n");
				return 1;
			}
		}
#endif

		uinput_len = utf8_convert_to_utf16(uinput, uinput_max, cinput, cinput_len, &cinput_crs);
		if(cinput_len > cinput_crs)
		{
			uinput_max = uinput_len + 1;
			uinput = realloc(uinput, uinput_max * sizeof(unichar));
			if(!uinput)
			{
				fprintf(stderr, "FATAL:  out of memory\n");
				return 1;
			}
			uinput_len = utf8_convert_to_utf16(uinput, uinput_max, cinput, cinput_len, &cinput_crs);
			ASSERT(cinput_crs == cinput_len)
		}

		if(opt_output_mapped)
		{
			chars_to_cells = malloc(uinput_len * sizeof(int));
			cells_to_chars = malloc(uoutput_max * sizeof(int));
		}

#ifdef PREALLOCATE
		if(uoutput_max < uinput_max)
		{
			uoutput_max = uinput_max;
			uoutput = realloc(uoutput, uoutput_max * sizeof(unichar));
			if(!uoutput)
			{
				fprintf(stderr, "FATAL:  out of memory\n");
				return 1;
			}
			if(opt_output_mapped)
			{
				cells_to_chars = realloc(cells_to_chars, uoutput_max * sizeof(int));
				if(!cells_to_chars)
				{
					fprintf(stderr, "FATAL:  out of memory\n");
					return 1;
				}
			}
		}
#endif

		uoutput_len = translate_start(
			uoutput, uoutput_max, uinput, uinput_len,
			(const struct table * const*)tables, table_cnt, conversion, direction,
			chars_to_cells, cells_to_chars, NULL);
		if(uoutput_len <= 0)
		{
			if(opt_echo_no_processed)
				printf("%s\n", cinput);
			else
				puts("");
			continue;
		}
		if(uoutput_len >= uoutput_max)
		{
			uoutput_max = uoutput_len + 1;
			uoutput = realloc(uoutput, uoutput_max * sizeof(unichar));
			if(!uoutput)
			{
				fprintf(stderr, "FATAL:  out of memory\n");
				return 1;
			}
			if(opt_output_mapped)
			{
				cells_to_chars = realloc(cells_to_chars, uoutput_max * sizeof(int));
				if(!cells_to_chars)
				{
					fprintf(stderr, "FATAL:  out of memory\n");
					return 1;
				}
			}
			uoutput_len = translate_start(
				uoutput, uoutput_max, uinput, uinput_len,
				(const struct table * const*)tables, table_cnt, conversion, direction,
				chars_to_cells, cells_to_chars, NULL);
		}

#ifdef PREALLOCATE
		if(coutput_max < uoutput_max)
		{
			coutput_max = uoutput_max;
			coutput = realloc(coutput, coutput_max);
			if(!coutput)
			{
				fprintf(stderr, "FATAL:  out of memory\n");
				return 1;
			}
		}
#endif

		coutput_len = utf16_convert_to_utf8(coutput, coutput_max, uoutput, uoutput_len, &uoutput_crs);
		if(uoutput_len > uoutput_crs)
		{
			coutput_max = coutput_len + 1;
			coutput = realloc(coutput, coutput_max);
			if(!coutput)
			{
				fprintf(stderr, "FATAL:  out of memory\n");
				return 1;
			}
			coutput_len = utf16_convert_to_utf8(coutput, coutput_max, uoutput, uoutput_len, &uoutput_crs);
			ASSERT(uoutput_crs == uoutput_len)
		}

		if(opt_output_mapped)
		{
			if(opt_output_mapped == 1)
			{
				tens = -1;
				for(int i = 0; i < uinput_len; i++)
				{
					ten = (i / 10) % 10;
					if(tens == ten)
						printf(" ");
					else
					{
						printf("%d", ten);
						tens = ten;
					}
				}
				puts("");
				for(int i = 0; i < uinput_len; i++)
					printf("%d", i % 10);
				puts("");

				printf("%s\n", cinput);

				tens = -1;
				for(int i = 0; i < uinput_len; i++)
				if(chars_to_cells[i] < 0)
					printf(" ");
				else
				{
					ten = (chars_to_cells[i] / 10) % 10;
					if(tens == ten)
						printf(" ");
					else
					{
						printf("%d", ten);
						tens = ten;
					}
				}
				puts("");

				for(int i = 0; i < uinput_len; i++)
				if(chars_to_cells[i] < 0)
					printf("-");
				else
					printf("%d", chars_to_cells[i] % 10);
				puts("");

				puts("");

				tens = -1;
				for(int i = 0; i < uoutput_len; i++)
				{
					ten = (i / 10) % 10;
					if(tens == ten)
						printf(" ");
					else
					{
						printf("%d", ten);
						tens = ten;
					}
				}
				puts("");
				for(int i = 0; i < uoutput_len; i++)
					printf("%d", i % 10);
				puts("");

				printf("%s\n", coutput);

				tens = -1;
				for(int i = 0; i < uoutput_len; i++)
				if(cells_to_chars[i] < 0)
					printf(" ");
				else
				{
					ten = (cells_to_chars[i] / 10) % 10;
					if(tens == ten)
						printf(" ");
					else
					{
						printf("%d", ten);
						tens = ten;
					}
				}
				puts("");
				for(int i = 0; i < uoutput_len; i++)
				if(cells_to_chars[i] < 0)
					printf("-");
				else
					printf("%d", cells_to_chars[i] % 10);
				puts("");

				puts("");
			}
			else if(opt_output_mapped == 2)
			{
				for(int i = 0; i < uinput_len; i++)
				{
					memset(cchar, 0, 15);
					utf16_convert_to_utf8(cchar, 15, &uinput[i], 1, NULL);
					printf("[%d]\t%s\t%d\n", i, cchar, chars_to_cells[i]);
				}
				puts("");
				for(int i = 0; i < uoutput_len; i++)
				{
					memset(cchar, 0, 15);
					utf16_convert_to_utf8(cchar, 15, &uoutput[i], 1, NULL);
					printf("[%d]\t%s\t%d\n", i, cchar, cells_to_chars[i]);
				}
				puts("");
			}

			free(chars_to_cells);
			free(cells_to_chars);

			chars_to_cells =
			cells_to_chars = NULL;
		}
		else
			printf("%s\n", coutput);

	}

	free(tables);
	free(cinput);
	free(uinput);
	free(coutput);
	free(uoutput);
	lookup_fini();

	return 0;
}

/******************************************************************************/
