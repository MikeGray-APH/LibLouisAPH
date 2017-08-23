/*

LibLouisAPH Braille Translation and Back-Translation Library

Copyright (C) 2017 American Printing House for the Blind, Inc.

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

#include "translate.h"
#include "lookup.h"
#include "utf-convert.h"
#include "utf-output.h"
#include "table-output.h"
#include "log.h"
#include "test.h"

static Unicode *token_crs, *token_nxt;
static int token_len;

/******************************************************************************/

static int test_expect_both(
	FILE *output,
	const struct table *const*tables,
	const int table_cnt,
	const struct conversion *conversion,
	const Unicode *chars,
	const int chars_len,
	const Unicode *dots,
	const int dots_len)
{
	Unicode *forward, *backward;
	int forward_len, backward_len, status;

	backward = NULL;

	forward = MALLOC((dots_len + 1) * sizeof(Unicode));
	memset(forward, 0, (dots_len + 1) * sizeof(Unicode));

	utf16le_output(output, chars, chars_len);
	fputs("   ", output);
	utf16le_output(output, dots, dots_len);
	forward_len = translate_start(forward, dots_len, chars, chars_len, tables, table_cnt, conversion, FORWARD, NULL, NULL, NULL);
	if(forward_len == -1)
	{
		fputs("   FAIL", output);
		status = 0;
		goto free_and_return_status;
	}
	fputs("   ", output);
	utf16le_output(output, forward, forward_len);
	if(!utf16_are_equal(forward, forward_len, dots, dots_len))
	{
		fputs("   FAIL", output);
		status = 0;
		goto free_and_return_status;
	}

	backward = MALLOC((chars_len + 1) * sizeof(Unicode));
	memset(backward, 0, (chars_len + 1) * sizeof(Unicode));
	backward_len = translate_start(backward, chars_len, forward, forward_len, tables, table_cnt, conversion, BACKWARD, NULL, NULL, NULL);
	if(backward_len == -1)
	{
		fputs("   FAIL", output);
		status = 0;
		goto free_and_return_status;
	}
	fputs("   ", output);
	utf16le_output(output, backward, backward_len);
	if(!utf16_are_equal(backward, backward_len, chars, chars_len))
	{
		fputs("   FAIL", output);
		status = 0;
		goto free_and_return_status;
	}

	status = 1;

	free_and_return_status:
	if(forward)
		FREE(forward);
	if(backward)
		FREE(backward);

	fputs("\n", output);
	fflush(output);

	return status;
}

int test_expect_cursor(
	FILE *output,
	const struct table *const*tables,
	const int table_cnt,
	const struct conversion *conversion,
	const enum rule_direction direction,
	const Unicode *chars,
	const int chars_len,
	const Unicode *dots,
	const int dots_len,
	const int cursor_chars,
	const int cursor_dots)
{
	Unicode *trans;
	int trans_len, cursor, status;

	if(direction == BOTH)
		return test_expect_both(output, tables, table_cnt, conversion,chars, chars_len, dots, dots_len);

	if(cursor_chars >= 0)
		cursor = cursor_chars;
	else
		cursor = 0;

	status = 0;

	trans = MALLOC((dots_len + 1) * sizeof(Unicode));
	memset(trans, 0, (dots_len + 1) * sizeof(Unicode));

	utf16le_output(output, chars, chars_len);
	fputs("   ", output);
	utf16le_output(output, dots, dots_len);
	trans_len = translate_start(trans, dots_len, chars, chars_len, tables, table_cnt, conversion, direction, NULL, NULL, &cursor);
	if(trans_len == -1)
	{
		fputs("FAIL", output);
		goto free_and_return_status;
	}

	fputs("   ", output);
	utf16le_output(output, trans, trans_len);
	if(!utf16_are_equal(trans, trans_len, dots, dots_len))
	{
		fputs("   FAIL", output);
		goto free_and_return_status;
	}

	if(cursor_chars >= 0)
	{
		fprintf(output, "   %d:%d", cursor_chars, cursor);
		if(cursor != cursor_dots)
		{
			fprintf(output, "!=%d   FAIL", cursor_dots);
			goto free_and_return_status;
		}
	}

	status = 1;

	free_and_return_status:
	FREE(trans);

	fputs("\n", output);
	fflush(output);

	return status;
}

static int test_expect_mapping_both(
	FILE *output,
	const struct table *const*tables,
	const int table_cnt,
	const struct conversion *conversion,
	const Unicode *chars,
	const int chars_len,
	const Unicode *dots,
	const int dots_len,
	const int *chars_to_dots,
	const int *dots_to_chars)
{
	if(!test_expect_mapping(
		output,
		tables, table_cnt, conversion,
		FORWARD,
		chars, chars_len, dots, dots_len,
		chars_to_dots, dots_to_chars))
		return 0;

	if(!test_expect_mapping(
		output,
		tables, table_cnt, conversion,
		BACKWARD,
		dots, dots_len, chars, chars_len,
		dots_to_chars, chars_to_dots))
		return 0;

	return 1;
}

int test_expect_mapping(
	FILE *output,
	const struct table *const*tables,
	const int table_cnt,
	const struct conversion *conversion,
	const enum rule_direction direction,
	const Unicode *chars,
	const int chars_len,
	const Unicode *dots,
	const int dots_len,
	const int *chars_to_dots_map,
	const int *dots_to_chars_map)
{
	Unicode *trans, *uchars;
	int *trans_chars_to_dots_map, *trans_dots_to_chars_map;
	int trans_len, status, i;

	uchars = NULL;

	if(direction == BOTH)
		return test_expect_mapping_both(output, tables, table_cnt, conversion, chars, chars_len, dots, dots_len, chars_to_dots_map, dots_to_chars_map);

	status = 0;

	trans = MALLOC((dots_len + 1) * sizeof(Unicode));
	trans_chars_to_dots_map = MALLOC((chars_len + 1) * sizeof(int));
	trans_dots_to_chars_map = MALLOC((dots_len + 1) * sizeof(int));
	memset(trans, 0, (dots_len + 1) * sizeof(Unicode));
	memset(trans_chars_to_dots_map, 0, (chars_len + 1) * sizeof(int));
	memset(trans_dots_to_chars_map, 0, (dots_len + 1) * sizeof(int));

	trans_len = translate_start(trans, dots_len, chars, chars_len, tables, table_cnt, conversion, direction, trans_chars_to_dots_map, trans_dots_to_chars_map, NULL);
	if(trans_len == -1)
	{
		fputs("FAIL", output);
		goto free_and_return_status;
	}
	uchars = MALLOC((chars_len + 1) * sizeof(Unicode));
	utf16_copy(uchars, chars, chars_len + 1);
	for(i = 0; i < chars_len; i++)
		fprintf(output, "%x", (i % 16));
	fputs("\n", output);
	table_convert_markers(tables[table_cnt - 1], uchars, chars_len);
	utf16le_output(output, uchars, chars_len);
	fputs("\n", output);

	for(i = 0; i < chars_len; i++)
	if(trans_chars_to_dots_map[i] == -1)
		fputs("_", output);
	else
		fprintf(output, "%x", (trans_chars_to_dots_map[i] % 16));
	fputs("\n", output);
	for(i = 0; i < chars_len; i++)
	if(chars_to_dots_map[i] == -1)
		fputs("_", output);
	else
		fprintf(output, "%x", (chars_to_dots_map[i] % 16));
	fputs("\n", output);

	fputs("\n", output);

	for(i = 0; i < trans_len; i++)
		fprintf(output, "%x", (i % 16));
	fputs("\n", output);
	utf16le_output(output, dots, dots_len);
	fputs("\n", output);
	table_convert_markers(tables[table_cnt - 1], trans, trans_len);
	utf16le_output(output, trans, trans_len);
	fputs("\n", output);

	for(i = 0; i < trans_len; i++)
	if(trans_dots_to_chars_map[i] == -1)
		fputs("_", output);
	else
		fprintf(output, "%x", (trans_dots_to_chars_map[i] % 16));
	fputs("\n", output);
	for(i = 0; i < trans_len; i++)
	if(dots_to_chars_map[i] == -1)
		fputs("_", output);
	else
		fprintf(output, "%x", (dots_to_chars_map[i] % 16));
	fputs("\n", output);

	if(!utf16_are_equal(trans, trans_len, dots, dots_len))
	{
		fputs("FAIL", output);
		goto free_and_return_status;
	}

	for(i = 0; i < chars_len; i++)
	if(trans_chars_to_dots_map[i] != chars_to_dots_map[i])
	{
		fputs("FAIL", output);
		goto free_and_return_status;
	}

	for(i = 0; i < dots_len; i++)
	if(trans_dots_to_chars_map[i] != dots_to_chars_map[i])
	{
		fputs("FAIL", output);
		goto free_and_return_status;
	}

	status = 1;

	free_and_return_status:
	if(uchars)
		FREE(uchars);
	FREE(trans);
	FREE(trans_chars_to_dots_map);
	FREE(trans_dots_to_chars_map);

	fputs("\n", output);
	fflush(output);

	return status;
}

/******************************************************************************/

/* Functions for parsing lines of text.  Must make sure that the uchars used to
 * initialize parsing is terminated with two NULL characters.
 *
 * Unlike in compile.c, parsing will check for double quotes for tokens
 * containing whitespace.
*/

static int token_parse(void)
{
	ASSERT(token_nxt)
	if(!(*token_nxt))
		return 0;

	token_crs = token_nxt;

	if(token_crs[0] == u'"')
	{
		token_crs++;
		token_nxt++;
		for(token_len = 0; *token_nxt != u'"'; token_nxt++)
		{
			if(!(*token_nxt))
				return 0;

			if(*token_nxt == u'\\')
			{
				token_nxt++;
				if(!(*token_nxt))
					return 0;
				token_len += 2;
			}
			else
				token_len++;
		}
	}
	else
		for(token_len = 0; !is_space(*token_nxt); token_nxt++)
		if(!(*token_nxt))
			return 1;
		else
			token_len++;

	*token_nxt = 0;
	for(token_nxt++; is_space(*token_nxt); token_nxt++);

	return 1;
}

static int token_init(Unicode *uchars)
{
	if(!uchars)
		return 0;

	for(token_nxt = uchars; is_space(*token_nxt); token_nxt++);
	if(!(*token_nxt))
		return 0;

	return token_parse();
}

/******************************************************************************/

static inline int token_convert_escapes(const struct table *table)
{
	token_len = table_convert_escape_markers(table, token_crs, token_len);
	return token_len = utf16le_convert_escapes(token_crs, token_len);
}

static int utf16_are_equal_ambiguous(const Unicode *uchars0, const int uchars0_len, const Unicode *uchars1, const int uchars1_len)
{
	int i;

	if(uchars0_len != uchars1_len)
		return 0;
	for(i = 0; i < uchars0_len; i++)
	if(
	   (
	       (uchars0[i] == u'"' || uchars0[i] == u'“')
	    && (uchars1[i] == u'"' || uchars1[i] == u'“')
	   )
	   ||
	   (
	       (uchars0[i] == u'"' || uchars0[i] == u'”')
	    && (uchars1[i] == u'"' || uchars1[i] == u'”')
	   )
	   ||
	   (
	       (uchars0[i] == u'\'' || uchars0[i] == u'’')
	    && (uchars1[i] == u'\'' || uchars1[i] == u'’')
	   )
	   ||
	   (
	       (uchars0[i] == u'\'' || uchars0[i] == u'‘')
	    && (uchars1[i] == u'\'' || uchars1[i] == u'‘')
	   )
	   ||
	   (
	       (uchars0[i] == u'-' || uchars0[i] == u'‐' || uchars0[i] == u'‑' || uchars0[i] == u'‒' || uchars0[i] == u'–' || uchars0[i] == u'—' || uchars0[i] == u'―')
	    && (uchars1[i] == u'-' || uchars1[i] == u'‐' || uchars1[i] == u'‑' || uchars1[i] == u'‒' || uchars1[i] == u'–' || uchars1[i] == u'—' || uchars1[i] == u'―')
	   )
	   ||
	   (
	       (uchars0[i] == u'Σ' || uchars0[i] == u'∑')
	    && (uchars1[i] == u'Σ' || uchars1[i] == u'∑')
	   )
	)
		continue;
	else if(uchars0[i] != uchars1[i])
		return 0;
	return 1;
}

/******************************************************************************/

static int remove_soft(const Unicode *uchars, const int uchars_len, const int at)
{
	Unicode soft;
	int i;

	soft = uchars[at];
	for(i = at + 1; i < uchars_len; i++)
	if(uchars[i] == soft)
		break;

	return i + 1;
}

static int strip_input(Unicode *original, const Unicode *uchars, const int uchars_len, const struct table *table)
{
	int off, crs;

	crs =
	off = 0;
	while(off < uchars_len)
	{
		if(   uchars[off] == table->marker_user
		   || uchars[off] == table->marker_begin
		   || uchars[off] == table->marker_end
		   || uchars[off] == table->marker_modifier
		   || uchars[off] == table->marker_hard
		   || uchars[off] == table->marker_soft
		   || uchars[off] == table->marker_internal)
			off = remove_soft(uchars, uchars_len, off);

		/*   numeric space   */
		else if(uchars[off] == u'\u2810')
		{
			original[crs++] = u' ';
			off++;
		}
		else
			original[crs++] = uchars[off++];
	}

	return crs;
}

/******************************************************************************/

static Unicode* test_input_uchars(
	FILE *output,
	int *trans_len_ref,
	const struct table *table,
	const struct conversion *conversion,
	const Unicode *uchars,
	const int uchars_len,
	const enum rule_direction direction)
{
	Unicode *trans;
	int trans_len;

	trans_len = uchars_len * 31;
	trans  = MALLOC((trans_len + 1) * sizeof(Unicode));
	memset(trans, 0, (trans_len + 1) * sizeof(Unicode));

	*trans_len_ref = translate_start(trans, trans_len, uchars, uchars_len, &table, 1, conversion, direction, NULL, NULL, NULL);
	if(*trans_len_ref == -1)
	{
		fputs("FAIL\n", output);
		FREE(trans);
		return NULL;
	}
	if(*trans_len_ref == trans_len)
	{
		fputs("FAIL:  buffer too small\n", output);
		FREE(trans);
		return NULL;
	}

	return trans;
}

/******************************************************************************/

#define INPUT_LINE_MAX 0x1000

int test_back_from_file(
	FILE *output,
	const char *file_name,
	const struct table *table,
	const struct conversion *conversion,
	const int output_pass_fail)
{
	FILE *file;
	Unicode token_line[INPUT_LINE_MAX], *uchars, *original, *trans, *reverse;
	char cchars[INPUT_LINE_MAX];
	int cchars_len, uchars_len, original_len, trans_len, reverse_len, line;
	int pass, fail;

	if(!table)
		return 1;

	if(output != stdout)
	{
		printf("test_back:         %s:  ", file_name);
		fflush(stdout);
	}

	fprintf(output, "test_back:         %s\n", file_name);

	file = fopen(file_name, "r");
	if(!file)
	{
		fprintf(output, "FAIL:  unable to open %s\n\n", file_name);
		fail = 1;
		goto return_close;
	}

	pass =
	fail = 0;

	line = 0;
	while(fgets(cchars, INPUT_LINE_MAX, file))
	{
		if(!strncmp(cchars, ".end", 4))
			break;

		line++;
		//fprintf(output, "%7d   %s", line, cchars);fflush(output);

		if(cchars[0] == '#')
		{
			//if(cchars[1] != '#')
			//	fprintf(output, "%s", cchars);
			continue;
		}

		/*   trim return whitespace at end   */
		for(cchars_len = strlen(cchars); cchars_len > 0; cchars_len--)
		if(cchars[cchars_len - 1] == '\n' || cchars[cchars_len - 1] == '\r')
			cchars[cchars_len - 1] = 0;
		else
			break;
		if(cchars_len <= 0)
			continue;

		uchars_len = utf8_convert_to_utf16le(token_line, INPUT_LINE_MAX, cchars, INPUT_LINE_MAX);
		uchars_len = table_convert_escape_markers(table, token_line, uchars_len);
		uchars_len = utf16le_convert_escapes(token_line, uchars_len);
		uchars = token_line;

		original_len = uchars_len;
		original = MALLOC((original_len + 1) * sizeof(Unicode));
		memset(original, 0, (original_len + 1) * sizeof(Unicode));
		original_len = strip_input(original, uchars, uchars_len, table);

		trans = test_input_uchars(output, &trans_len, table, conversion, uchars, uchars_len, FORWARD);
		if(!trans)
		{
			fprintf(output, "TEST ERROR:  %s\n\n", cchars);
			fail = -1;
			goto return_close;
		}

		reverse = test_input_uchars(output, &reverse_len, table, conversion, trans, trans_len, BACKWARD);
		if(!reverse)
		{
			fprintf(output, "TEST ERROR:  %s\n\n", cchars);
			fail = -1;
			goto return_close;
		}
		if(output_pass_fail)
		{
			if(!utf16_are_equal_ambiguous(reverse, reverse_len, original, original_len))
			{
				fail++;
				fputs("-  ", output);
			}
			else
			{
				pass++;
				fputs("+  ", output);
			}

			table_convert_markers(table, uchars, uchars_len);
			utf16le_output(output, uchars, uchars_len);
			if(!utf16_are_equal(original, original_len, uchars, uchars_len))
			{
				fputs("   ", output);
				utf16le_output(output, original, original_len);
			}
			fputs("   ", output);
			utf16le_output(output, trans, trans_len);
			fputs("   ", output);
			utf16le_output(output, reverse, reverse_len);
			fputs("\n", output);
			fflush(output);
		}
		else
		{
			if(!utf16_are_equal_ambiguous(reverse, reverse_len, original, original_len))
			{
				fail++;

				table_convert_markers(table, uchars, uchars_len);
				utf16le_output(output, uchars, uchars_len);
				if(!utf16_are_equal(original, original_len, uchars, uchars_len))
				{
					fputs("   ", output);
					utf16le_output(output, original, original_len);
				}
				fputs("   ", output);
				utf16le_output(output, trans, trans_len);
				fputs("   ", output);
				utf16le_output(output, reverse, reverse_len);
				fputs("\n", output);
				fflush(output);
			}
			else
				pass++;
		}

		FREE(original);
		FREE(trans);
		FREE(reverse);
	}

	if(fail)
		fprintf(output, "pass:   %d\nfail:   %d\n        %d\n\n", pass, fail, pass + fail);

	return_close:
	if(file)
		fclose(file);

	if(output != stdout)
	if(!fail)
		printf("PASS  %d\n", pass);
	else if(fail > 0)
		printf("FAIL  %d\n", fail);
	else
		puts("ERROR");

	return !fail;
}

int test_expect_from_file(
	FILE *output,
	const char *file_name,
	const struct table *table,
	const struct conversion *conversion,
	const int output_pass_fail,
	const int do_back)
{
	FILE *file;
	Unicode token_line[INPUT_LINE_MAX], *uchars, *original, *expect, *trans, *reverse;
	char cchars[INPUT_LINE_MAX];
	int cchars_len, uchars_len, original_len, expect_len, trans_len, reverse_len, line;
	int pass, fail;

	if(!table)
		return 1;

	if(output != stdout)
	{
		if(do_back)
			printf("test_expect back:  %s:  ", file_name);
		else
			printf("test_expect:       %s:  ", file_name);
		fflush(stdout);
	}

	if(do_back)
		fprintf(output, "test_expect back:  %s\n", file_name);
	else
		fprintf(output, "test_expect:       %s\n", file_name);

	file = fopen(file_name, "r");
	if(!file)
	{
		fprintf(output, "FAIL:  unable to open %s\n\n", file_name);
		fail = 1;
		goto return_close;
	}

	pass =
	fail = 0;

	reverse = NULL;
	line = 0;
	while(fgets(cchars, INPUT_LINE_MAX, file))
	{
		if(!strncmp(cchars, ".end", 4))
			break;

		line++;
		//fprintf(output, "%7d   %s", line, cchars);fflush(output);

		if(cchars[0] == '#')
		{
			//if(cchars[1] != '#')
			//	fprintf(output, "%s", cchars);
			continue;
		}

		/*   trim return whitespace at end   */
		for(cchars_len = strlen(cchars); cchars_len > 0; cchars_len--)
		if(cchars[cchars_len - 1] == '\n' || cchars[cchars_len - 1] == '\r')
			cchars[cchars_len - 1] = 0;
		else
			break;
		if(cchars_len <= 0)
			continue;

		memset(token_line, 0, INPUT_LINE_MAX * sizeof(Unicode));
		utf8_convert_to_utf16le(token_line, INPUT_LINE_MAX - 1, cchars, INPUT_LINE_MAX);

		if(!token_init(token_line))
			continue;
		token_convert_escapes(table);

		uchars = token_crs;
		uchars_len = token_len;

		original_len = uchars_len;
		original = MALLOC((original_len + 1) * sizeof(Unicode));
		memset(original, 0, (original_len + 1) * sizeof(Unicode));
		original_len = strip_input(original, uchars, uchars_len, table);

		token_parse();
		if(!token_len)
		{
			fprintf(stderr, "TEST ERROR:  %d:  %s\n\n", line, cchars);
			FREE(original);
			continue;
		}
		token_convert_escapes(table);

		expect = token_crs;
		expect_len = token_len;

		trans = test_input_uchars(output, &trans_len, table, conversion, uchars, uchars_len, FORWARD);
		if(!trans)
		{
			fprintf(output, "TEST ERROR:  %s\n\n", cchars);
			FREE(original);
			fail = -1;
			goto return_close;
		}

		reverse_len = 0;

		if(do_back)
		{
			reverse = test_input_uchars(output, &reverse_len, table, conversion, trans, trans_len, BACKWARD);
			if(!reverse)
			{
				fprintf(output, "TEST ERROR:  %s\n\n", cchars);
				FREE(original);
				FREE(trans);
				fail = -1;
				goto return_close;
			}
		}
		if(output_pass_fail)
		{
			if(   !utf16_are_equal(expect, expect_len, trans, trans_len)
			   || ((do_back) && !utf16_are_equal_ambiguous(reverse, reverse_len, original, original_len)))
			{
				fail++;
				fputs("-  ", output);
			}
			else
			{
				pass++;
				fputs("+  ", output);
			}
			table_convert_markers(table, uchars, uchars_len);
			utf16le_output(output, uchars, uchars_len);
			if(!utf16_are_equal(original, original_len, uchars, uchars_len))
			{
				fputs("   ", output);
				utf16le_output(output, original, original_len);
			}
			fputs("   ", output);
			utf16le_output(output, expect, expect_len);
			fputs("   ", output);
			utf16le_output(output, trans, trans_len);
			if(reverse)
			{
				fputs("   ", output);
				utf16le_output(output, reverse, reverse_len);
			}
			fputs("\n", output);
			fflush(output);
		}
		else
		{
			if(   !utf16_are_equal(expect, expect_len, trans, trans_len)
			   || ((do_back) && !utf16_are_equal_ambiguous(reverse, reverse_len, original, original_len)))
			{
				fail++;

				table_convert_markers(table, uchars, uchars_len);
				utf16le_output(output, uchars, uchars_len);
				if(!utf16_are_equal_ambiguous(original, original_len, uchars, uchars_len))
				{
					fputs("   ", output);
					utf16le_output(output, original, original_len);
				}
				fputs("   ", output);
				utf16le_output(output, expect, expect_len);
				fputs("   ", output);
				utf16le_output(output, trans, trans_len);
				if(reverse)
				{
					fputs("   ", output);
					utf16le_output(output, reverse, reverse_len);
				}
				fputs("\n", output);
				fflush(output);
			}
			else
				pass++;
		}

		FREE(original);
		FREE(trans);
		if(reverse)
			FREE(reverse);
	}

	if(fail)
		fprintf(output, "pass:   %d\nfail:   %d\n        %d\n\n", pass, fail, pass + fail);

	return_close:
	if(file)
		fclose(file);

	if(output != stdout)
	if(!fail)
		printf("PASS  %d\n", pass);
	else if(fail > 0)
		printf("FAIL  %d\n", fail);
	else
		puts("ERROR");

	return !fail;
}

/******************************************************************************/
