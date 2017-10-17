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
#include "conversion.h"
#include "utf-output.h"
#include "conversion-output.h"
#include "lookup.h"
#include "log.h"

#define FORWARD   (+1)
#define BACKWARD  (-1)
#define INPUT_BUFFER_MAX   0x1000

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
		"Licensed under the Apache License, Version 2.0 <http://www.apache.org/licenses/LICENSE-2.0>.",
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
	   && (!strncmp(args[1], "-h", 3) || !strncmp(args[1], "--help", 7))))
	{
		print_usage();
		return NULL;
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
		else if(!strncmp(&((*args)[2]), "back-conversion", 16))
			opt_direction = BACKWARD;
		else if(!strncmp(&((*args)[2]), "unicode-to-digits", 18))
			opt_unicode_to_digits = 1;
		else if(!strncmp(&((*args)[2]), "digits-to-unicode", 18))
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
	char *cchars;
	Unicode *uchars;
	int cchars_len, uchars_len, max_len;

	args = scan_arguments(args, argn);
	if(!args)
		return 1;

	log_set_callback(log_callback);

	max_len = INPUT_BUFFER_MAX;
	cchars = malloc(max_len);
	uchars = malloc(max_len * sizeof(Unicode));
	memset(cchars, 0, max_len);
	memset(uchars, 0, max_len * sizeof(Unicode));

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
		return 1;

	if(opt_output)
	{
		conversion_output(stdout, conversion);
		return 0;
	}

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
		if(opt_direction == FORWARD)
			conversion_convert_to(uchars, uchars_len, conversion);
		else if(opt_direction == BACKWARD)
			conversion_convert_from(uchars, uchars_len, conversion);

		/*   check that there should be enough room
		     for UTF conversion   */
		if(uchars_len * 3 >= max_len)
		{
			max_len = uchars_len * 3 + 1;

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
		}

		utf16le_convert_to_utf8(cchars, max_len, uchars, uchars_len);
		printf("%s\n", cchars);
	}

	conversion_free(conversion);

	return 0;
}

/******************************************************************************/
