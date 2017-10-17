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

#ifdef DEBUG

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "utf-convert.h"
#include "utf-output.h"
#include "table-output.h"
#include "log.h"

/******************************************************************************/

static inline void cchars_convert_spaces(char *cchars, const int cchars_len)
{
	int i;

	for(i = 0; i < cchars_len; i++)
	if(!cchars[i])
		return;
	else switch(cchars[i])
	{
	case '\n':
	case '\r':
	case '\t':  cchars[i] = ' ';
	}
}

/******************************************************************************/

void debug_output(const Unicode *uchars, const int uchars_len)
{
	char cchars[0x4000];
	int cchars_len;

	if(uchars_len <= 0 || !uchars)
	{
		puts("");
		fflush(stdout);
		return;
	}

	memset(cchars, 0, 0x4000);
	cchars_len = utf16le_convert_to_utf8(cchars, 0x4000, uchars, uchars_len);
	cchars_convert_spaces(cchars, cchars_len);

	printf("%s", cchars);
	fflush(stdout);
}

void debug_output_line(const Unicode *uchars, const int uchars_len)
{
	char cchars[0x4000];
	int cchars_len;

	rewind(stdout);

	if(uchars_len <= 0 || !uchars)
	{
		puts("");
		fflush(stdout);
		return;
	}

	memset(cchars, 0, 0x4000);
	cchars_len = utf16le_convert_to_utf8(cchars, 0x4000, uchars, uchars_len);
	cchars_convert_spaces(cchars, cchars_len);

	printf("%s\n", cchars);
	fflush(stdout);
}

void debug_output_pad(const Unicode *uchars, const int uchars_len)
{
	char cchars[0x4000];
	int cchars_len, i;

	if(uchars_len <= 0 || !uchars)
	{
		puts("");
		fflush(stdout);
		return;
	}

	memset(cchars, 0, 0x4000);
	cchars_len = utf16le_convert_to_utf8(cchars, 0x4000, uchars, uchars_len);
	cchars_convert_spaces(cchars, cchars_len);

	printf("%s", cchars);
	for(i = strlen(cchars); i < uchars_len; i++)
		printf(" ");
	fflush(stdout);
}

void debug_output_chomp(const Unicode *uchars, const int uchars_len)
{
	char cchars[0x4000], *crs;
	int cchars_len;

	if(uchars_len <= 0 || !uchars)
	{
		puts("");
		fflush(stdout);
		return;
	}

	memset(cchars, 0, 0x4000);
	cchars_len = utf16le_convert_to_utf8(cchars, 0x4000, uchars, uchars_len);
	cchars_convert_spaces(cchars, cchars_len);

	for(crs = cchars; *crs; crs++);
	crs--;
	while(crs >= cchars && (*crs == '\n' || *crs == '\r'))
		*crs-- = 0;
	printf("%s", cchars);
	fflush(stdout);
}

void debug_output_uchar(const Unicode uchar)
{
	char cchars[16];
	Unicode uchars[2];

	switch(uchar)
	{
	case 0xa0:
	case u' ':
	case u'\n':
	case u'\r':
	case u'\t':  printf(" ");  break;
	default:

		uchars[0] = uchar;
		uchars[1] = 0;
		utf16le_convert_to_utf8(cchars, 16, uchars, 2);
		printf("%s", cchars);
	}

	fflush(stdout);
}

void debug_output_uchar_escape(const Unicode uchar)
{
	char cchars[16];
	Unicode uchars[2];

	switch(uchar)
	{
	case 0xa0:   printf("\\S");  break;
	case u' ':   printf("\\s");  break;
	case u'\n':  printf("\\n");  break;
	case u'\r':  printf("\\r");  break;
	case u'\t':  printf("\\t");  break;
	default:

		uchars[0] = uchar;
		uchars[1] = 0;
		utf16le_convert_to_utf8(cchars, 16, uchars, 2);
		printf("%s", cchars);
	}

	fflush(stdout);
}

void debug_output_convert_private(const struct table *table, const Unicode *uchars, const int uchars_len)
{
	Unicode convert[0x4000];

	if(uchars_len > 0x3fff)
	{
		log_message(LOG_ERROR, "TOO LONG");
		return;
	}

	memset(convert, 0, 0x4000 * sizeof(Unicode));
	memcpy(convert, uchars, uchars_len * sizeof(Unicode));
	table_convert_markers(table, convert, uchars_len);
	utf16le_output(stdout, convert, uchars_len);
}

/******************************************************************************/

/* Calling pattern_print* functions directly from debug scripts using stdout
 * seems to have flushing issues.
*/

void pattern_print_expression(FILE *output, const Unicode *expr_data, int expr_crs);
void pattern_print(FILE *output, const Unicode *expr_data, const char *attrs_chars_);
void pattern_print_line(FILE *output, const Unicode *expr_data, const char *attrs_chars_);

void debug_pattern_print_expression(const Unicode *expr_data, int expr_crs)
{
	pattern_print_expression(stdout, expr_data, expr_crs);
	fflush(stdout);
}

void debug_pattern_print(const Unicode *expr_data, const char *attrs_chars_)
{
	pattern_print(stdout, expr_data, attrs_chars_);
	fflush(stdout);
}

void debug_pattern_print_line(const Unicode *expr_data, const char *attrs_chars_)
{
	pattern_print_line(stdout, expr_data, attrs_chars_);
	fflush(stdout);
}

/******************************************************************************/

#endif /*   DEBUG   */
