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

#include "pattern-private.h"
#include "pattern.h"
#include "utf-convert.h"
#include "utf-output.h"
#include "translate.h"

struct expression
{
	unichar type;
	unichar prv;
	unichar nxt;
	unichar data[1];
};

/*   gdb won't know what struct expression is unless it is actually used   */
struct expression *expr_debug;

static char spaces[] = "..............................";
static int  space = 30;

/******************************************************************************/

static void attrs_output_brackets(const unichar attrs0, const unichar attrs1)
{
	int cnt, i;

	cnt = 0;
	for(i = 0; i < 16; i++)
	if(attrs0 & BIT(i))
		cnt++;
	for(i = 0; i < 16; i++)
	if(attrs1 & BIT(i))
		cnt++;

	if(cnt > 1)
		printf("[");

	for(i = 0; i < 16; i++)
	if(attrs0 & BIT(i))
		utf16_output_char_escape(stdout, attrs_chars[i]);
	for(i = 0; i < 16; i++)
	if(attrs1 & BIT(i))
		utf16_output_char_escape(stdout, attrs_chars[i + 16]);

	if(cnt > 1)
		printf("]");
}

static void attrs_output(const unichar attrs0, const unichar attrs1)
{
	int i;

	for(i = 0; i < 16; i++)
	if(attrs0 & BIT(i))
		utf16_output_char_escape(stdout, attrs_chars[i]);
	for(i = 0; i < 16; i++)
	if(attrs1 & BIT(i))
		utf16_output_char_escape(stdout, attrs_chars[i + 16]);
}

static void pattern_output_expression(const unichar *expr_data, int expr_crs)
{
	int i;

	while(EXPR_TYPE(expr_crs) != PTN_END)
	{
		printf("%s%d", &spaces[space], expr_crs);
		if(expr_crs < 100)
			printf(" ");
		if(expr_crs < 10)
			printf(" ");
		for(i = 0; i < 13 - (30 - space); i++)
			printf(" ");

		switch(EXPR_TYPE(expr_crs))
		{
		case PTN_START:

			printf("START\t%d\t%d\n", EXPR_PRV(expr_crs), EXPR_NXT(expr_crs));
			break;

		case PTN_GROUP:

			printf("(    \t%d\t%d\t-> %d\n", EXPR_PRV(expr_crs), EXPR_NXT(expr_crs), EXPR_DATA_0(expr_crs));
			space--;
			if(space < 0)
				space = 0;
			pattern_output_expression(expr_data, EXPR_DATA_0(expr_crs));
			space++;
			if(space > 30)
				space = 30;
			break;

		case PTN_NOT:

			printf("!    \t%d\t%d\t-> %d\n", EXPR_PRV(expr_crs), EXPR_NXT(expr_crs), EXPR_DATA_0(expr_crs));
			space--;
			if(space < 0)
				space = 0;
			pattern_output_expression(expr_data, EXPR_DATA_0(expr_crs));
			space++;
			if(space > 30)
				space = 30;
			break;

		case PTN_ONE_MORE:

			printf("+    \t%d\t%d\t-> %d\t#%d\n", EXPR_PRV(expr_crs), EXPR_NXT(expr_crs), EXPR_DATA_0(expr_crs), EXPR_DATA_1(expr_crs));
			space--;
			if(space < 0)
				space = 0;
			pattern_output_expression(expr_data, EXPR_DATA_0(expr_crs));
			space++;
			if(space > 30)
				space = 30;
			break;

		case PTN_ZERO_MORE:

			printf("*    \t%d\t%d\t-> %d\t#%d\n", EXPR_PRV(expr_crs), EXPR_NXT(expr_crs), EXPR_DATA_0(expr_crs), EXPR_DATA_1(expr_crs));
			space--;
			if(space < 0)
				space = 0;
			pattern_output_expression(expr_data, EXPR_DATA_0(expr_crs));
			space++;
			if(space > 30)
				space = 30;
			break;

		case PTN_OPTIONAL:

			printf("?    \t%d\t%d\t-> %d\n", EXPR_PRV(expr_crs), EXPR_NXT(expr_crs), EXPR_DATA_0(expr_crs));
			space--;
			if(space < 0)
				space = 0;
			pattern_output_expression(expr_data, EXPR_DATA_0(expr_crs));
			space++;
			if(space > 30)
				space = 30;
			break;

		case PTN_ALTERNATE:

			printf("|    \t%d\t%d\t-> %d\t-> %d\n", EXPR_PRV(expr_crs), EXPR_NXT(expr_crs), EXPR_DATA_0(expr_crs), EXPR_DATA_1(expr_crs));
			space--;
			if(space < 0)
				space = 0;
			pattern_output_expression(expr_data, EXPR_DATA_0(expr_crs));
			pattern_output_expression(expr_data, EXPR_DATA_1(expr_crs));
			space++;
			if(space > 30)
				space = 30;
			break;

		case PTN_ANY:

			printf(".    \t%d\t%d\n", EXPR_PRV(expr_crs), EXPR_NXT(expr_crs));
			break;

		case PTN_ATTRIBUTES:

			printf("%%    \t%d\t%d\t", EXPR_PRV(expr_crs), EXPR_NXT(expr_crs));
			attrs_output(EXPR_DATA_0(expr_crs), EXPR_DATA_1(expr_crs));
			puts("");
			break;

		case PTN_CHARS:

			printf("[]   \t%d\t%d\t", EXPR_PRV(expr_crs), EXPR_NXT(expr_crs));
			for(i = 0; i < EXPR_DATA_0(expr_crs); i++)
				utf16_output_char_escape(stdout, EXPR_CONST_DATA(expr_crs)[i + 1]);
			puts("");
			break;

		case PTN_SUBPATTERN:

			printf("@    \t%d\t%d\t", EXPR_PRV(expr_crs), EXPR_NXT(expr_crs));
			for(i = 0; i < EXPR_DATA_0(expr_crs); i++)
				printf("%c", EXPR_CONST_DATA(expr_crs)[i + 1]);
			puts("");
			break;

		case PTN_END_OF_INPUT:

			printf("^    \t%d\t%d\n", EXPR_PRV(expr_crs), EXPR_NXT(expr_crs));
			break;

		default:

			printf("%d?    \t%d\t%d\n", EXPR_TYPE(expr_crs), EXPR_PRV(expr_crs), EXPR_NXT(expr_crs));
			break;
		}

		expr_crs = EXPR_NXT(expr_crs);
	}

	printf("%s%d", &spaces[space], expr_crs);
	if(expr_crs < 100)
		printf(" ");
	if(expr_crs < 10)
		printf(" ");
	for(i = 0; i < 13 - (30 - space); i++)
		printf(" ");
	printf("END\t%d\t%d\n", EXPR_PRV(expr_crs), EXPR_NXT(expr_crs));
	fflush(stdout);
	return;
}

void pattern_output(const unichar *expr_data)
{
	printf("%d    \tlength\n", expr_data[0]);
	printf("%d    \tloops\n", expr_data[1]);
	if(expr_data[0] > 0 && expr_data[0] != PTN_END)
		pattern_output_expression(expr_data, 2);
	fflush(stdout);
}

/******************************************************************************/

#ifndef DEBUG
static
#endif
void pattern_print_expression(FILE *output, const unichar *expr_data, int expr_crs)
{
	int i;

	if(expr_crs == PTN_END)
		return;

	ASSERT(expr_crs > 1)
	ASSERT(expr_crs < expr_data[0])

	while(EXPR_TYPE(expr_crs) != PTN_END)
	{
		switch(EXPR_TYPE(expr_crs))
		{
		case PTN_START:  break;

		case PTN_GROUP:

			fputs("(", output);
			pattern_print_expression(output, expr_data, EXPR_DATA_0(expr_crs));
			fputs(")", output);
			break;

		case PTN_NOT:

			fputs("!", output);
			pattern_print_expression(output, expr_data, EXPR_DATA_0(expr_crs));
			break;

		case PTN_ONE_MORE:

			pattern_print_expression(output, expr_data, EXPR_DATA_0(expr_crs));
			fputs("+", output);
			break;

		case PTN_ZERO_MORE:

			pattern_print_expression(output, expr_data, EXPR_DATA_0(expr_crs));
			fputs("*", output);
			break;

		case PTN_OPTIONAL:

			pattern_print_expression(output, expr_data, EXPR_DATA_0(expr_crs));
			fputs("?", output);
			break;

		case PTN_ALTERNATE:

			pattern_print_expression(output, expr_data, EXPR_DATA_0(expr_crs));
			fputs("|", output);
			pattern_print_expression(output, expr_data, EXPR_DATA_1(expr_crs));
			break;

		case PTN_ANY:

			fputs(".", output);
			break;

		case PTN_ATTRIBUTES:

			fputs("%", output);
			attrs_output_brackets(EXPR_DATA_0(expr_crs), EXPR_DATA_1(expr_crs));
			break;

		case PTN_CHARS:

			if(EXPR_DATA_0(expr_crs) == 1)
				utf16_output_char_escape(stdout, EXPR_DATA_1(expr_crs));
			else
			{
				fputs("[", output);
				for(i = 0; i < EXPR_DATA_0(expr_crs); i++)
					utf16_output_char_escape(output, EXPR_CONST_DATA(expr_crs)[i + 1]);
				fputs("]", output);
			}
			break;

		case PTN_SUBPATTERN:

			fputs("@{", output);
			for(i = 0; i < EXPR_DATA_0(expr_crs); i++)
				fprintf(output, "%c", EXPR_CONST_DATA(expr_crs)[i + 1]);
			fputs("}", output);
			break;

		case PTN_END_OF_INPUT:

			fputs("^", output);
			break;

		default:  fprintf(output, "0x%x?", EXPR_TYPE(expr_crs));  return;
		}

		expr_crs = EXPR_NXT(expr_crs);
	}

	return;
}

void pattern_print(FILE *output, const unichar *expr_data, const char *attrs_chars_)
{
	set_attrs_chars(attrs_chars_);

	if(expr_data[0] > 0 && expr_data[0] != PTN_END)
		pattern_print_expression(output, expr_data, 2);
	fflush(output);
}

void pattern_print_line(FILE *output, const unichar *expr_data, const char *attrs_chars_)
{
	pattern_print(output, expr_data, attrs_chars_);
	fputs("\n", output);
	fflush(output);
}

/******************************************************************************/
