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
#include "translate.h"
#include "log.h"

static const struct translate *translate;
static int subpattern_level;

#ifdef PATTERN_OUTPUT_TRACE

#include "utf-output.h"
void pattern_print(FILE *output, const Unicode *expr_data, const char *attrs_chars_);
void pattern_print_expression(FILE *output, const Unicode *expr_data, int expr_crs);

#ifndef OUTPUT
#error OUTPUT needs to be defined
#endif

#define START  0
#define CALL   1
#define RETURN 2
#define SHOW   3

#define CHECK_OUTPUT(type, ret, msg) \
{ \
	int in = 0; \
	if(*input_crs > -1) \
		in = input[*input_crs]; \
	do_output(type, ret, in, input_minmax, *input_crs, input_dir, expr_data, expr_crs, not, loop_crs, loop_cnts, msg); \
}

#else

#define CHECK_OUTPUT(type, ret, msg) { ; }

#endif

/******************************************************************************/

#ifdef PATTERN_OUTPUT_TRACE

void pattern_output(const Unicode *expr_data);

static char spaces[] = "..............................";
static int  space = 30;

static void do_output(
	const int type, const int ret,
	const int input, const int input_minmax, const int input_crs, const int input_dir,
	const Unicode *expr_data, const int expr_crs,
	const int not,
	const int loop_crs, const int *loop_cnts,
	const char *msg)
{
	const Unicode *data;
	int cnt, i;

	switch(type)
	{
	case START:

		space--;
		return;
//		if(space < 0) space = 0;
//		printf("|%s()  ", &spaces[space]);
//		break;

	case CALL:

		printf("|%s>   ", &spaces[space]);
		break;

	case RETURN:

		printf("|%s<%d  ", &spaces[space], ret);
		space++;
		if(space > 31) space = 31;
		break;

	case SHOW:

		printf("|%s    ", &spaces[space]);
		break;
	}

	switch(expr_data[expr_crs])
	{
	case PTN_ERROR:         printf("# ");   break;
	case PTN_START:         printf("> ");   break;
	case PTN_END_OF_INPUT:  printf("^ ");   break;
	case PTN_ALTERNATE:     printf("| ");   break;
	case PTN_OPTIONAL:      printf("? ");   break;
	case PTN_ONE_MORE:      printf("+ ");   break;
	case PTN_ZERO_MORE:     printf("* ");   break;
	case PTN_NOT:           printf("! ");   break;
	case PTN_GROUP:         printf("( ");   break;
	case PTN_ANY:           printf(". ");   break;
	case PTN_ATTRIBUTES:    printf("%% ");  break;
	case PTN_CHARS:         printf("[ ");   break;
	case PTN_SUBPATTERN:    printf("@ ");   break;
	case PTN_END:           printf("< ");   break;
	default:                printf("  ");   break;
	}
	printf("%-5d ", expr_crs);

	if(input)
		utf16le_output_char_escape(stdout, input);
	else
		printf(" ");
	printf(" ");

	if(input_crs * input_dir >= input_minmax * input_dir)
		printf("#   ");
	else
		printf("%-3d ", input_crs);

	if(input_dir > 0)
		printf("<");
	else
		printf(">");
	printf("%-3d ", input_minmax);

	if(not)
		printf("!   ");
	else
		printf("    ");

	if(loop_crs)
	{
		printf("%-3d ", loop_crs);
		printf("%-3d ", loop_cnts[EXPR_DATA_1(loop_crs)]);
	}
	else
		printf("-   -   ");
	if(EXPR_TYPE(expr_crs) == PTN_ONE_MORE || EXPR_TYPE(expr_crs) == PTN_ZERO_MORE)
		printf("%-3d ", loop_cnts[EXPR_DATA_1(expr_crs)]);
	else
		printf("-   ");

	if(msg)
		printf("%s", msg);

	switch(expr_data[expr_crs])
	{
	case PTN_CHARS:

		data = EXPR_CONST_DATA(expr_crs);
		cnt = data[0] + 1;

		printf("   ");
		for(i = 1; i < cnt; i++)
			utf16le_output_char(stdout, data[i]);
		break;

	case PTN_ALTERNATE:

		if(type == SHOW && ret == 1)
		{
			printf("   ");
			pattern_print_expression(stdout, expr_data, EXPR_DATA_1(expr_crs));
			break;
		}

	case PTN_START:
	case PTN_END_OF_INPUT:
	case PTN_OPTIONAL:
	case PTN_ONE_MORE:
	case PTN_ZERO_MORE:
	case PTN_NOT:
	case PTN_GROUP:
	case PTN_ANY:

		printf("   ");
		pattern_print_expression(stdout, expr_data, EXPR_DATA_0(expr_crs));
		break;

	case PTN_ERROR:
	case PTN_ATTRIBUTES:
	case PTN_SUBPATTERN:
	case PTN_END:
	default:  break;
	}

	puts("");
	fflush(stdout);
}

#endif /*   PATTERN_OUTPUT_TRACE   */

/******************************************************************************/

ATTRIBUTE_FUNCTION_MALLOC
struct subpattern* subpattern_allocate(void)
{
	struct subpattern *subpattern;

	subpattern = MALLOC(sizeof(struct subpattern));
	LOG_ALLOCATE_FAIL_RETURN_NULL(subpattern)
	memset(subpattern, 0, sizeof(struct subpattern));
	return subpattern;
}

void subpattern_free(struct subpattern *subpattern)
{
	if(!subpattern)
		return;

	subpattern_free(subpattern->nxt);
	if(subpattern->tag)
		FREE(subpattern->tag);
	if(subpattern->expr_data)
		FREE(subpattern->expr_data);
	if(subpattern->src_data)
		FREE(subpattern->src_data);
	FREE(subpattern);
}

static struct subpattern* subpattern_find(struct subpattern *subpatterns, const Unicode *uchars, const int uchars_len)
{
	struct subpattern *subpattern;
	int i;

	subpattern = subpatterns;
	while(subpattern)
	{
		if(subpattern->tag_len == uchars_len)
		{
			for(i = 0; i < uchars_len; i++)
			if(subpattern->tag[i] != uchars[i])
				break;
			if(i == uchars_len)
				return subpattern;
		}
		subpattern = subpattern->nxt;
	}
	return NULL;
}

/******************************************************************************/

static void attr_from_char(Unicode *attrs0, Unicode *attrs1, const Unicode uchar)
{
	int i;

	for(i = 0; i < 16; i++)
	if(attrs_chars[i] == uchar)
	{
		*attrs0 |= BIT(i);
		return;
	}

	for(i = 16; i < 32; i++)
	if(attrs_chars[i] == uchar)
	{
		*attrs1 |= BIT(i - 16);
		return;
	}
}

/******************************************************************************/

static int pattern_compile_1(
	const Unicode *input,
	const int input_len,
	int *input_crs,
	Unicode *expr_data,
	const int expr_len,
	Unicode *expr_crs,
	Unicode *loop_cnts,
	struct subpattern *subpatterns);

static int pattern_compile_expression(
	const Unicode *input,
	const int input_len,
	int *input_crs,
	Unicode *expr_data,
	const int expr_len,
	Unicode *expr_crs,
	Unicode *loop_cnts,
	struct subpattern *subpatterns)
{
	struct subpattern *subpattern;
	Unicode *data, attrs0, attrs1;;
	int expr_start, expr_end, expr_sub, expr_crs_prv;
	int input_end, subinput_crs;
	int set, esc, nest, i;

	switch(input[*input_crs])
	{
	case '(':

		if(*expr_crs + 10 >= expr_len)
			return 0;

		(*input_crs)++;
		if(*input_crs >= input_len)
			return 0;

		/*   find closing parenthesis   */
		nest = esc = 0;
		for(input_end = *input_crs; input_end < input_len; input_end++)
		{
			if(input[input_end] == '\\' && !esc)
			{
				esc = 1;
				continue;
			}

			if(input[input_end] == '(' && !esc)
				nest++;
			else if(input[input_end] == ')' && !esc)
			{
				if(nest)
					nest--;
				else
					break;
			}

			esc = 0;
		}
		if(input_end >= input_len)
			return 0;

		EXPR_TYPE(*expr_crs) = PTN_GROUP;

		/*   compile sub expressions   */
		expr_crs_prv = *expr_crs;
		*expr_crs += 4;
		EXPR_DATA_0(expr_crs_prv) = *expr_crs;
		expr_sub = *expr_crs;
		EXPR_TYPE(expr_sub) = PTN_ERROR;
		EXPR_PRV(expr_sub) = PTN_END;
		EXPR_NXT(expr_sub) = PTN_END;
		if(!pattern_compile_1(input, input_end, input_crs, expr_data, expr_len, expr_crs, loop_cnts, subpatterns))
			return 0;
		(*input_crs)++;

		/*   reset end expression   */
		expr_end = *expr_crs;
		EXPR_NXT(expr_end) = expr_crs_prv;

		return *expr_crs += 3;

	case '!':

		if(*expr_crs + 10 >= expr_len)
			return 0;

		(*input_crs)++;
		if(*input_crs >= input_len)
			return 0;

		EXPR_TYPE(*expr_crs) = PTN_NOT;
		expr_crs_prv = *expr_crs;
		*expr_crs += 4;
		EXPR_DATA_0(expr_crs_prv) = *expr_crs;

		/*   create start expression   */
		expr_start = *expr_crs;
		EXPR_TYPE(expr_start) = PTN_START;
		EXPR_PRV(expr_start) = PTN_END;
		*expr_crs += 3;
		EXPR_NXT(expr_start) = *expr_crs;

		/*   compile sub expression   */
		expr_sub = *expr_crs;
		EXPR_TYPE(expr_sub) = PTN_ERROR;
		EXPR_PRV(expr_sub) = expr_start;
		EXPR_NXT(expr_sub) = PTN_END;

		if(!pattern_compile_expression(input, input_len, input_crs, expr_data, expr_len, expr_crs, loop_cnts, subpatterns))
			return 0;

		EXPR_NXT(expr_sub) = *expr_crs;

		/*   create end expression   */
		expr_end = *expr_crs;
		EXPR_TYPE(expr_end) = PTN_END;
		EXPR_PRV(expr_end) = expr_sub;
		EXPR_NXT(expr_end) = expr_crs_prv;

		return *expr_crs += 3;

	case '+':

		if(*expr_crs + 4 >= expr_len)
			return 0;
		EXPR_TYPE(*expr_crs) = PTN_ONE_MORE;
		EXPR_DATA_1(*expr_crs) = (*loop_cnts)++;
		(*input_crs)++;
		return *expr_crs += 5;

	case '*':

		if(*expr_crs + 4 >= expr_len)
			return 0;
		EXPR_TYPE(*expr_crs) = PTN_ZERO_MORE;
		EXPR_DATA_1(*expr_crs) = (*loop_cnts)++;
		(*input_crs)++;
		return *expr_crs += 5;

	case '?':

		if(*expr_crs + 4 >= expr_len)
			return 0;
		EXPR_TYPE(*expr_crs) = PTN_OPTIONAL;
		(*input_crs)++;
		return *expr_crs += 4;

	case '|':

		if(*expr_crs + 5 >= expr_len)
			return 0;
		EXPR_TYPE(*expr_crs) = PTN_ALTERNATE;
		(*input_crs)++;
		return *expr_crs += 5;

	case '.':

		if(*expr_crs + 3 >= expr_len)
			return 0;
		EXPR_TYPE(*expr_crs) = PTN_ANY;
		(*input_crs)++;
		return *expr_crs += 3;

	case '%':

		if(*expr_crs + 5 >= expr_len)
			return 0;

		(*input_crs)++;
		if(*input_crs >= input_len)
			return 0;

		/*   find closing bracket   */
		if(input[*input_crs] == '[')
		{
			set = 1;
			(*input_crs)++;
			for(input_end = *input_crs; input_end < input_len; input_end++)
			if(input[input_end] == ']')
				break;
			if(input_end >= input_len)
				return 0;
		}
		else
		{
			set = 0;
			input_end = *input_crs + 1;
		}

		EXPR_TYPE(*expr_crs) = PTN_ATTRIBUTES;

		attrs0 = attrs1 = 0;
		for( ; (*input_crs) < input_end; (*input_crs)++)
			attr_from_char(&attrs0, &attrs1, input[*input_crs]);

		EXPR_DATA_0(*expr_crs) = attrs0;
		EXPR_DATA_1(*expr_crs) = attrs1;

		if(set)
			(*input_crs)++;
		return *expr_crs += 5;

	case '[':

		(*input_crs)++;
		if(*input_crs >= input_len)
			return 0;

		/*   find closing bracket   */
		esc = 0;
		for(input_end = *input_crs; input_end < input_len; input_end++)
		{
			if(input[input_end] == '\\' && !esc)
			{
				esc = 1;
				continue;
			}

			if(input[input_end] == ']' && !esc)
				break;
			esc = 0;
		}
		if(input_end >= input_len)
			return 0;

		if(*expr_crs + 4 + (input_end - *input_crs) >= expr_len)
			return 0;

		EXPR_TYPE(*expr_crs) = PTN_CHARS;

		esc = 0;
		data = EXPR_DATA(*expr_crs);
		for(i = 1; *input_crs < input_end; (*input_crs)++)
		{
			if(input[*input_crs] == '\\' && !esc)
			{
				esc = 1;
				continue;
			}

			esc = 0;
			data[i++] = (Unicode)input[*input_crs];
		}
		data[0] = i - 1;
		(*input_crs)++;
		return *expr_crs += 4 + data[0];

	case '@':

		if(*expr_crs + 10 >= expr_len)
			return 0;

		(*input_crs)++;
		if(*input_crs >= input_len)
			return 0;

		/*   which bracket   */
		if(input[*input_crs] == '{')
		{
			set = 1;
			(*input_crs)++;
			for(input_end = *input_crs; input_end < input_len; input_end++)
			if(input[input_end] == '}')
				break;
			if(input_end >= input_len)
				return 0;

			if(*expr_crs + 4 + (input_end - *input_crs) >= expr_len)
				return 0;

			EXPR_TYPE(*expr_crs) = PTN_SUBPATTERN;

			esc = 0;
			data = EXPR_DATA(*expr_crs);
			for(i = 1; *input_crs < input_end; (*input_crs)++)
			{
				if(input[*input_crs] == '\\' && !esc)
				{
					esc = 1;
					continue;
				}

				esc = 0;
				data[i++] = (Unicode)input[*input_crs];
			}
			data[0] = i - 1;
			(*input_crs)++;
			return *expr_crs += 4 + data[0];
		}

		/*   find closing bracket   */
		else if(input[*input_crs] == '[')
		{
			set = 1;
			(*input_crs)++;
			for(input_end = *input_crs; input_end < input_len; input_end++)
			if(input[input_end] == ']')
				break;
			if(input_end >= input_len)
				return 0;

			subpattern = subpattern_find(subpatterns, &input[*input_crs], input_end - *input_crs);
			if(!subpattern)
				return 0;
			if(subpattern->processing)
				return 0;

			EXPR_TYPE(*expr_crs) = PTN_GROUP;

			/*   compile sub pattern   */
			expr_crs_prv = *expr_crs;
			*expr_crs += 4;
			EXPR_DATA_0(expr_crs_prv) = *expr_crs;
			expr_sub = *expr_crs;
			EXPR_TYPE(expr_sub) = PTN_ERROR;
			EXPR_PRV(expr_sub) = PTN_END;
			EXPR_NXT(expr_sub) = PTN_END;
			subinput_crs = 0;
			subpattern->processing = 1;
			if(!pattern_compile_1(subpattern->src_data, subpattern->src_len, &subinput_crs, expr_data, expr_len, expr_crs, loop_cnts, subpatterns))
				return 0;
			subpattern->processing = 0;
			*input_crs = input_end + 1;

			/*   reset end expression   */
			expr_end = *expr_crs;
			EXPR_NXT(expr_end) = expr_crs_prv;

			return *expr_crs += 3;
		}

		return 0;

	case '^':
	case '$':

		if(*expr_crs + 3 >= expr_len)
			return 0;
		EXPR_TYPE(*expr_crs) = PTN_END_OF_INPUT;
		(*input_crs)++;
		return *expr_crs += 3;

	case '\\':

		(*input_crs)++;
		if(*input_crs >= input_len)
			return 0;

	default:

		if(*expr_crs + 5 >= expr_len)
			return 0;
		EXPR_TYPE(*expr_crs) = PTN_CHARS;
		EXPR_DATA_0(*expr_crs) = 1;
		EXPR_DATA_1(*expr_crs) = (Unicode)input[*input_crs];
		(*input_crs)++;
		return *expr_crs += 5;
	}

}

/* Compile all expression sequences, resolving character sets, attributes,
 * groups, nots, and subpatterns.  Note that unlike the other compile functions,
 * on returning the expr_crs is set to the last end expression, not after it.
*/
static int pattern_compile_1(
	const Unicode *input,
	const int input_len,
	int *input_crs,
	Unicode *expr_data,
	const int expr_len,
	Unicode *expr_crs,
	Unicode *loop_cnts,
	struct subpattern *subpatterns)
{
	int expr_crs_prv;

	if(*expr_crs + 6 >= expr_len)
		return 0;

	expr_crs_prv = *expr_crs;

	/*   setup start expression   */
	EXPR_TYPE(*expr_crs) = PTN_START;
	EXPR_PRV(*expr_crs) = PTN_END;
	*expr_crs += 3;
	EXPR_NXT(expr_crs_prv) = *expr_crs;

	/*   setup end expression   */
	EXPR_TYPE(*expr_crs) = PTN_END;
	EXPR_PRV(*expr_crs) = expr_crs_prv;
	EXPR_NXT(*expr_crs) = PTN_END;

	while(*input_crs < input_len)
	{
		expr_crs_prv = *expr_crs;
		if(!pattern_compile_expression(input, input_len, input_crs, expr_data, expr_len, expr_crs, loop_cnts, subpatterns))
			return 0;

		/*   setup end expression   */
		if(*expr_crs + 3 >= expr_len)
			return 0;
		EXPR_NXT(expr_crs_prv) = *expr_crs;
		EXPR_TYPE(*expr_crs) = PTN_END;
		EXPR_PRV(*expr_crs) = expr_crs_prv;
		EXPR_NXT(*expr_crs) = PTN_END;
	}

	return *expr_crs;
}

/* Resolve optional and loop expressions.
*/
static int pattern_compile_2(Unicode *expr_data, int expr_at, const int expr_len, Unicode *expr_crs)
{
	int expr_start, expr_end, expr_prv, expr_sub;

	while(EXPR_TYPE(expr_at) != PTN_END)
	{
		if(EXPR_TYPE(expr_at) == PTN_GROUP || EXPR_TYPE(expr_at) == PTN_NOT)
		{
			if(!pattern_compile_2(expr_data, EXPR_DATA_0(expr_at), expr_len, expr_crs))
				return 0;
		}

		if(   EXPR_TYPE(expr_at) == PTN_ZERO_MORE
		   || EXPR_TYPE(expr_at) == PTN_ONE_MORE
		   || EXPR_TYPE(expr_at) == PTN_OPTIONAL)
		{
			if(*expr_crs + 6 >= expr_len)
				return 0;

			/*   get previous expressions, there must
			     be at least something and a PTN_START   */
			expr_sub = EXPR_PRV(expr_at);
			if(EXPR_TYPE(expr_sub) == PTN_START)
				return 0;
			expr_prv = EXPR_PRV(expr_sub);

			/*   create start expression   */
			expr_start = *expr_crs;
			EXPR_TYPE(expr_start) = PTN_START;
			EXPR_PRV(expr_start) = PTN_END;
			EXPR_NXT(expr_start) = expr_sub;
			*expr_crs += 3;

			/*   create end expression   */
			expr_end = *expr_crs;
			EXPR_TYPE(expr_end) = PTN_END;
			EXPR_PRV(expr_end) = expr_sub;
			EXPR_NXT(expr_end) = expr_at;
			*expr_crs += 3;

			/*   relink previous expression before sub expression   */
			EXPR_DATA_0(expr_at) = expr_start;
			EXPR_NXT(expr_prv) = expr_at;
			EXPR_PRV(expr_at) = expr_prv;

			/*   relink sub expression to start and end   */
			EXPR_PRV(expr_sub) = expr_start;
			EXPR_NXT(expr_sub) = expr_end;
		}

		expr_at = EXPR_NXT(expr_at);
	}

	return 1;
}

/* Resolves alternative expressions.
*/
static int pattern_compile_3(Unicode *expr_data, int expr_at, const int expr_len, Unicode *expr_crs)
{
	int expr_mrk, expr_start, expr_end, expr_sub_start, expr_sub_end;

	while(EXPR_TYPE(expr_at) != PTN_END)
	{
		if(   EXPR_TYPE(expr_at) == PTN_GROUP
		   || EXPR_TYPE(expr_at) == PTN_NOT
		   || EXPR_TYPE(expr_at) == PTN_OPTIONAL
		   || EXPR_TYPE(expr_at) == PTN_ZERO_MORE
		   || EXPR_TYPE(expr_at) == PTN_ONE_MORE)
		{
			if(!pattern_compile_3(expr_data, EXPR_DATA_0(expr_at), expr_len, expr_crs))
				return 0;
		}

		if(EXPR_TYPE(expr_at) == PTN_ALTERNATE)
		{
			if(*expr_crs + 12 >= expr_len)
				return 0;

			/*   get previous start expression,
			     can include alternate expressions   */
			expr_mrk = EXPR_PRV(expr_at);
			if(EXPR_TYPE(expr_mrk) == PTN_START)
				return 0;
			expr_sub_end = expr_mrk;
			while(EXPR_TYPE(expr_mrk) != PTN_START)
				expr_mrk = EXPR_PRV(expr_mrk);
			expr_sub_start = EXPR_NXT(expr_mrk);

			/*   create first start expression   */
			expr_start = *expr_crs;
			EXPR_TYPE(expr_start) = PTN_START;
			EXPR_PRV(expr_start) = PTN_END;
			EXPR_NXT(expr_start) = expr_sub_start;
			*expr_crs += 3;

			/*   create first end expression   */
			expr_end = *expr_crs;
			EXPR_TYPE(expr_end) = PTN_END;
			EXPR_PRV(expr_end) = expr_sub_end;
			EXPR_NXT(expr_end) = expr_at;
			*expr_crs += 3;

			/*   relink previous expression before sub expression   */
			EXPR_DATA_0(expr_at) = expr_start;
			EXPR_NXT(expr_mrk) = expr_at;
			EXPR_PRV(expr_at) = expr_mrk;

			/*   relink sub expression to start and end   */
			EXPR_PRV(expr_sub_start) = expr_start;
			EXPR_NXT(expr_sub_end) = expr_end;

			/*   get following PTN_END or PTN_ALTERNATE expression   */
			expr_mrk = EXPR_NXT(expr_at);
			if(EXPR_TYPE(expr_mrk) == PTN_END || EXPR_TYPE(expr_mrk) == PTN_ALTERNATE)
				return 0;
			expr_sub_start = expr_mrk;
			while(EXPR_TYPE(expr_mrk) != PTN_END && EXPR_TYPE(expr_mrk) != PTN_ALTERNATE)
				expr_mrk = EXPR_NXT(expr_mrk);
			expr_sub_end = EXPR_PRV(expr_mrk);

			/*   create first start expression   */
			expr_start = *expr_crs;
			EXPR_TYPE(expr_start) = PTN_START;
			EXPR_PRV(expr_start) = PTN_END;
			EXPR_NXT(expr_start) = expr_sub_start;
			*expr_crs += 3;

			/*   create first end expression   */
			expr_end = *expr_crs;
			EXPR_TYPE(expr_end) = PTN_END;
			EXPR_PRV(expr_end) = expr_sub_end;
			EXPR_NXT(expr_end) = expr_at;
			*expr_crs += 3;

			/*   relink following expression before sub expression   */
			EXPR_DATA_1(expr_at) = expr_start;
			EXPR_PRV(expr_mrk) = expr_at;
			EXPR_NXT(expr_at) = expr_mrk;

			/*   relink sub expression to start and end   */
			EXPR_PRV(expr_sub_start) = expr_start;
			EXPR_NXT(expr_sub_end) = expr_end;

			/*   check expressions were after alternate and got moved into
			     a sub expression, previous expressions already checked   */
			if(!pattern_compile_3(expr_data, EXPR_DATA_1(expr_at), expr_len, expr_crs))
				return 0;
		}

		expr_at = EXPR_NXT(expr_at);
	}

	return 1;
}

int pattern_compile(
	Unicode *expr_data,
	const int expr_len,
	const Unicode *input,
	const int input_len,
	const char *attrs_chars_,
	struct subpattern *subpatterns)
{
	int input_crs;

	set_attrs_chars(attrs_chars_);

	input_crs = 0;
	expr_data[0] = 2;
	expr_data[1] = 0;

	if(!pattern_compile_1(input, input_len, &input_crs, expr_data, expr_len, &expr_data[0], &expr_data[1], subpatterns))
		return 0;

	/*   shift past the last end   */
	expr_data[0] += 3;

	if(!pattern_compile_2(expr_data, 2, expr_len, &expr_data[0]))
		return 0;

	if(!pattern_compile_3(expr_data, 2, expr_len, &expr_data[0]))
		return 0;

	return expr_data[0];
}

/******************************************************************************/

static void pattern_reverse_expression(Unicode *expr_data, const int expr_start);

static void pattern_reverse_branch(Unicode *expr_data, const int expr_at)
{
	switch(EXPR_TYPE(expr_at))
	{
	case PTN_ALTERNATE:

#ifdef PATTERN_REVERSE_ALTERNATE_ORDER
		pattern_reverse_expression(expr_data, EXPR_DATA_0(expr_at));
		expr_swap = EXPR_DATA_0(expr_at);
		EXPR_DATA_0(expr_at) = EXPR_DATA_1(expr_at);
		EXPR_DATA_1(expr_at) = expr_swap;
#else
		pattern_reverse_expression(expr_data, EXPR_DATA_1(expr_at));
#endif

	case PTN_GROUP:
	case PTN_NOT:
	case PTN_ONE_MORE:
	case PTN_ZERO_MORE:
	case PTN_OPTIONAL:

		pattern_reverse_expression(expr_data, EXPR_DATA_0(expr_at));
	}
}

static void pattern_reverse_expression(Unicode *expr_data, const int expr_start)
{
	Unicode expr_end, expr_crs, expr_prv;

	expr_end = EXPR_NXT(expr_start);

	/*   empty expression   */
	if(EXPR_TYPE(expr_end) == PTN_END)
		return;

	/*   find end expression   */
	while(EXPR_TYPE(expr_end) != PTN_END)
		expr_end = EXPR_NXT(expr_end);

	expr_crs = EXPR_PRV(expr_end);
	expr_prv = EXPR_PRV(expr_crs);

	/*   relink expression before end expression   */
	EXPR_NXT(expr_start) = expr_crs;
	EXPR_PRV(expr_crs)   = expr_start;
	EXPR_NXT(expr_crs)   = expr_prv;

	/*   reverse any branching expressions   */
	pattern_reverse_branch(expr_data, expr_crs);

	while(expr_prv != expr_start)
	{
		/*   shift current expression   */
		expr_crs = expr_prv;
		expr_prv = EXPR_PRV(expr_prv);

		/*   reverse any branching expressions   */
		pattern_reverse_branch(expr_data, expr_crs);

		if(expr_prv == expr_start)
			break;

		/*   relink current expression   */
		EXPR_PRV(expr_crs) = EXPR_NXT(expr_crs);
		EXPR_NXT(expr_crs) = expr_prv;
	}

	/*   relink expression after start expression   */
	EXPR_PRV(expr_crs) = EXPR_NXT(expr_crs);
	EXPR_NXT(expr_crs) = expr_end;
	EXPR_PRV(expr_end) = expr_crs;
}

void pattern_reverse(Unicode *expr_data)
{
	pattern_reverse_expression(expr_data, 2);
}

/******************************************************************************/

static int pattern_check_chars(const Unicode input_char, const Unicode *expr_data)
{
	int expr_cnt, i;

	expr_cnt = expr_data[0] + 1;

	for(i = 1; i < expr_cnt; i++)
	if(input_char == expr_data[i])
		break;

	if(i == expr_cnt)
		return 0;
	return 1;
}

static int pattern_check_attrs(const Unicode input_char, const Unicode *expr_data)
{
	int attrs;

	attrs = ((expr_data[1] << 16) | expr_data[0]);
	if(!(table_get_unichar_attributes(translate->tables[translate->table_crs], input_char) & attrs))
		return 0;
	return 1;
}

static int subpattern_check(
	const Unicode *input,
	int *input_crs,
	const int input_minmax,
	const int input_dir,
	const Unicode *expr_data,
	struct subpattern *subpatterns);

static int pattern_check_expression(
	const Unicode * const input,
	int *input_crs,
	const int input_minmax,
	const int input_dir,
	const Unicode * const expr_data,
	struct subpattern *subpatterns,
	int expr_crs,
	int not,
	int loop_crs,
	int *loop_cnts)
{
	struct subpattern *subpattern;
	int input_crs_prv, input_start, loop_crs_prv, loop_cnt_prv, ret;

	loop_crs_prv =
	loop_cnt_prv = 0;

	/*   save input_crs to know if loop consumed input   */
	input_start = *input_crs;

	CHECK_OUTPUT(START, 0, "check start")

	while(EXPR_TYPE(expr_crs) != PTN_END)
	{
		/*   end of input expression   */
		if(EXPR_TYPE(expr_crs) == PTN_END_OF_INPUT)
		if(*input_crs * input_dir >= input_minmax * input_dir)
		{
			if(not)
				CHECK_OUTPUT(RETURN, 0, "end of input failed:  no input and not ")
			else
				CHECK_OUTPUT(RETURN, 1, "end of input passed:  no input")
			return !not;
		}
		else
		{
			if(not)
				CHECK_OUTPUT(RETURN, 1, "end of input passed:  input and not")
			else
				CHECK_OUTPUT(RETURN, 0, "end of input failed:  input")
			return not;
		}

		/*   no more input   */
		if(*input_crs * input_dir >= input_minmax * input_dir)
		{
			switch(EXPR_TYPE(expr_crs))
			{
			case PTN_ATTRIBUTES:
			case PTN_ANY:
			case PTN_CHARS:

				CHECK_OUTPUT(RETURN, 0, "chars failed:  no input")
				return 0;
			}
		}

		switch(EXPR_TYPE(expr_crs))
		{

		case PTN_START:

			expr_crs = EXPR_NXT(expr_crs);
			break;

		case PTN_GROUP:

			CHECK_OUTPUT(SHOW, 0, "group start")
			expr_crs = EXPR_DATA_0(expr_crs);
			break;

		case PTN_NOT:

			CHECK_OUTPUT(SHOW, 0, "not start")
			not = !not;
			expr_crs = EXPR_DATA_0(expr_crs);
			break;

		case PTN_ONE_MORE:
		case PTN_ZERO_MORE:

			/*   check if loop already started   */
			if(expr_crs == loop_crs)
			{
				loop_cnts[EXPR_DATA_1(loop_crs)]++;
				CHECK_OUTPUT(SHOW, 0, "loop again")
			}
			else
			{
				/*   start loop   */
				loop_crs_prv = loop_crs;
				loop_crs = expr_crs;
				loop_cnt_prv = loop_cnts[EXPR_DATA_1(loop_crs)];
				loop_cnts[EXPR_DATA_1(loop_crs)] = 1;

#ifdef PATTERN_OUTPUT_TRACE
				if(EXPR_TYPE(expr_crs) == PTN_ONE_MORE)
					CHECK_OUTPUT(SHOW, 0, "loop+ start")
				else
					CHECK_OUTPUT(SHOW, 0, "loop start")
#endif
			}

			/*   start loop expression   */
			input_crs_prv = *input_crs;
			ret = pattern_check_expression(input, input_crs, input_minmax, input_dir, expr_data, subpatterns, EXPR_DATA_0(expr_crs), not, loop_crs, loop_cnts);
			if(ret)
			{
				CHECK_OUTPUT(RETURN, 1, "loop passed")
				return 1;
			}
			if(EXPR_TYPE(expr_crs) != PTN_ONE_MORE)
				CHECK_OUTPUT(SHOW, 0, "loop failed")
			*input_crs = input_crs_prv;

			/*   check loop count   */
			loop_cnts[EXPR_DATA_1(loop_crs)]--;
			if(EXPR_TYPE(expr_crs) == PTN_ONE_MORE)
			{
				if(loop_cnts[EXPR_DATA_1(loop_crs)] < 1)
				{
					CHECK_OUTPUT(RETURN, 0, "loop+ failed")
					return 0;
				}
				else
					CHECK_OUTPUT(SHOW, 0, "loop+ passed")
			}

			/*   continue after loop   */
			loop_cnts[EXPR_DATA_1(loop_crs)] = loop_cnt_prv;
			loop_crs = loop_crs_prv;

			expr_crs = EXPR_NXT(expr_crs);
			break;

		case PTN_OPTIONAL:

			/*   save current state   */
			input_crs_prv = *input_crs;

			/*   start optional expression   */
			CHECK_OUTPUT(CALL, 0, "option start")
			if(pattern_check_expression(input, input_crs, input_minmax, input_dir, expr_data, subpatterns, EXPR_DATA_0(expr_crs), not, loop_crs, loop_cnts))
			{
				CHECK_OUTPUT(RETURN, 1, "option passed")
				return 1;
			}
			CHECK_OUTPUT(SHOW, 0, "option failed")

			/*   continue after optional expression   */
			*input_crs = input_crs_prv;
			CHECK_OUTPUT(SHOW, 0, "no option start")
			expr_crs = EXPR_NXT(expr_crs);
			break;

		case PTN_ALTERNATE:

			/*   save current state   */
			input_crs_prv = *input_crs;

			/*   start first expression   */
			CHECK_OUTPUT(CALL, 0, "or 1 start")
			if(pattern_check_expression(input, input_crs, input_minmax, input_dir, expr_data, subpatterns, EXPR_DATA_0(expr_crs), not, loop_crs, loop_cnts))
			{
				CHECK_OUTPUT(RETURN, 1, "or 1 passed")
				return 1;
			}
			CHECK_OUTPUT(SHOW, 0, "or 1 failed")

			/*   start second expression (no need to push)   */
			*input_crs = input_crs_prv;
			CHECK_OUTPUT(SHOW, 1, "or 2 start")
			expr_crs = EXPR_DATA_1(expr_crs);
			break;

		case PTN_ANY:

			CHECK_OUTPUT(SHOW, 0, "any")
			*input_crs += input_dir;
			expr_crs = EXPR_NXT(expr_crs);
			break;

		case PTN_ATTRIBUTES:

			ret = pattern_check_attrs(input[*input_crs], EXPR_CONST_DATA(expr_crs));
			if(ret && not)
			{
				CHECK_OUTPUT(RETURN, 0, "attributes failed:  not");
				return 0;
			}
			if(!ret && !not)
			{
				CHECK_OUTPUT(RETURN, 0, "attributes failed");
				return 0;
			}
			CHECK_OUTPUT(SHOW, 0, "attributes passed")
			*input_crs += input_dir;
			expr_crs = EXPR_NXT(expr_crs);
			break;

		case PTN_CHARS:

			ret = pattern_check_chars(input[*input_crs], EXPR_CONST_DATA(expr_crs));
			if(ret && not)
			{
				CHECK_OUTPUT(RETURN, 0, "chars failed:  not");
				return 0;
			}
			if(!ret && !not)
			{
				CHECK_OUTPUT(RETURN, 0, "chars failed");
				return 0;
			}
			CHECK_OUTPUT(SHOW, 0, "chars passed")
			*input_crs += input_dir;
			expr_crs = EXPR_NXT(expr_crs);
			break;

		case PTN_SUBPATTERN:

			if(subpatterns == NULL)
			{
				CHECK_OUTPUT(RETURN, 0, "subpatterns failed:  NULL");
				return 0;
			}

			subpattern = subpattern_find(subpatterns, EXPR_CONST_DATA(expr_crs + 1), EXPR_DATA_0(expr_crs));
			if(!subpattern)
			{
				CHECK_OUTPUT(RETURN, 0, "subpattern failed:  NULL");
				return 0;
			}
			if(subpattern->processing)
			{
				CHECK_OUTPUT(RETURN, 0, "subpattern failed:  recursive");
				return 0;
			}

			/*   call subpattern   */
			subpattern->processing = 1;
			subpattern_level++;
			ret = subpattern_check(input, input_crs, input_minmax, input_dir, subpattern->expr_data, subpatterns);
			subpattern->processing = 0;
			subpattern_level--;
			if(ret && not)
			{
				CHECK_OUTPUT(RETURN, 0, "subpattern failed:  not");
				return 0;
			}
			if(!ret && !not)
			{
				CHECK_OUTPUT(RETURN, 0, "subpattern failed");
				return 0;
			}
			CHECK_OUTPUT(SHOW, 0, "subpattern passed")
			expr_crs = EXPR_NXT(expr_crs);
			break;

		case PTN_END:  break;

		default:

			CHECK_OUTPUT(RETURN, 0, "unknown opcode")
			return 0;
		}

		/*   check end expression    */
		while(EXPR_TYPE(expr_crs) == PTN_END)
		{
			/*   check for end of expressions   */
			if(EXPR_NXT(expr_crs) == PTN_END)
				break;

			expr_crs = EXPR_NXT(expr_crs);

			/*   returning loop   */
			if(EXPR_TYPE(expr_crs) == PTN_ZERO_MORE || EXPR_TYPE(expr_crs) == PTN_ONE_MORE)
			{
				CHECK_OUTPUT(SHOW, 0, "end loop")

				/*   check that loop consumed input   */
				if(*input_crs == input_start)
				{
					CHECK_OUTPUT(RETURN, 0, "loop failed:  did not consume")
					return 0;
				}

				/*   loops do not continue to the next expression   */
				break;
			}

			/*   returning not   */
			if(EXPR_TYPE(expr_crs) == PTN_NOT)
				not = !not;

			expr_crs = EXPR_NXT(expr_crs);
		}
	}

	CHECK_OUTPUT(RETURN, 1, "check passed:  end of expression");
	return 1;
}

static int subpattern_check(
	const Unicode *input,
	int *input_crs,
	const int input_minmax,
	const int input_dir,
	const Unicode *expr_data,
	struct subpattern *subpatterns)
{
	int ret, *loop_cnts;

#ifdef PATTERN_OUTPUT_TRACE
	if(subpattern_level)
		puts("");
	else
		puts("----------------------------------------");
	printf("[%d]\n", *input_crs);
	pattern_print(stdout, expr_data, attrs_chars);
	puts("");
	printf(" ");
	utf16le_output(stdout, input, 0x100);
	puts("");
	for(int i = 0; i <= *input_crs; i++)
		printf(" ");
	if(input_dir > 0)
		puts(">");
	else
		puts("<");
	//pattern_output(expr_data);
	fflush(stdout);
#endif

	loop_cnts = MALLOC(expr_data[1] * sizeof(int));
	if(!loop_cnts)
	{
		LOG_ALLOCATE_FAIL
		return 0;
	}
	memset(loop_cnts, 0, expr_data[1] * sizeof(int));
	ret = pattern_check_expression(input, input_crs, input_minmax, input_dir, expr_data, subpatterns, 2, 0, 0, loop_cnts);
	FREE(loop_cnts);

#ifdef PATTERN_OUTPUT_TRACE
	puts("");
#endif
	return ret;
}

int pattern_check(
	const struct translate *translate_,
	const Unicode *input,
	const int input_start,
	const int input_minmax,
	const int input_dir,
	const Unicode *expr_data,
	const char *attrs_chars_,
	struct subpattern *subpatterns)
{
	int input_crs;

	input_crs = input_start;
	set_attrs_chars(attrs_chars_);
	translate = translate_;
	subpattern_level = 0;
	return subpattern_check(input, &input_crs, input_minmax, input_dir, expr_data, subpatterns);
}

/******************************************************************************/
