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

#include "utf-convert.h"
#include "table.h"
#include "conversion.h"
#include "pattern.h"
#include "lookup.h"
#include "log.h"

#define INPUT_LINE_MAX     1024
#define INCLUDE_DEPTH_MAX     8

static struct table *table;
static const char *table_file_names[INCLUDE_DEPTH_MAX];
static int include_depth, table_file_lines[INCLUDE_DEPTH_MAX];

static unsigned int rule_attrs;
static Unicode token_line[INPUT_LINE_MAX];
static Unicode *token_crs, *token_nxt;
static int token_len, token_int;

static int token_compile(void);

/******************************************************************************/

/* Functions for parsing lines of text.  Must make sure that the uchars used to
 * initialize parsing is terminated with two NULL characters.
*/

static int token_parse(void)
{
	ASSERT(token_nxt)
	if(!(*token_nxt))
		return 0;

	token_crs = token_nxt;
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

static int token_is_equal(const char *cchars, const int cchars_len)
{
	return utf16_is_equal_cchars(token_crs, token_len, cchars, cchars_len);
}

static inline int token_convert_escapes(void)
{
	token_len = table_convert_escape_markers(table, token_crs, token_len);
	return token_len = utf16le_convert_escapes(token_crs, token_len);
}

/* Returns length of converted characters or -1 if invalid character is found.
 *
 * Unicode braille is allowed, and does not need to be separated with dashes.
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
 *    1-02-3          ->  1-2-3
 *    1-20-3          ->  1-0-3
 *    1-1234567802-3  ->  1-2-3
*/
static int convert_to_dots(Unicode *uchars, const int uchars_len)
{
	Unicode cell;
	int crs, off;

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
			return -1;
	}

	if(cell)
	{
		uchars[crs++] = cell | 0x2800;
		cell = 0;
	}

	return crs;
}

static inline int token_convert_to_dots(void)
{
	return token_len = convert_to_dots(token_crs, token_len);
}

static int convert_with_dots(Unicode *uchars, const int uchars_len)
{
	int esc, crs, off, cells_len, cells_end, i;

	if(uchars_len == 1 && uchars[0] == u';')
		return 1;

	esc =
	crs =
	off = 0;
	while(off < uchars_len)
	{
		if(uchars[off] == u'\\')
		{
			/*   deal with escaped back slash   */
			if(esc)
				uchars[crs++] = uchars[off++];
			else if(uchars[off + 1] == u';')
			{
				off++;

				/*   find next ;   */
				for(cells_end = off + 1; cells_end < uchars_len; cells_end++)
				if(uchars[cells_end] == u';')
					break;
				if(cells_end >= uchars_len)
					return 0;

				/*   ;;, no digits   */
				if(cells_end == off + 1)
					off = cells_end + 1;
				else
				{
					cells_len = convert_to_dots(&uchars[off + 1], cells_end - off - 1);
					if(cells_len == -1)
						return -1;

					for(i = 0; i < cells_len; i++)
						uchars[crs + i] = uchars[off + i + 1];

					off = cells_end + 1;
					crs += cells_len;
				}
			}
			else
			{
				uchars[crs++] = uchars[off++];
				esc = 1;
				continue;
			}
		}
		else
			uchars[crs++] = uchars[off++];
		esc = 0;
	}

	uchars[crs] = 0;
	return crs;
}

static int token_convert_escapes_with_dots(void)
{
	token_len = convert_with_dots(token_crs, token_len);
	return token_convert_escapes();
}

/******************************************************************************/

static int compile_attrs_chars(void)
{
	int i;

	if(!token_parse())
	{
		log_message(LOG_ERROR, "%s:%d  missing attrs chars", table_file_names[include_depth], table_file_lines[include_depth]);
		return 0;
	}

	if(token_len > 32)
	{
		log_message(LOG_ERROR, "%s:%d  too many attrs chars", table_file_names[include_depth], table_file_lines[include_depth]);
		return 0;
	}

	for(i = 0; i < token_len; i++)
		table->attrs_chars[i] = (char)token_crs[i];

	return 1;
}

static int compile_control(void)
{
	Unicode *type;
	int type_len;

	if(!token_parse())
	{
		log_message(LOG_ERROR, "%s:%d  missing control type", table_file_names[include_depth], table_file_lines[include_depth]);
		return 0;
	}

	type = token_crs;
	type_len = token_len;

	if(!token_parse())
	{
		log_message(LOG_ERROR, "%s:%d  missing control character", table_file_names[include_depth], table_file_lines[include_depth]);
		return 0;
	}
	token_convert_escapes();

	     if(utf16_are_equal(u"user", 4, type, type_len))
		table->marker_user = *token_crs;
	else if(utf16_are_equal(u"begin", 5, type, type_len))
		table->marker_begin = *token_crs;
	else if(utf16_are_equal(u"end", 3, type, type_len))
		table->marker_end = *token_crs;
	else if(utf16_are_equal(u"modifier", 8, type, type_len))
		table->marker_modifier = *token_crs;
	else if(utf16_are_equal(u"hard", 4, type, type_len))
		table->marker_hard = *token_crs;
	else if(utf16_are_equal(u"soft", 4, type, type_len))
		table->marker_soft = *token_crs;
	else if(utf16_are_equal(u"internal", 8, type, type_len))
		table->marker_modifier = *token_crs;
	else
	{
		log_message_with_token(LOG_ERROR, token_crs, token_len, "%s:%d  invalid control type %TOKEN", table_file_names[include_depth], table_file_lines[include_depth]);
		return 0;
	}

	return 1;
}

static int compile_config(void)
{
	if(!token_parse())
	{
		log_message(LOG_ERROR, "%s:%d  empty config", table_file_names[include_depth], table_file_lines[include_depth]);
		return 0;
	}

	if(token_is_equal("attrs_chars", 11))
		return compile_attrs_chars();
	if(token_is_equal("control", 7))
		return compile_control();

	return 1;
}

/******************************************************************************/

struct variable
{
	struct variable *nxt;
	Unicode *uchars;
	int uchars_len;
	unsigned int value;
};

static struct variable *variables;

static int var_enum;

static void variable_free(struct variable *var)
{
	if(!var)
		return;

	variable_free(var->nxt);
	ASSERT(var->uchars)
	FREE(var->uchars);
	FREE(var);
}

static struct variable* variable_find(const Unicode *uchars, const int uchars_len)
{
	struct variable *var;

	var = variables;
	while(var)
	if(utf16_are_equal(uchars, uchars_len, var->uchars, var->uchars_len))
		break;
	else
		var = var->nxt;

	return var;
}

static struct variable* variable_add(const Unicode *uchars, const int uchars_len, const int value)
{
	struct variable *var;

	var = MALLOC(sizeof(struct variable));
	LOG_ALLOCATE_FAIL_RETURN_NULL(var)

	var->uchars = MALLOC((uchars_len + 1) * sizeof(Unicode));
	if(!var->uchars)
	{
		LOG_ALLOCATE_FAIL
		FREE(var);
		return 0;
	}
	var->uchars_len = uchars_len;
	utf16_copy(var->uchars, uchars, uchars_len + 1);

	var->value = value;

	var->nxt = variables;
	variables = var;

	return var;
}

static int token_convert_to_int(void)
{
	struct variable *var;

	switch(token_crs[0])
	{
	case u'0':  case u'1':  case u'2':  case u'3':  case u'4':
	case u'5':  case u'6':  case u'7':  case u'8':  case u'9':

		token_int = utf16le_convert_to_int(token_crs, token_len);
		return 1;

	case u'$':

		var = variable_find(&token_crs[1], token_len - 1);
		if(!var)
		{
			log_message_with_token(LOG_ERROR, &token_crs[1], token_len - 1, "%s:%d  variable $%TOKEN not found", table_file_names[include_depth], table_file_lines[include_depth]);
			return 0;
		}
		token_int = var->value;
		return 1;

	case u'b':

		if(token_len < 3)
			break;
		if(token_crs[1] != u'i' || token_crs[2] != u't')
			break;
		if(token_len < 5)
			token_int = BIT(token_crs[3] - u'0');
		else
			token_int = BIT(((token_crs[3] - u'0') * 10) + (token_crs[4] - u'0'));
		return 1;
	}

	log_message_with_token(LOG_ERROR, token_crs, token_len, "%s:%d  invalid value %TOKEN", table_file_names[include_depth], table_file_lines[include_depth]);
	return 0;
}

static int compile_set(void)
{
	Unicode *var_name;
	int var_len, value;

	if(!token_parse())
		return 0;

	token_convert_escapes();

	if(token_crs[0] == u'=')
	{
		if(token_parse())
			var_enum = utf16le_convert_to_int(token_crs, token_len);
		else
			var_enum = 0;

		return 1;
	}

	var_name = token_crs;
	var_len = token_len;

	if(token_parse())
	{
		if(token_convert_to_int())
			value = token_int;
		else
			return 0;
	}
	else
		value = var_enum++;

	if(!variable_add(var_name, var_len, value))
		return 0;

	return 1;
}

/******************************************************************************/

static int mode_compile(struct mode *mode)
{
	int i;

	if(!token_parse())
		goto return_missing;

	memset(mode, 0, sizeof(struct mode));

	/*   begin   */
	token_convert_to_dots();
	if(token_len >= INDICATOR_MAX - 1)
		goto return_too_long;
	if(token_len < 0)
		goto return_invalid_uchar;
	if(!(token_crs[0] == u'-' && token_len == 1))
	{
		for(i = 0; i < token_len; i++)
			mode->begin[i] = token_crs[i];
		mode->begin[token_len] = 0;
		mode->begin_len = token_len;
	}

	if(!token_parse())
		goto return_missing;

	/*   end   */
	token_convert_to_dots();
	if(token_len >= INDICATOR_MAX - 1)
		goto return_too_long;
	if(token_len < 0)
		goto return_invalid_uchar;
	if(!(token_crs[0] == u'-' && token_len == 1))
	{
		for(i = 0; i < token_len; i++)
			mode->end[i] = token_crs[i];
		mode->end[token_len] = 0;
		mode->end_len = token_len;
	}

	/*   short form   */
	if(!token_parse())
		return 1;

	/*   word   */
	token_convert_to_dots();
	if(token_len >= INDICATOR_MAX - 1)
		goto return_too_long;
	if(token_len < 0)
		goto return_invalid_uchar;
	if(!(token_crs[0] == u'-' && token_len == 1))
	{
		for(i = 0; i < token_len; i++)
			mode->word[i] = token_crs[i];
		mode->word[token_len] = 0;
		mode->word_len = token_len;
	}

	if(!token_parse())
		goto return_missing;

	/*   term   */
	token_convert_to_dots();
	if(token_len >= INDICATOR_MAX - 1)
		goto return_too_long;
	if(token_len < 0)
		goto return_invalid_uchar;
	if(!(token_crs[0] == u'-' && token_len == 1))
	{
		for(i = 0; i < token_len; i++)
			mode->term[i] = token_crs[i];
		mode->term[token_len] = 0;
		mode->term_len = token_len;
	}

	if(!token_parse())
		goto return_missing;

	/*   symbol   */
	token_convert_to_dots();
	if(token_len >= INDICATOR_MAX - 1)
		goto return_too_long;
	if(token_len < 0)
		goto return_invalid_uchar;
	if(!(token_crs[0] == u'-' && token_len == 1))
	{
		for(i = 0; i < token_len; i++)
			mode->symbol[i] = token_crs[i];
		mode->symbol[token_len] = 0;
		mode->symbol_len = token_len;
	}

	/*   passage length   */
	if(token_parse())
	if(token_convert_to_int())
		mode->passage_len = token_int;
	else
		return 0;

	return 1;

	return_missing:
	log_message(LOG_ERROR, "%s:%d  missing indicators", table_file_names[include_depth], table_file_lines[include_depth]);
	return 0;

	return_invalid_uchar:
	log_message(LOG_ERROR, "%s:%d  invalid dot character", table_file_names[include_depth], table_file_lines[include_depth]);
	return 0;

	return_too_long:
	log_message(LOG_ERROR, "%s:%d  indicator too long", table_file_names[include_depth], table_file_lines[include_depth]);
	return 0;
}

static int compile_mode(void)
{
	struct mode mode_auto, *mode;
	Unicode *name;
	int name_len;

	if(!token_parse())
	{
		log_message(LOG_ERROR, "%s:%d  missing indicator name", table_file_names[include_depth], table_file_lines[include_depth]);
		return 0;
	}

	token_convert_escapes();
	name = token_crs;
	name_len = token_len;

	if(!mode_compile(&mode_auto))
		return 0;

	if(utf16_is_equal_cchars(name, name_len, "nocontract", 10))
	{
		table->nocontract = mode_auto;
		table->nocontract_set = 1;
		ASSERT(!table->nocontract.nxt)
		return 1;
	}
	if(utf16_is_equal_cchars(name, name_len, "capital", 7))
	{
		table->capital = mode_auto;
		table->capital_set = 1;
		ASSERT(!table->capital.nxt)
		return 1;
	}
	if(utf16_is_equal_cchars(name, name_len, "numeric", 7))
	{
		table->numeric = mode_auto;
		table->numeric_set = 1;
		ASSERT(!table->numeric.nxt)
		return 1;
	}

	mode_auto.name = MALLOC((name_len + 1) * sizeof(Unicode));
	if(!mode_auto.name)
	{
		LOG_ALLOCATE_FAIL
		return 0;
	}
	utf16_copy(mode_auto.name, name, name_len + 1);
	mode_auto.name_len = name_len;

	mode = mode_allocate();
	if(!mode)
	{
		LOG_ALLOCATE_FAIL
		FREE(mode_auto.name);
		return 0;
	}
	*mode = mode_auto;

	mode->id = table->emphases_cnt++;

	mode->nxt = table->emphases;
	table->emphases = mode;

	return 1;
}

/******************************************************************************/

static unsigned int chars_scan_bits(void)
{
	unsigned int bit;

	bit = 0;
	while(token_parse())
	{
		if(token_crs[0] == u'#' && token_len == 1)
			break;
		else if(token_convert_to_int())
			bit |= token_int;
	}

	return bit;
}

static int compile_chars(void)
{
	struct unichar *unichar;
	Unicode *uchars;
	unsigned int uchars_len, bit, i;

	if(!token_parse())
	{
		log_message(LOG_ERROR, "%s:%d  missing characters", table_file_names[include_depth], table_file_lines[include_depth]);
		return 0;
	}

	token_convert_escapes_with_dots();
	if(token_len <= 0)
	{
		log_message(LOG_ERROR, "%s:%d  invalid characters", table_file_names[include_depth], table_file_lines[include_depth]);
		return 0;
	}
	uchars = token_crs;
	uchars_len = token_len;

	bit = chars_scan_bits();
	if(!bit)
		return 0;

	for(i = 0; i < uchars_len; i++)
	{
		unichar = table_find_or_add_unichar(table, uchars[i]);
		if(!unichar)
			return 0;
		unichar->attrs |= bit;
	}

	return 1;
}

/******************************************************************************/

static int compile_join(void)
{
	struct unichar *unichar0, *unichar1;
	int index;
	unsigned int attrs0, attrs1;

	if(!token_parse())
	{
		log_message(LOG_ERROR, "%s:%d  missing join index", table_file_names[include_depth], table_file_lines[include_depth]);
		return 0;
	}
	if(!token_convert_to_int())
		return 0;
	index = token_int;
	if(index < 0 || index > UNICHAR_JOIN_MAX)
	{
		log_message(LOG_ERROR, "%s:%d  join index out of range", table_file_names[include_depth], table_file_lines[include_depth]);
		return 0;
	}

	if(!token_parse())
	{
		log_message(LOG_ERROR, "%s:%d  missing character", table_file_names[include_depth], table_file_lines[include_depth]);
		return 0;
	}
	token_convert_escapes();
	if(token_len != 1)
	{
		log_message(LOG_ERROR, "%s:%d  invalid character", table_file_names[include_depth], table_file_lines[include_depth]);
		return 0;
	}
	unichar0 = table_find_or_add_unichar(table, token_crs[0]);
	if(!unichar0)
		return 0;

	if(!token_parse())
	{
		log_message(LOG_ERROR, "%s:%d  missing character", table_file_names[include_depth], table_file_lines[include_depth]);
		return 0;
	}
	token_convert_escapes();
	if(token_len != 1)
	{
		log_message(LOG_ERROR, "%s:%d  invalid character", table_file_names[include_depth], table_file_lines[include_depth]);
		return 0;
	}

	unichar1 = table_find_or_add_unichar(table, token_crs[0]);
	if(!unichar1)
		return 0;

	attrs0 = 0;
	attrs1 = 0;
	if(token_parse())
	if(token_convert_to_int())
	{
		attrs0 = token_int;

		if(token_parse())
		if(token_convert_to_int())
			attrs1 = token_int;
	}

	unichar0->attrs |= attrs0;
	unichar0->joins[index] = unichar1;
	unichar1->attrs |= attrs1;
	unichar1->joins[index] = unichar0;

	return 1;
}

/******************************************************************************/

static int compile_attrs(void)
{
	if(!token_parse())
		goto return_fail;

	if(token_crs[0] == u'=')
	{
		if(token_len != 1)
			goto return_fail;

		if(!token_parse())
			rule_attrs = 0;
		else if(token_convert_to_int())
			rule_attrs = token_int;
	}
	else if(token_crs[0] == u'+')
	{
		if(token_len != 1)
			goto return_fail;

		if(!token_parse())
			rule_attrs = 0;
		else if(token_convert_to_int())
			rule_attrs |= token_int;
	}
	else if(token_crs[0] == u'-')
	{
		if(token_len != 1)
			goto return_fail;

		if(!token_parse())
			rule_attrs = 0;
		else if(token_convert_to_int())
			rule_attrs &= ~token_int;
	}
	else
		goto return_fail;

	return 1;

	return_fail:
	log_message(LOG_ERROR, "%s:%d  invalid attribute", table_file_names[include_depth], table_file_lines[include_depth]);
	return 0;
}

/******************************************************************************/

static struct filter *rule_filter_forward, *rule_filter_backward;

#define PATTERN_MAX 0x2520

static int compile_pattern(void)
{
	struct subpattern *subpattern;
	Unicode pattern[PATTERN_MAX], *token_tag, *token_src, *tag, *expr_data, *src_data;
	int tag_len, expr_len, src_len;

	tag =
	expr_data =
	src_data = NULL;

	if(!token_parse())
		goto return_fail;

	token_convert_escapes();
	if(token_len <= 0)
	{
		log_message(LOG_ERROR, "%s:%d  invalid pattern name", table_file_names[include_depth], table_file_lines[include_depth]);
		return 0;
	}
	token_tag = token_crs;
	tag_len = token_len;

	if(!token_parse())
		goto return_fail;
	if(token_convert_escapes_with_dots() <= 0)
		goto return_fail;

	token_src = token_crs;
	src_len = token_len;
	expr_len = pattern_compile(pattern, PATTERN_MAX, token_crs, token_len, table->attrs_chars, table->subpatterns);
	if(!expr_len)
		goto return_fail;

	if(token_parse())
	if(token_crs[0] == u'<' && token_len == 1)
		pattern_reverse(pattern);

	tag = MALLOC((tag_len + 1) * sizeof(Unicode));
	if(!tag)
	{
		LOG_ALLOCATE_FAIL
		goto return_fail_free;
	}
	utf16_copy(tag, token_tag, tag_len + 1);

	expr_data = MALLOC((expr_len + 1) * sizeof(Unicode));
	if(!expr_data)
	{
		LOG_ALLOCATE_FAIL
		goto return_fail_free;
	}
	memcpy(expr_data, pattern, (expr_len + 1) * sizeof(Unicode));

	src_data = MALLOC((src_len + 1) * sizeof(Unicode));
	if(!src_data)
	{
		LOG_ALLOCATE_FAIL
		goto return_fail_free;
	}
	utf16_copy(src_data, token_src, src_len + 1);

	subpattern = subpattern_allocate();
	if(!subpattern)
	{
		LOG_ALLOCATE_FAIL
		goto return_fail_free;
	}
	subpattern->nxt = NULL;
	subpattern->processing = 0;
	subpattern->tag = tag;
	subpattern->tag_len = tag_len;
	subpattern->expr_data = expr_data;
	subpattern->expr_len = expr_len;
	subpattern->src_data = src_data;
	subpattern->src_len = src_len;

	subpattern->nxt = table->subpatterns;
	table->subpatterns = subpattern;

	return 1;

	return_fail:
	log_message(LOG_ERROR, "%s:%d  invalid pattern", table_file_names[include_depth], table_file_lines[include_depth]);

	return_fail_free:
	if(tag)
		FREE(tag);
	if(expr_data)
		FREE(expr_data);
	if(src_data)
		FREE(src_data);

	return 0;
}

static int compile_filter(void)
{
	struct filter *filter;
	Unicode pattern[PATTERN_MAX], *name, *before, *after;
	int name_len, before_len, after_len;

	DB_MEMSET(pattern, 0, PATTERN_MAX)
	before =
	after = NULL;

	if(!token_parse())
		goto return_fail;

	token_convert_escapes();
	if(token_len <= 0)
	{
		log_message(LOG_ERROR, "%s:%d  invalid filter name", table_file_names[include_depth], table_file_lines[include_depth]);
		return 0;
	}
	name = token_crs;
	name_len = token_len;

	if(!token_parse())
		goto return_fail;

	if(token_crs[0] == u'-' && token_len == 1)
	{
		before = NULL;
		before_len = 0;
	}
	else
	{
		if(token_convert_escapes_with_dots() <= 0)
			goto return_fail;
		before_len = pattern_compile(pattern, PATTERN_MAX, token_crs, token_len, table->attrs_chars, table->subpatterns);
		if(!before_len)
			goto return_fail;
		pattern_reverse(pattern);
		before = MALLOC((before_len + 1) * sizeof(Unicode));
		if(!before)
		{
			LOG_ALLOCATE_FAIL
			goto return_fail_free;
		}
		memcpy(before, pattern, (before_len + 1) * sizeof(Unicode));
	}

	if(!token_parse())
		goto return_fail;

	if(token_crs[0] == u'-' && token_len == 1)
	{
		after = NULL;
		after_len = 0;
	}
	else
	{
		if(token_convert_escapes_with_dots() <= 0)
			goto return_fail;
		after_len = pattern_compile(pattern, PATTERN_MAX, token_crs, token_len, table->attrs_chars, table->subpatterns);
		if(!after_len)
			goto return_fail;
		after = MALLOC((after_len + 1) * sizeof(Unicode));
		if(!after)
		{
			LOG_ALLOCATE_FAIL
			goto return_fail_free;
		}
		memcpy(after, pattern, (after_len + 1) * sizeof(Unicode));
	}

	filter = filter_allocate();
	if(!filter)
	{
		LOG_ALLOCATE_FAIL
		goto return_fail_free;
	}
	filter->name = MALLOC((name_len + 1) * sizeof(Unicode));
	if(!filter->name)
	{
		LOG_ALLOCATE_FAIL
		goto return_fail_free;
	}
	utf16_copy(filter->name, name, name_len + 1);
	filter->name_len = name_len;

	filter->nxt = NULL;
	filter->before = before;
	filter->before_len = before_len;
	filter->after = after;
	filter->after_len = after_len;

	filter->nxt = table->filters;
	table->filters = filter;

	return 1;

	return_fail:
	log_message(LOG_ERROR, "%s:%d  invalid filter", table_file_names[include_depth], table_file_lines[include_depth]);

	return_fail_free:
	if(before)
		FREE(before);
	if(after)
		FREE(after);

	return 0;
}

static struct filter* filter_find(const Unicode *uchars, const int uchars_len)
{
	struct filter *filter;

	filter = table->filters;
	while(filter)
	if(utf16_are_equal(uchars, uchars_len, filter->name, filter->name_len))
		break;
	else
		filter = filter->nxt;

	return filter;
}

static struct filter* token_get_filter(void)
{
	struct filter *filter;

	filter = filter_find(token_crs, token_len);
	if(!filter)
	{
		log_message_with_token(LOG_ERROR, token_crs, token_len, "%s:%d  filter %TOKEN not found", table_file_names[include_depth], table_file_lines[include_depth]);
		return NULL;
	}
	return filter;
}

/******************************************************************************/

static int compile_use(void)
{
	if(!token_parse())
	{
		rule_filter_forward = NULL;
		rule_filter_backward = NULL;
		return 1;
	}

	if(token_is_equal("-", 1))
		rule_filter_forward = NULL;
	else if(!token_is_equal("=", 1))
		rule_filter_forward = token_get_filter();

	if(!token_parse())
	{
		rule_filter_backward = NULL;
		return 1;
	}

	if(token_is_equal("-", 1))
		rule_filter_backward = NULL;
	else if(!token_is_equal("=", 1))
		rule_filter_backward = token_get_filter();

	return 1;
}

static int compile_uses(void)
{
	struct filter *forward, *backward;
	int status;

	if(!token_parse())
		goto return_fail;

	forward = rule_filter_forward;
	backward = rule_filter_backward;

	if(token_is_equal("-", 1))
		rule_filter_forward = NULL;
	else if(!token_is_equal("=", 1))
	{
		rule_filter_forward = token_get_filter();
		if(!rule_filter_forward)
			goto return_fail;
	}

	if(!token_parse())
	{
		rule_filter_forward = forward;
		goto return_fail;
	}

	if(token_is_equal("-", 1))
		rule_filter_backward = NULL;
	else if(!token_is_equal("=", 1))
	{
		rule_filter_backward = token_get_filter();
		if(!rule_filter_backward)
			goto return_fail;
	}

	if(!token_parse())
	{
		rule_filter_forward = forward;
		rule_filter_backward = backward;
		goto return_fail;
	}

	status = token_compile();

	rule_filter_forward = forward;
	rule_filter_backward = backward;
	return status;

	return_fail:
	log_message(LOG_ERROR, "%s:%d  invalid uses", table_file_names[include_depth], table_file_lines[include_depth]);
	return 0;
}

/******************************************************************************/

static int compile_rule(void)
{
	struct rule *rule;
	enum table_hash_type hash_type;
	enum rule_direction direction;
	Unicode *chars, *dots;
	int chars_len, dots_len;
	int chars_weight, dots_weight;

	if(!token_parse())
		goto return_fail;

	chars_weight =
	dots_weight = 0;
	direction = BOTH;
	while(*token_crs == u'-')
	{
		if(token_is_equal("-forward", 8))
			direction = FORWARD;
		else if(token_is_equal("-backward", 9))
			direction = BACKWARD;
		else if(token_is_equal("-after", 6))
			chars_weight =
			dots_weight = 1;
		else
		{
			log_message_with_token(LOG_ERROR, token_crs, token_len, "%s:%d  invalid rule option %TOKEN", table_file_names[include_depth], table_file_lines[include_depth]);
			return 0;
		}

		if(!token_parse())
			goto return_fail;
	}

	if(token_is_equal("init", 4))
		hash_type = TABLE_HASH_INIT;
	else if(token_is_equal("premode", 7))
		hash_type = TABLE_HASH_PREMODE;
	else if(token_is_equal("postmode", 8))
		hash_type = TABLE_HASH_POSTMODE;
	else if(token_is_equal("pretrans", 8))
		hash_type = TABLE_HASH_PRETRANS;
	else if(token_is_equal("trans", 5))
		hash_type = TABLE_HASH_TRANS;
	else if(token_is_equal("posttrans", 9))
		hash_type = TABLE_HASH_POSTTRANS;
	else if(token_is_equal("fini", 4))
		hash_type = TABLE_HASH_FINI;
	else
	{
		log_message_with_token(LOG_ERROR, token_crs, token_len, "%s:%d  invalid rule type %TOKEN", table_file_names[include_depth], table_file_lines[include_depth]);
		return 0;
	}

	if(!token_parse())
		goto return_fail;

	chars_len = token_convert_escapes_with_dots();
	if(chars_len <= 0)
		goto return_fail;
	chars = token_crs;

	if(!token_parse())
		goto return_fail;

	if(hash_type == TABLE_HASH_TRANS)
		dots_len = token_convert_to_dots();
	else
		dots_len = token_convert_escapes_with_dots();
	if(dots_len <= 0)
		goto return_fail;
	dots = token_crs;

	rule = table_add_rule(table, hash_type, direction, rule_filter_forward, rule_filter_backward, chars, chars_len, dots, dots_len, chars_weight, dots_weight);
	if(!rule)
	{
		log_message(LOG_ERROR, "%s:%d  unable to add rule", table_file_names[include_depth], table_file_lines[include_depth]);
		return 0;
	}
	rule->attrs = rule_attrs;
	rule->direction = direction;

	return 1;

	return_fail:
	log_message(LOG_ERROR, "%s:%d  invalid rule", table_file_names[include_depth], table_file_lines[include_depth]);
	return 0;
}

/******************************************************************************/

static int compile_match(void)
{
	struct rule *rule;
	enum table_hash_type hash_type;
	enum rule_direction direction;
	Unicode *chars, *dots;
	int chars_len, dots_len;
	int chars_weight, dots_weight;
	struct filter *filter_forward, *filter_backward;
	Unicode pattern[PATTERN_MAX], *before, *after;
	int before_len, after_len;

	filter_forward =
	filter_backward = NULL;
	before =
	after = NULL;

	if(!token_parse())
		goto return_fail;

	/*   -weak may be pointless for match,
	     but leave it for consistency   */
	chars_weight =
	dots_weight = 0;

	direction = BOTH;
	while(*token_crs == u'-')
	{
		if(token_is_equal("-forward", 8))
			direction = FORWARD;
		else if(token_is_equal("-backward", 9))
			direction = BACKWARD;
		else if(token_is_equal("-after", 6))
			chars_weight =
			dots_weight = 1;
		else
		{
			log_message_with_token(LOG_ERROR, token_crs, token_len, "%s:%d  invalid match option %TOKEN", table_file_names[include_depth], table_file_lines[include_depth]);
			return 0;
		}

		if(!token_parse())
			goto return_fail;
	}

	if(token_is_equal("init", 4))
		hash_type = TABLE_HASH_INIT;
	else if(token_is_equal("premode", 7))
		hash_type = TABLE_HASH_PREMODE;
	else if(token_is_equal("postmode", 8))
		hash_type = TABLE_HASH_POSTMODE;
	else if(token_is_equal("pretrans", 8))
		hash_type = TABLE_HASH_PRETRANS;
	else if(token_is_equal("trans", 5))
		hash_type = TABLE_HASH_TRANS;
	else if(token_is_equal("posttrans", 9))
		hash_type = TABLE_HASH_POSTTRANS;
	else if(token_is_equal("fini", 4))
		hash_type = TABLE_HASH_FINI;
	else
	{
		log_message_with_token(LOG_ERROR, token_crs, token_len, "%s:%d  invalid match type %TOKEN", table_file_names[include_depth], table_file_lines[include_depth]);
		return 0;
	}

	if(!token_parse())
		goto return_fail;

	/*   forward filter   */
	if(token_crs[0] == u'-' && token_len == 1)
	{
		before = NULL;
		before_len = 0;
	}
	else if(token_crs[0] == u'=' && token_len == 1)
	{
		if(rule_filter_forward->before)
		{
			before_len = rule_filter_forward->before_len;
			before = MALLOC((before_len + 1) * sizeof(Unicode));
			if(!before)
			{
				LOG_ALLOCATE_FAIL
				goto return_fail_free;
			}
			memcpy(before, rule_filter_forward->before, (before_len + 1) * sizeof(Unicode));
		}
		else
		{
			before = NULL;
			before_len = 0;
		}
	}
	else
	{
		if(token_convert_escapes_with_dots() <= 0)
			goto return_fail;
		before_len = pattern_compile(pattern, PATTERN_MAX, token_crs, token_len, table->attrs_chars, table->subpatterns);
		if(!before_len)
			goto return_fail;
		pattern_reverse(pattern);
		before = MALLOC((before_len + 1) * sizeof(Unicode));
		if(!before)
		{
			LOG_ALLOCATE_FAIL
			goto return_fail_free;
		}
		memcpy(before, pattern, (before_len + 1) * sizeof(Unicode));
	}

	if(!token_parse())
		goto return_fail;

	/*   target chars   */
	chars_len = token_convert_escapes_with_dots();
	if(chars_len <= 0)
		goto return_fail;
	chars = token_crs;

	if(!token_parse())
		goto return_fail;

	/*   after pattern   */
	if(token_crs[0] == u'-' && token_len == 1)
	{
		after = NULL;
		after_len = 0;
	}
	else if(token_crs[0] == u'=' && token_len == 1)
	{
		if(rule_filter_forward->after)
		{
			after_len = rule_filter_forward->after_len;
			after = MALLOC((after_len + 1) * sizeof(Unicode));
			if(!after)
			{
				LOG_ALLOCATE_FAIL
				goto return_fail_free;
			}
			memcpy(after, rule_filter_forward->after, (after_len + 1) * sizeof(Unicode));
		}
		else
		{
			after = NULL;
			after_len = 0;
		}
	}
	else
	{
		if(token_convert_escapes_with_dots() <= 0)
			goto return_fail;
		after_len = pattern_compile(pattern, PATTERN_MAX, token_crs, token_len, table->attrs_chars, table->subpatterns);
		if(!after_len)
			goto return_fail;
		after = MALLOC((after_len + 1) * sizeof(Unicode));
		if(!after)
		{
			LOG_ALLOCATE_FAIL
			goto return_fail_free;
		}
		memcpy(after, pattern, (after_len + 1) * sizeof(Unicode));
	}

	if(before || after)
	{
		filter_forward = filter_allocate();
		if(!filter_forward)
		{
			LOG_ALLOCATE_FAIL
			goto return_fail_free;
		}
		filter_forward->nxt = NULL;
		filter_forward->name = NULL;
		filter_forward->before = before;
		filter_forward->before_len = before_len;
		filter_forward->after = after;
		filter_forward->after_len = after_len;
		before =
		after = NULL;
	}

	if(!token_parse())
		goto return_fail;

	/*   backward filter   */
	if(token_crs[0] == u'-' && token_len == 1)
	{
		before = NULL;
		before_len = 0;
	}
	else if(token_crs[0] == u'=' && token_len == 1)
	{
		if(rule_filter_backward->before)
		{
			before_len = rule_filter_backward->before_len;
			before = MALLOC((before_len + 1) * sizeof(Unicode));
			if(!before)
			{
				LOG_ALLOCATE_FAIL
				goto return_fail_free;
			}
			memcpy(before, rule_filter_backward->before, (before_len + 1) * sizeof(Unicode));
		}
		else
		{
			before = NULL;
			before_len = 0;
		}
	}
	else
	{
		if(token_convert_escapes_with_dots() <= 0)
			goto return_fail;
		before_len = pattern_compile(pattern, PATTERN_MAX, token_crs, token_len, table->attrs_chars, table->subpatterns);
		if(!before_len)
			goto return_fail;
		pattern_reverse(pattern);
		before = MALLOC((before_len + 1) * sizeof(Unicode));
		if(!before)
		{
			LOG_ALLOCATE_FAIL
			goto return_fail_free;
		}
		memcpy(before, pattern, (before_len + 1) * sizeof(Unicode));
	}

	if(!token_parse())
		goto return_fail;

	/*   dots   */
	if(hash_type == TABLE_HASH_TRANS)
		dots_len = token_convert_to_dots();
	else
		dots_len = token_convert_escapes_with_dots();
	if(dots_len <= 0)
		goto return_fail;
	dots = token_crs;

	if(!token_parse())
		goto return_fail;

	/*   after pattern   */
	if(token_crs[0] == u'-' && token_len == 1)
	{
		after = NULL;
		after_len = 0;
	}
	else if(token_crs[0] == u'=' && token_len == 1)
	{
		if(rule_filter_backward->after)
		{
			after_len = rule_filter_backward->after_len;
			after = MALLOC((after_len + 1) * sizeof(Unicode));
			if(!after)
			{
				LOG_ALLOCATE_FAIL
				goto return_fail_free;
			}
			memcpy(after, rule_filter_backward->after, (after_len + 1) * sizeof(Unicode));
		}
		else
		{
			after = NULL;
			after_len = 0;
		}
	}
	else
	{
		if(token_convert_escapes_with_dots() <= 0)
			goto return_fail;
		after_len = pattern_compile(pattern, PATTERN_MAX, token_crs, token_len, table->attrs_chars, table->subpatterns);
		if(!after_len)
			goto return_fail;
		after = MALLOC((after_len + 1) * sizeof(Unicode));
		if(!after)
		{
			LOG_ALLOCATE_FAIL
			goto return_fail_free;
		}
		memcpy(after, pattern, (after_len + 1) * sizeof(Unicode));
	}

	if(before || after)
	{
		filter_backward = filter_allocate();
		if(!filter_backward)
		{
			LOG_ALLOCATE_FAIL
			goto return_fail_free;
		}
		filter_backward->nxt = NULL;
		filter_backward->name = NULL;
		filter_backward->before = before;
		filter_backward->before_len = before_len;
		filter_backward->after = after;
		filter_backward->after_len = after_len;
		before =
		after = NULL;
	}

	rule = table_add_rule(table, hash_type, direction, filter_forward, filter_backward, chars, chars_len, dots, dots_len, chars_weight, dots_weight);
	if(!rule)
	{
		log_message(LOG_ERROR, "%s:%d  unable to add match rule", table_file_names[include_depth], table_file_lines[include_depth]);
		goto return_fail_free;
	}
	rule->attrs = rule_attrs;
	rule->direction = direction;

	return 1;

	return_fail:
	log_message(LOG_ERROR, "%s:%d  invalid match", table_file_names[include_depth], table_file_lines[include_depth]);

	return_fail_free:
	if(before)
		FREE(before);
	if(after)
		FREE(after);
	if(filter_forward)
		FREE(filter_forward);
	if(filter_backward)
		FREE(filter_backward);
	return 0;
}

/******************************************************************************/

struct macro
{
	struct macro *nxt;
	char *ctag;
	Unicode *tag;
	Unicode **lines;
	int tag_len, lines_cnt, processing;
	char *file_name;
	int file_line;
};

#define MACRO_ARGUMENTS_MAX  10
#define MACRO_LINES_MAX      50
#define MACRO_DEPTH_MAX       8

static struct macro *macros;
static int macro_depth;

static void macro_init(struct macro *macro)
{
	memset(macro, 0, sizeof(struct macro));
}

static void macro_fini(struct macro *macro)
{
	int i;

	if(!macro)
		return;

	ASSERT(!macro->processing)

	if(macro->ctag)
		FREE(macro->ctag);
	if(macro->tag)
		FREE(macro->tag);
	if(macro->file_name)
		FREE(macro->file_name);

	if(macro->lines)
	{
		/*   lines[] could be null if error while compiling macro   */
		for(i = 0; i < macro->lines_cnt; i++)
		if(macro->lines[i])
			FREE(macro->lines[i]);
		FREE(macro->lines);
	}
}

ATTRIBUTE_FUNCTION_MALLOC
static struct macro* macro_allocate(void)
{
	struct macro *macro;

	macro = MALLOC(sizeof(struct macro));
	LOG_ALLOCATE_FAIL_RETURN_NULL(macro)
	macro_init(macro);
	return macro;
}

static void macro_free(struct macro *macro)
{
	if(!macro)
		return;

	macro_free(macro->nxt);

	macro_fini(macro);
	FREE(macro);
}

static struct macro* macro_find(const Unicode *uchars, const int uchars_len)
{
	struct macro *macro;

	macro = macros;
	while(macro)
	if(utf16_are_equal(uchars, uchars_len, macro->tag, macro->tag_len))
		break;
	else
		macro = macro->nxt;

	return macro;
}

static inline struct macro* token_find_macro(void)
{
	return macro_find(&token_crs[1], token_len - 1);
}

static int compile_macro(FILE *file, char cchars[INPUT_LINE_MAX], const char *file_name)
{
	struct macro *macro;
	Unicode tag[INPUT_LINE_MAX], *lines[MACRO_LINES_MAX];
	char ctag[INPUT_LINE_MAX];
	int ctag_len, file_name_len, tag_len, line_len, lines_cnt, table_line_begin, i;

	DB_MEMSET(tag, 0, INPUT_LINE_MAX * sizeof(Unicode));
	DB_MEMSET(ctag, 0, INPUT_LINE_MAX);
	DB_MEMSET(lines, 0, MACRO_LINES_MAX * sizeof(Unicode*));

	if(!token_parse())
	{
		log_message(LOG_ERROR, "%s:%d  missing macro tag", table_file_names[include_depth], table_file_lines[include_depth]);
		return 0;
	}

	/*   tag array is same length of cchars array,
	     so there should always be enough space to copy   */
	tag_len = token_len;
	utf16_copy(tag, token_crs, token_len + 1);

	ctag_len = utf16le_convert_to_utf8(ctag, INPUT_LINE_MAX, token_crs, token_len);
	if(!ctag_len)
	{
		log_message_with_token(LOG_ERROR, token_crs, token_len, "%s:%d  invalid macro tag %TOKEN", table_file_names[include_depth], table_file_lines[include_depth]);
		return 0;
	}

	/*   make room for terminating NULL char   */
	ctag_len++;

	/*   use return_fail_free from here on out   */
	macro = NULL;
	lines_cnt = 0;

	table_line_begin = table_file_lines[include_depth];
	while(fgets(cchars, INPUT_LINE_MAX, file))
	{
		table_file_lines[include_depth]++;

		if(!strncmp(cchars, "eom", 3))
			break;

		/*   let continue to try to find eom   */
		if(lines_cnt >= MACRO_LINES_MAX)
			continue;

		line_len = utf8_convert_to_utf16le(token_line, INPUT_LINE_MAX, cchars, INPUT_LINE_MAX) + 1;

		lines[lines_cnt] = MALLOC((line_len + 1) * sizeof(Unicode));
		if(!lines[lines_cnt])
		{
			LOG_ALLOCATE_FAIL
			goto return_fail_free;
		}
		utf16_copy(lines[lines_cnt], token_line, line_len + 1);

		lines_cnt++;
	}

	if(lines_cnt >= MACRO_LINES_MAX)
	{
		log_message(LOG_ERROR, "%s:%d  too many lines for macro %s", table_file_names[include_depth], table_file_lines[include_depth], ctag);
		goto return_fail_free;
	}

	macro = macro_allocate();
	if(!macro)
		goto return_fail_free;

	macro->ctag = MALLOC(ctag_len + 1);
	if(!macro->ctag)
	{
		LOG_ALLOCATE_FAIL
		goto return_fail_free;
	}
	strncpy(macro->ctag, ctag, ctag_len + 1);

	file_name_len = strlen(file_name) + 1;
	macro->file_name = MALLOC(file_name_len);
	if(!macro->file_name)
	{
		LOG_ALLOCATE_FAIL
		goto return_fail_free;
	}
	strncpy(macro->file_name, file_name, file_name_len);

	macro->tag = MALLOC((tag_len + 1) * sizeof(Unicode));
	if(!macro->tag)
	{
		LOG_ALLOCATE_FAIL
		goto return_fail_free;
	}
	utf16_copy(macro->tag, tag, tag_len + 1);
	macro->tag_len = tag_len;

	macro->lines = MALLOC(lines_cnt * sizeof(Unicode*));
	if(!macro->lines)
	{
		LOG_ALLOCATE_FAIL
		goto return_fail_free;
	}
	for(i = 0; i < lines_cnt; i++)
		macro->lines[i] = lines[i];
	macro->lines_cnt = lines_cnt;

	macro->file_line = table_line_begin;

	/*   add to macro list   */
	macro->nxt = macros;
	macros = macro;
	return 1;

	return_fail_free:
	if(macro)
		macro_free(macro);
	for(i = 0; i < lines_cnt; i++)
		FREE(lines[i]);

	return 0;
}

static int do_macro(void)
{
	Unicode line[INPUT_LINE_MAX], *args[MACRO_ARGUMENTS_MAX];
	int args_lens[MACRO_ARGUMENTS_MAX], args_cnt;
	struct macro *macro;
	int i, j, off, crs, arg;

	macro = token_find_macro();
	if(!macro)
	{
		log_message_with_token(LOG_ERROR, &token_crs[1], token_len - 1, "%s:%d  macro %TOKEN not found", table_file_names[include_depth], table_file_lines[include_depth]);
		return 0;
	}

	if(macro_depth + 1 >= MACRO_DEPTH_MAX)
	{
		log_message_with_token(LOG_ERROR, &token_crs[1], token_len - 1, "%s:%d  macro %TOKEN too deep", table_file_names[include_depth], table_file_lines[include_depth]);
		return 0;
	}

	if(macro->processing)
	{
		log_message(LOG_ERROR, "%s:%d  recursive macro @%s, defined at %s:%d", table_file_names[include_depth], table_file_lines[include_depth], macro->ctag, macro->file_name, macro->file_line);
		return 0;
	}
	macro->processing = 1;

	memset(args,      0, MACRO_ARGUMENTS_MAX * sizeof(Unicode*));
	memset(args_lens, 0, MACRO_ARGUMENTS_MAX * sizeof(int));
	args_cnt = 0;

	while(token_parse())
	{
		if(token_crs[0] == u'#' && token_len == 1)
			break;

		args[args_cnt] = token_crs;
		args_lens[args_cnt] = token_len;

		args_cnt++;
		if(args_cnt >= MACRO_ARGUMENTS_MAX)
		{
			macro->processing = 0;
			log_message(LOG_ERROR, "%s:%d  too many args for macro @%s, defined at %s:%d", table_file_names[include_depth], table_file_lines[include_depth], macro->ctag, macro->file_name, macro->file_line);
			return 0;
		}
	}

	for(i = 0; i < macro->lines_cnt; i++)
	{
		DB_MEMSET(line, 0, INPUT_LINE_MAX * sizeof(Unicode))

		/*   convert args   */
		off =
		crs = 0;
		while(off < INPUT_LINE_MAX - 1)
		{
			if(!macro->lines[i][off])
				break;
			else if(macro->lines[i][off] == u'$')
			{
				if(off + 1 >= INPUT_LINE_MAX)
				{
					line[crs++] = macro->lines[i][off++];
					continue;
				}

				off++;
				if(macro->lines[i][off] >= u'1' && macro->lines[i][off] <= u'9')
				{
					arg = 8 - (u'9' - macro->lines[i][off]);
					if(arg >= args_cnt)
					{
						macro->processing = 0;
						log_message(LOG_ERROR, "%s:%d  $%d over argument count %d for macro @%s, defined at %s:%d", table_file_names[include_depth], table_file_lines[include_depth], arg + 1, args_cnt, macro->ctag, macro->file_name, macro->file_line);
						return 0;
					}
					if(args_lens[arg] + crs >= INPUT_LINE_MAX)
					{
						macro->processing = 0;
						log_message(LOG_FATAL, "%s:%d  $%d caused buffer overflow for macro @%s, defined at %s:%d", table_file_names[include_depth], table_file_lines[include_depth], arg + 1, macro->ctag, macro->file_name, macro->file_line);
						return 0;
					}
					for(j = 0; j < args_lens[arg]; j++)
						line[crs++] = args[arg][j];
					off++;
					continue;
				}
				else
					line[crs++] = u'$';

				/*   fall through to just copy character after offset   */
			}
			line[crs++] = macro->lines[i][off++];
		}
		line[crs] =
		line[crs + 1] = 0;

		if(!token_init(line))
			continue;

		macro_depth++;
		token_compile();
		macro_depth--;
	}

	macro->processing = 0;
	return 1;
}

/******************************************************************************/

static void log_included_file_errors(void)
{
	int i;

	for(i = include_depth - 1; i >= 0; i--)
		log_message(LOG_ERROR, "   included at %s:%d", table_file_names[i], table_file_lines[i]);
}

static int token_compile(void)
{
	int status;

	ASSERT(macro_depth < MACRO_DEPTH_MAX)

	status = 0;
	     if(token_crs[0] == u'@')
		status = do_macro();
	else if(token_is_equal("config", 6))
		status = compile_config();
	else if(token_is_equal("set", 3))
		status = compile_set();
	else if(token_is_equal("mode", 4))
		status = compile_mode();
	else if(token_is_equal("chars", 5))
		status = compile_chars();
	else if(token_is_equal("join", 4))
		status = compile_join();
	else if(token_is_equal("attrs", 5))
		status = compile_attrs();
	else if(token_is_equal("pattern", 7))
		status = compile_pattern();
	else if(token_is_equal("filter", 6))
		status = compile_filter();
	else if(token_is_equal("use", 3))
		status = compile_use();
	else if(token_is_equal("uses", 4))
		status = compile_uses();
	else if(token_is_equal("rule", 4))
		status = compile_rule();
	else if(token_is_equal("match", 5))
		status = compile_match();
	else
		log_message_with_token(LOG_ERROR, token_crs, token_len, "%s:%d  unknown opcode %TOKEN", table_file_names[include_depth], table_file_lines[include_depth]);

	if(!status)
		log_included_file_errors();

	return 1;
}

static void file_read(FILE *file, const char *file_name)
{
	FILE *include_file;
	char cchars[INPUT_LINE_MAX], path_name[INPUT_LINE_MAX];
	int pause, crs, i;

	if(include_depth >= INCLUDE_DEPTH_MAX - 1)
	{
		log_message(LOG_ERROR, "%s:%d  too many levels of include files", table_file_names[include_depth], table_file_lines[include_depth]);
		log_included_file_errors();
		return;
	}

	include_depth++;
	table_file_names[include_depth] = file_name;
	table_file_lines[include_depth] = 0;

	pause = 0;
	while(fgets(cchars, INPUT_LINE_MAX, file))
	{
		table_file_lines[include_depth]++;

		if(pause)
		{
			if(!strncmp(cchars, ".cont", 5))
				pause = 0;
			continue;
		}
		else if(!strncmp(cchars, ".stop", 5))
		{
			pause = 1;
			continue;
		}

		if(cchars[0] == '#')
			continue;

		/*   include file   */
		else if(!strncmp(cchars, "include", 7))
		{
			/*   parse file name   */
			if(cchars[7] != ' ' && cchars[7] != '\t')
			{
				log_message(LOG_ERROR, "%s:%d  include missing file name", table_file_names[include_depth], table_file_lines[include_depth]);
				log_included_file_errors();
				continue;
			}
			for(crs = 8; cchars[crs] && crs < INPUT_LINE_MAX; crs++)
			if(!is_space(cchars[crs]))
				break;
			if(crs >= INPUT_LINE_MAX)
			{
				log_message(LOG_ERROR, "%s:%d  include missing file name", table_file_names[include_depth], table_file_lines[include_depth]);
				log_included_file_errors();
				continue;
			}

			/*   trim whitespace at end   */
			for(i = strlen(cchars) - 1; i > 8; i--)
			if(is_space(cchars[i]))
				cchars[i] = 0;
			else
				break;
			if(i <= 8)
			{
				log_message(LOG_ERROR, "%s:%d  invalid include", table_file_names[include_depth], table_file_lines[include_depth]);
				log_included_file_errors();
				continue;
			}

			/*   compile include file   */
			include_file = lookup_open_file(path_name, INPUT_LINE_MAX, &cchars[crs], table->file_name);
			if(!include_file)
			{
				log_message(LOG_ERROR, "%s:%d  unable to open include file %s", table_file_names[include_depth], table_file_lines[include_depth], &cchars[crs]);
				log_included_file_errors();
				continue;
			}
			file_read(include_file, path_name);
			fclose(include_file);
			continue;
		}

		memset(token_line, 0, INPUT_LINE_MAX * sizeof(Unicode));
		utf8_convert_to_utf16le(token_line, INPUT_LINE_MAX - 1, cchars, INPUT_LINE_MAX);

		if(!token_init(token_line))
			continue;

		if(token_is_equal(".end", 4))
			break;

		/*  do this here so macros can't define other macros   */
		if(token_is_equal("macro", 5))
		{
			if(!compile_macro(file, cchars, file_name))
				log_included_file_errors();
			continue;
		}

		token_compile();
	}

	include_depth--;
}

struct table* table_compile_from_file(const char *file_name)
{
	FILE *file;
	struct table table_auto;
	char attrs_chars_default[] = "0123456789ABCDEFGHIJKLMNOPQRSTUV";
	int file_name_len, i;

	file = fopen(file_name, "r");
	if(!file)
		return NULL;

	table = &table_auto;
	table_init(table);

	file_name_len = strlen(file_name) + 1;
	table->file_name = MALLOC(file_name_len);
	LOG_ALLOCATE_FAIL_RETURN_NULL(table->file_name)
	strncpy(table->file_name, file_name, file_name_len);

	rule_attrs = 0;
	rule_filter_forward =
	rule_filter_backward = NULL;
	variables = NULL;
	macros = NULL;
	var_enum = 0;
	macro_depth = 0;
	include_depth = -1;

	/*   set defaults   */
	table->marker_user      = TABLE_MARKER_USER;
	table->marker_begin     = TABLE_MARKER_BEGIN;
	table->marker_end       = TABLE_MARKER_END;
	table->marker_modifier  = TABLE_MARKER_MODIFIER;
	table->marker_hard      = TABLE_MARKER_HARD;
	table->marker_soft      = TABLE_MARKER_SOFT;
	table->marker_internal  = TABLE_MARKER_INTERNAL;
	for(i = 0; i < 32; i++)
		table->attrs_chars[i] = attrs_chars_default[i];

	file_read(file, table->file_name);
	fclose(file);

	variable_free(variables);
	variables = NULL;
	macro_free(macros);
	macros = NULL;

	/*   this could happen if file_name was a directory
	     or an empty file   */
	if(!table_file_lines[0])
	{
		FREE(table->file_name);
		return NULL;
	}

	table = table_allocate();
	*table = table_auto;

#ifdef DEBUG

	if(!table->nocontract_set)
	{
		ASSERT(!table->nocontract.begin_len)
		ASSERT(!table->nocontract.end_len)
		ASSERT(!table->nocontract.word_len)
		ASSERT(!table->nocontract.term_len)
		ASSERT(!table->nocontract.symbol_len)
	}
	if(!table->capital_set)
	{
		ASSERT(!table->capital.begin_len)
		ASSERT(!table->capital.end_len)
		ASSERT(!table->capital.word_len)
		ASSERT(!table->capital.term_len)
		ASSERT(!table->capital.symbol_len)
	}
	if(!table->numeric_set)
	{
		ASSERT(!table->numeric.begin_len)
		ASSERT(!table->numeric.end_len)
		ASSERT(!table->numeric.word_len)
		ASSERT(!table->numeric.term_len)
		ASSERT(!table->numeric.symbol_len)
	}

#endif

	return table;
}

/******************************************************************************/

static int compile_convert(struct conversion *conversion)
{
	Unicode cell, uchar;

	if(!token_parse())
		goto return_fail;
	if(token_convert_to_dots() < 0)
		goto return_fail;
	if(token_len != 1)
		goto return_fail;

	cell = *token_crs;

	if(!token_parse())
		goto return_fail;

	token_convert_escapes();
	if(token_len != 1)
		goto return_fail;

	uchar = *token_crs;

	return conversion_set_cell(conversion, cell, uchar);

	return_fail:
	log_message(LOG_ERROR, "%s:%d  invalid convert", conversion->file_name, table_file_lines[0]);
	return 0;
}

static int compile_unknown(struct conversion *conversion)
{
	if(!token_parse())
		goto return_fail;
	if(token_len != 1)
		goto return_fail;

	return conversion_set_unknown(conversion, *token_crs);

	return_fail:
	log_message(LOG_ERROR, "%s:%d  invalid unknown", conversion->file_name, table_file_lines[0]);
	return 0;
}

struct conversion* conversion_compile_from_file(const char *file_name)
{
	FILE *file;
	char cchars[INPUT_LINE_MAX];
	struct conversion conversion_auto, *conversion;
	int file_name_len;

	file = fopen(file_name, "r");
	if(!file)
		return NULL;

	conversion = &conversion_auto;
	conversion_init(conversion);

	file_name_len = strlen(file_name) + 1;
	conversion->file_name = MALLOC(file_name_len);
	LOG_ALLOCATE_FAIL_RETURN_NULL(conversion->file_name)
	strncpy(conversion->file_name, file_name, file_name_len);

	table_file_lines[0] = 0;

	while(fgets(cchars, INPUT_LINE_MAX, file))
	{
		table_file_lines[0]++;

		if(cchars[0] == '#')
			continue;

		memset(token_line, 0, INPUT_LINE_MAX * sizeof(Unicode));
		utf8_convert_to_utf16le(token_line, INPUT_LINE_MAX - 1, cchars, INPUT_LINE_MAX);

		if(!token_init(token_line))
			continue;

		if(token_is_equal(".end", 4))
			break;

		     if(token_is_equal("convert", 7))
			compile_convert(conversion);
		else if(token_is_equal("unknown", 7))
			compile_unknown(conversion);
	}

	fclose(file);

	/*   this could happen if file_name was a directory   */
	if(!table_file_lines[0])
	{
		FREE(table->file_name);
		return NULL;
	}

	conversion = conversion_allocate();
	*conversion = conversion_auto;

	return conversion;
}

/******************************************************************************/
