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
#include "conversion.h"
#include "utf-output.h"
#include "conversion-output.h"
#include "lookup.h"
#include "log.h"

#define FORWARD   (+1)
#define BACKWARD  (-1)
#define INPUT_BUFFER_MAX   0x2520

static int opt_direction, opt_unicode_to_digits, opt_digits_to_unicode, opt_output;

/******************************************************************************/

/* Unicode braille is allowed, and does not need to be separated with dashes.
 * Examples:
 *    ⠒⠭⠒        =  25-1346-25
 *    ⠒-⠭-⠒      =  25-1346-25
 *    123-⠭-456  =  123-1346-456
 *    123⠭456    =  123-1346-456
 *
 * If 0 is by itself, it becomes \u2800.  If 0 is not by itself, ie -0-, then
 * it acts like it just resets the cell to 0 and any valid digits afterward
 * are converted, and the digits before were not converted.
 * Examples:
 *    1-02-3          =  1-2-3
 *    1-20-3          =  1-0-3
 *    1-1234567802-3  =  1-2-3
 *
 * Invalid characters just stops processing, the converted cells are still
 * outputed.  This is different from how digits are converted when compiling.
 * Examples:
 *    1-2-!3  =  1-2
 *    1-2-!   =  1-2
 *    1-2!-3  =  1-2
 *    1-!2-3  =  1
*/
static void convert_digits_to_unicode(const char *dots)
{
	Unicode *uchars;
	char *cchars;
	int dots_len, cchars_len, uchars_len;
	Unicode cell;
	int crs, off;

	dots_len = strlen(dots);
	uchars_len = dots_len;
	cchars_len = uchars_len * 11;
	uchars = malloc((uchars_len + 1) * sizeof(Unicode));
	cchars = malloc(cchars_len + 1);
	utf8_convert_to_utf16le(uchars, (uchars_len + 1), dots, dots_len);

	cell = 0;
	crs = 0;
	for(off = 0; off < uchars_len; off++)
	{
		if(uchars[off] >= 0x2800 && uchars[off] <= 0x28ff)
		{
			if(cell)
			{
				uchars[crs++] = cell | 0x2800;
				cell = 0;
			}
			uchars[crs++] = uchars[off];
		}
		else if(uchars[off] == u'0')
			cell = 0x2800;
		else if(uchars[off] >= u'1' && uchars[off] <= u'8')
			cell |= (Unicode)BIT(uchars[off] - u'1');
		else if(uchars[off] == u'-')
		{
			if(cell)
			{
				uchars[crs++] = cell | 0x2800;
				cell = 0;
			}
		}
		else
			break;
	}

	if(cell)
	{
		uchars[crs++] = cell | 0x2800;
		cell = 0;
	}
	uchars[crs] = 0;
	utf16le_convert_to_utf8(cchars, (cchars_len + 1), uchars, crs);
	printf("%s\n", cchars);
	free(uchars);
	free(cchars);
}

static void convert_unicode_to_digits(const char *dots)
{
	Unicode *uchars;
	char *cchars;
	int dots_len, cchars_len, uchars_len, crs, off;

	dots_len = strlen(dots);
	uchars_len = dots_len;
	cchars_len = uchars_len * 11;
	uchars = malloc((uchars_len + 1) * sizeof(Unicode));
	cchars = malloc(cchars_len + 1);
	utf8_convert_to_utf16le(uchars, (uchars_len + 1), dots, dots_len);

	crs = 0;
	for(off = 0; off < uchars_len; off++)
	{
		if(uchars[off] == 0)
			break;
		if(!(uchars[off] >= 0x2800 && uchars[off] <= 0x28ff))
			break;
		if(!(uchars[off] & 0xff))
			cchars[crs++] = '0';
		if(uchars[off] & BIT(0))
			cchars[crs++] = '1';
		if(uchars[off] & BIT(1))
			cchars[crs++] = '2';
		if(uchars[off] & BIT(2))
			cchars[crs++] = '3';
		if(uchars[off] & BIT(3))
			cchars[crs++] = '4';
		if(uchars[off] & BIT(4))
			cchars[crs++] = '5';
		if(uchars[off] & BIT(5))
			cchars[crs++] = '6';
		if(uchars[off] & BIT(6))
			cchars[crs++] = '7';
		if(uchars[off] & BIT(7))
			cchars[crs++] = '8';

		if(off + 1 < uchars_len)
		if(uchars[off + 1])
			cchars[crs++] = '-';
	}

	cchars[crs] = 0;
	printf("%s\n", cchars);
	free(uchars);
	free(cchars);
}

/******************************************************************************/

static void log_callback(const int level, const char *message)
{
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
		"Usage: lou_convert [-b] CONVERSION_FILE",
		"Usage: lou_convert  -d [CELLS]",
		"Usage: lou_convert  -u [DOTS]",
		"Usage: lou_convert  -o  CONVERSION_FILE",
		"Options:",
		"   -b         do back conversion",
		"   -d         convert unicode to digits",
		"   -u         convert digits to unicode",
		"   -o         output conversion",
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
		"lou_convert (LibLouisAPH) " VERSION,
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
	opt_direction = FORWARD;
	opt_unicode_to_digits =
	opt_digits_to_unicode = 0;
	opt_output = 0;

	if(   argn == 1
	   || (args[1][0] == '-'
	   && (!strncmp(args[1], "-h", 2) || !strncmp(args[1], "--help", 6))))
	{
		print_usage();
		return NULL;
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
	case 'b':  opt_direction = BACKWARD;   break;
	case 'd':  opt_unicode_to_digits = 1;  break;
	case 'u':  opt_digits_to_unicode = 1;  break;
	case 'o':  opt_output = 1;             break;

	case 'p':  add_paths:

		args++;
		lookup_add_paths(*args);
		break;

	/*   read long arguments   */
	case '-':

		if((*args)[2] == 0)
			return ++args;
		else if(!strncmp(&((*args)[2]), "back-conversion", 15))
			opt_direction = BACKWARD;
		else if(!strncmp(&((*args)[2]), "unicode-to-digits", 17))
			opt_unicode_to_digits = 1;
		else if(!strncmp(&((*args)[2]), "digits-to-unicode", 17))
			opt_digits_to_unicode = 1;
		else if(!strncmp(&((*args)[2]), "output", 7))
			opt_output = 1;
		else if(!strncmp(&((*args)[2]), "paths", 6))
			goto add_paths;
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
	struct conversion *conversion;
	char cchars[INPUT_BUFFER_MAX];
	Unicode uchars[INPUT_BUFFER_MAX];
	int cchars_len, uchars_len;

	args = scan_arguments(args, argn);
	if(!args)
		return 1;

	log_set_callback(log_callback);


	if(opt_unicode_to_digits)
	{
		if(*args)
		while(*args)
		{
			convert_unicode_to_digits(*args);
			args++;
		}
		else
		{
			memset(cchars, 0, INPUT_BUFFER_MAX);
			while(fgets(cchars, INPUT_BUFFER_MAX, stdin))
				convert_unicode_to_digits(cchars);
		}

		return 0;
	}

	if(opt_digits_to_unicode)
	{
		if(*args)
		while(*args)
		{
			convert_digits_to_unicode(*args);
			args++;
		}
		else
		{
			memset(cchars, 0, INPUT_BUFFER_MAX);
			while(fgets(cchars, INPUT_BUFFER_MAX, stdin))
				convert_digits_to_unicode(cchars);
		}

		return 0;
	}

	if(!args[0])
	{
		print_usage();
		return 1;
	}

	 conversion = lookup_conversion(*args);
	 if(!conversion)
	{
		fprintf(stderr, "ERROR:  unable to load conversion %s\n", *args);
		return 1;
	}

	if(opt_output)
	{
		conversion_output(stdout, conversion);
		return 0;
	}

	memset(cchars, 0, INPUT_BUFFER_MAX);
	memset(uchars, 0, INPUT_BUFFER_MAX * sizeof(Unicode));
	while(fgets(cchars, INPUT_BUFFER_MAX, stdin))
	{
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

		uchars_len = utf8_convert_to_utf16le(uchars, INPUT_BUFFER_MAX, cchars, cchars_len);
		if(opt_direction == FORWARD)
			conversion_convert_to(uchars, uchars_len, conversion);
		else if(opt_direction == BACKWARD)
			conversion_convert_from(uchars, uchars_len, conversion);
		utf16le_convert_to_utf8(cchars, INPUT_BUFFER_MAX, uchars, uchars_len);
		printf("%s\n", cchars);
	}

	conversion_free(conversion);

	return 0;
}

/******************************************************************************/
