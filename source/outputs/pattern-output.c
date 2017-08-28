/*

LibLouisAPH Braille Translation and Back-Translation Library

Copyright (C) 2017 Mike Gray, American Printing House for the Blind, Inc.

This file is part of LibLouisAPH.

LibLouisAPH is free software: you can redistribute it and/or modify it
under the terms of the GNU Lesser General Public License as published
by the Free Software Foundation, either version 2.1 of the License, or
(at your option) any later version.

LibLouisAPH is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with LibLouisAPH. If not, see <http://www.gnu.org/licenses/>.

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
	Unicode type;
	Unicode prv;
	Unicode nxt;
	Unicode data[1];
};

/*   gdb won't know what struct expression is unless it is actually used   */
struct expression *expr_debug;

static char spaces[] = "..............................";
static int  space = 30;

/******************************************************************************/

static void attrs_output_brackets(const Unicode attrs0, const Unicode attrs1)
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
		utf16le_output_char_escape(stdout, attrs_chars[i]);
	for(i = 0; i < 16; i++)
	if(attrs1 & BIT(i))
		utf16le_output_char_escape(stdout, attrs_chars[i + 16]);

	if(cnt > 1)
		printf("]");
}

static void attrs_output(const Unicode attrs0, const Unicode attrs1)
{
	int i;

	for(i = 0; i < 16; i++)
	if(attrs0 & BIT(i))
		utf16le_output_char_escape(stdout, attrs_chars[i]);
	for(i = 0; i < 16; i++)
	if(attrs1 & BIT(i))
		utf16le_output_char_escape(stdout, attrs_chars[i + 16]);
}

static void pattern_output_expression(const Unicode *expr_data, int expr_crs)
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
				utf16le_output_char_escape(stdout, EXPR_CONST_DATA(expr_crs)[i + 1]);
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

void pattern_output(const Unicode *expr_data)
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
void pattern_print_expression(FILE *output, const Unicode *expr_data, int expr_crs)
{
	int i;

	if(expr_crs == PTN_END)
		return;

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
				utf16le_output_char_escape(stdout, EXPR_DATA_1(expr_crs));
			else
			{
				fputs("[", output);
				for(i = 0; i < EXPR_DATA_0(expr_crs); i++)
					utf16le_output_char_escape(output, EXPR_CONST_DATA(expr_crs)[i + 1]);
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

void pattern_print(FILE *output, const Unicode *expr_data, const char *attrs_chars_)
{
	set_attrs_chars(attrs_chars_);

	if(expr_data[0] > 0 && expr_data[0] != PTN_END)
		pattern_print_expression(output, expr_data, 2);
	fflush(output);
}

void pattern_print_line(FILE *output, const Unicode *expr_data, const char *attrs_chars_)
{
	pattern_print(output, expr_data, attrs_chars_);
	fputs("\n", output);
	fflush(output);
}

/******************************************************************************/
