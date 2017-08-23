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

#ifndef TRANSLATE_H
#define TRANSLATE_H


/* By keeping track of whether any function in translate_generic_forward() or
 * translate_generic_backward() has made any change in translation, unnecessary
 * calls to translate_copy_to_output() can be avoided.  This does give a
 * noticable performance boost.
 *
 * If this is not defined, then translate->output must always contain at least
 * a copy of translate->input, so that when translate_output_to_input() is
 * called, translate->output is never empty and wipes out translate->input.
 * The same is true for the input and output maps.
*/
#define CHECK_FOR_CHANGE


#include "table.h"
#include "conversion.h"

/******************************************************************************/

struct translate
{
	const struct table *const*tables;
	int table_crs, table_cnt;

	const Unicode *chars;
	Unicode *dots;
	int chars_len, dots_len;
	int *chars_to_dots_map, *dots_to_chars_map;

	Unicode *input;
	int input_crs, input_len;
	int *input_to_output_map, *input_map;

	Unicode *output;
	int output_len, output_max, output_inc;
	int *output_to_input_map;

	int cursor_pos, cursor_set;

	int maps_use;

#ifdef CHECK_FOR_CHANGE
	int changed;
#endif
};

/******************************************************************************/

/* Checks input_crs if on soft or hard indicator and if indicator is defined by
 * mode.  The table table is used to determine the soft and hard indicators
 * (should be the last table in translate) and that mode does not need to be
 * defined in that table.
 *
 * Returns the type of indicator or NONE.
*/
enum mode_type translate_get_mode_indicator(const struct translate *translate, const struct table *table, const struct mode *mode);


/* Checks the current output_len to ensure that there is enough space to store
 * increment more characters.  If not, the output and output map buffers are
 * reallocated.
 *
 * Returns status of successful check.
*/
int translate_check_output_max(struct translate *translate, const int increment);


/* Shifts the input_crs chars_cnt number of characters.  Ensures that input_crs
 * stops at input_len.  If clear_map is set, input mapping is set to -1.
 *
 * Returns status of successful shift.
*/
int translate_skip(struct translate *translate, const int chars_cnt, const int clear_map);


/* Appends dots to output.  Output map is set to -1.
 *
 * Returns status of successful insertion.
*/
int translate_insert_dots(struct translate *translate, const Unicode *dots, const int dots_len);


/* Appends dots to output and shifts the input_crs chars_cnt number of
 * characters.  Both input and output are mapped.  Ensures that input_crs stops
 * at input_len.
 *
 * Returns status of successful insertion.
*/
int translate_insert_dots_for_chars(struct translate *translate, const Unicode *dots, const int dots_len, const int chars_cnt);


/* Copies count characters at input_crs to output.  If do_map is set, input and
 * output are mapped; else input and output mappings are set to -1.
 *
 * Returns status of successful copy.
*/
int translate_copy_to_output(struct translate *translate, const int count, const int do_map);


/* If input_crs is on a user indicator, begin, or end, copies the indicator
 * and the next indicator along with the characters in between.  Input and
 * output mappings are set to -1.
 *
 * Returns status of successful copy or -1 is was not on indicator.
*/
int translate_copy_marked_user(struct translate *translate);


/* If input_crs is on either a soft or hard indicator mark, copies the indicator
 * and the next indicator along with the characters in between.  Input and
 * output mappings are set to -1.
 *
 * Returns status of successful copy or -1 is was not on indicator.
*/
int translate_copy_marked_indicators(struct translate *translate);


/* If input_crs is on either a soft or hard indicator or modifier mark, copies
 * the indicator or modifier and the next indicator or modifier along with the
 * characters in between.  Input and output mappings are set to -1.
 *
 * Returns status of successful copy or -1 is was not on indicator.
*/
int translate_copy_marked_indicators_or_modifiers(struct translate *translate);


/* Sets the input and its map buffer to the output and its map buffer.  The
 * original input and map buffer is freed and new output and map buffers are
 * allocated.
*/
int translate_output_to_input(struct translate *translate);


/* Sets up a translation and calls the appropriate translation function.
 *
 * Returns the length of the resulting translation, 0 if no processing was done
 * and no translation was performed, and -1 if an error occurred.  The resulting
 * translation is stored in dots (regardless of direction).
*/
int translate_start(Unicode *dots,
                    const int dots_len,
                    const Unicode *chars,
                    const int chars_len,
                    const struct table *const*tables,
                    const int table_cnt,
                    const struct conversion *conversion,
                    const enum rule_direction direction,
                    int *chars_to_dots_map,
                    int *dots_to_chars_map,
                    int *cursor);

/******************************************************************************/

/* Common input to output remapping function
*/
static inline void translate_remap_input(struct translate *translate, const int offset, const int clear_map)
{
	int map, i, m;

	map = translate->output_len;
	if(clear_map)
		map = -1;

	ASSERT(translate->input_crs + offset < translate->input_len)
	if(translate->input_map[translate->input_crs + offset] >= 0)
	if(translate->input_crs == 0 || (translate->input_map[translate->input_crs - 1] != translate->input_map[translate->input_crs]))
	{
		/*   remap whole input block   */
		m = translate->input_map[translate->input_crs + offset];
		if(translate->input_to_output_map[m] >= 0)
		{
			for(i = m + 1; i < translate->chars_len; i++)
			if(translate->input_to_output_map[i] >= 0 && translate->input_to_output_map[i] == translate->input_to_output_map[m])
				translate->input_to_output_map[i] = map;
			else
				break;

			translate->input_to_output_map[m] = map;
		}
	}
}


/* Increments translate input_crs by chars_cnt and output_len by dots_cnt.
 * Keeps track of the cursor and updates it when needed.
*/
static inline void translate_increment(struct translate *translate, const int chars_cnt, const int dots_cnt)
{
	if(chars_cnt)
	if(!translate->cursor_set)
	if(translate->cursor_pos >= translate->input_crs && translate->cursor_pos < translate->input_crs + chars_cnt)
	{
		translate->cursor_set = 1;
		translate->cursor_pos = translate->output_len;
	}
	translate->input_crs += chars_cnt;
	translate->output_len += dots_cnt;
}

/******************************************************************************/

/* Appends dot to output.  Output mapping is set to -1.
 *
 * Returns status of successful insertion.
*/
static inline int translate_insert_dot(struct translate *translate, const Unicode dot)
{
	return translate_insert_dots(translate, &dot, 1);
}


/* Appends dot to output and shifts the input_crs count number of characters.
 * Both input and output are mapped.  Ensures that input_crs stops at input_len.
 *
 * Returns status of successful insertion.
*/
static inline int translate_insert_dot_for_chars(struct translate *translate, const Unicode dot, const int chars_len)
{
	return translate_insert_dots_for_chars(translate, &dot, 1, chars_len);
}

/******************************************************************************/

/* Returns 1 if input from at or input_crs is equal to uchars, 0 otherwise.
*/

static inline int translate_is_equal_at(const struct translate *translate, const Unicode *uchars, const int uchars_len, const int at)
{
	int i;

	if(!uchars_len)
		return 0;

	if(at + uchars_len > translate->input_len)
		return 0;

	for(i = 0; i < uchars_len; i++)
	if(translate->input[at + i] != uchars[i])
		return 0;

	return uchars_len;
}

static inline int translate_is_equal(const struct translate *translate, const Unicode *uchars, const int uchars_len)
{
	return translate_is_equal_at(translate, uchars, uchars_len, translate->input_crs);
}

/******************************************************************************/

/* Returns 1 if input from at or input_crs is on specified markers, 0 otherwise.
*/

static inline int translate_on_indicator_marker_at(const struct translate *translate, const int at)
{
	const struct table *table;

	/*   only check indicators from last table in tables   */
	table = translate->tables[translate->table_cnt - 1];

	return   translate->input[at] == table->marker_hard
	       || translate->input[at] == table->marker_soft;
}

static inline int translate_on_indicator_marker(const struct translate *translate)
{
	return translate_on_indicator_marker_at(translate, translate->input_crs);
}

static inline int translate_on_indicator_or_modifier_marker_at(const struct translate *translate, const int at)
{
	const struct table *table;

	/*   only check indicators from last table in tables   */
	table = translate->tables[translate->table_cnt - 1];

	return   translate->input[at] == table->marker_modifier
	       || translate->input[at] == table->marker_hard
	       || translate->input[at] == table->marker_soft;
}

static inline int translate_on_indicator_or_modifier_marker(const struct translate *translate)
{
	return translate_on_indicator_or_modifier_marker_at(translate, translate->input_crs);
}

static inline int translate_on_user_marker_at(const struct translate *translate, const int at)
{
	const struct table *table;

	/*   only check indicators from last table in tables   */
	table = translate->tables[translate->table_cnt - 1];

	return   translate->input[at] == table->marker_user
	       || translate->input[at] == table->marker_begin
	       || translate->input[at] == table->marker_end;
}

static inline int translate_on_user_marker(const struct translate *translate)
{
	return translate_on_user_marker_at(translate, translate->input_crs);
}


/* Returns 1 if input from at or input_crs is on any marker other than modifier,
 * 0 otherwise.
*/
static inline int translate_on_marker_at(const struct translate *translate, const int at)
{
	const struct table *table;

	/*   only check indicators from last table in tables   */
	table = translate->tables[translate->table_cnt - 1];

	return   translate->input[at] == table->marker_user
	       || translate->input[at] == table->marker_begin
	       || translate->input[at] == table->marker_end
	       || translate->input[at] == table->marker_hard
	       || translate->input[at] == table->marker_soft
	       || translate->input[at] == table->marker_internal;
}

static inline int translate_on_marker(const struct translate *translate)
{
	return translate_on_marker_at(translate, translate->input_crs);
}

/******************************************************************************/

/* Returns total counts from all tables for specified rule type.
*/

static inline int translate_get_init_chars_hash_cnt(const struct translate *translate)
{
	int cnt, i;

	cnt = 0;
	for(i = 0; i < translate->table_cnt; i++)
		cnt += translate->tables[i]->init_chars_hash_cnt;
	return cnt;
}

static inline int translate_get_init_dots_hash_cnt(const struct translate *translate)
{
	int cnt, i;

	cnt = 0;
	for(i = 0; i < translate->table_cnt; i++)
		cnt += translate->tables[i]->init_dots_hash_cnt;
	return cnt;
}

static inline int translate_get_premode_chars_hash_cnt(const struct translate *translate)
{
	int cnt, i;

	cnt = 0;
	for(i = 0; i < translate->table_cnt; i++)
		cnt += translate->tables[i]->premode_chars_hash_cnt;
	return cnt;
}

static inline int translate_get_premode_dots_hash_cnt(const struct translate *translate)
{
	int cnt, i;

	cnt = 0;
	for(i = 0; i < translate->table_cnt; i++)
		cnt += translate->tables[i]->premode_dots_hash_cnt;
	return cnt;
}

static inline int translate_get_postmode_chars_hash_cnt(const struct translate *translate)
{
	int cnt, i;

	cnt = 0;
	for(i = 0; i < translate->table_cnt; i++)
		cnt += translate->tables[i]->postmode_chars_hash_cnt;
	return cnt;
}

static inline int translate_get_postmode_dots_hash_cnt(const struct translate *translate)
{
	int cnt, i;

	cnt = 0;
	for(i = 0; i < translate->table_cnt; i++)
		cnt += translate->tables[i]->postmode_dots_hash_cnt;
	return cnt;
}

static inline int translate_get_pretrans_chars_hash_cnt(const struct translate *translate)
{
	int cnt, i;

	cnt = 0;
	for(i = 0; i < translate->table_cnt; i++)
		cnt += translate->tables[i]->pretrans_chars_hash_cnt;
	return cnt;
}

static inline int translate_get_pretrans_dots_hash_cnt(const struct translate *translate)
{
	int cnt, i;

	cnt = 0;
	for(i = 0; i < translate->table_cnt; i++)
		cnt += translate->tables[i]->pretrans_dots_hash_cnt;
	return cnt;
}

static inline int translate_get_trans_chars_hash_cnt(const struct translate *translate)
{
	int cnt, i;

	cnt = 0;
	for(i = 0; i < translate->table_cnt; i++)
		cnt += translate->tables[i]->trans_chars_hash_cnt;
	return cnt;
}

static inline int translate_get_trans_dots_hash_cnt(const struct translate *translate)
{
	int cnt, i;

	cnt = 0;
	for(i = 0; i < translate->table_cnt; i++)
		cnt += translate->tables[i]->trans_dots_hash_cnt;
	return cnt;
}

static inline int translate_get_posttrans_chars_hash_cnt(const struct translate *translate)
{
	int cnt, i;

	cnt = 0;
	for(i = 0; i < translate->table_cnt; i++)
		cnt += translate->tables[i]->posttrans_chars_hash_cnt;
	return cnt;
}

static inline int translate_get_posttrans_dots_hash_cnt(const struct translate *translate)
{
	int cnt, i;

	cnt = 0;
	for(i = 0; i < translate->table_cnt; i++)
		cnt += translate->tables[i]->posttrans_dots_hash_cnt;
	return cnt;
}

static inline int translate_get_fini_chars_hash_cnt(const struct translate *translate)
{
	int cnt, i;

	cnt = 0;
	for(i = 0; i < translate->table_cnt; i++)
		cnt += translate->tables[i]->fini_chars_hash_cnt;
	return cnt;
}

static inline int translate_get_fini_dots_hash_cnt(const struct translate *translate)
{
	int cnt, i;

	cnt = 0;
	for(i = 0; i < translate->table_cnt; i++)
		cnt += translate->tables[i]->fini_dots_hash_cnt;
	return cnt;
}

/******************************************************************************/

/* Convenience functions for checking if modes have been defined.
*/

static inline int translate_is_nocontract_set(const struct translate *translate)
{
	/*   only check indicators from last table in tables   */
	return translate->tables[translate->table_cnt - 1]->nocontract_set;
}

static inline int translate_is_numeric_set(const struct translate *translate)
{
	/*   only check indicators from last table in tables   */
	return translate->tables[translate->table_cnt - 1]->numeric_set;
}

static inline int translate_is_capital_set(const struct translate *translate)
{
	/*   only check indicators from last table in tables   */
	return translate->tables[translate->table_cnt - 1]->capital_set;
}

static inline int translate_get_emphases_cnt(const struct translate *translate)
{
	/*   only check indicators from last table in tables   */
	return translate->tables[translate->table_cnt - 1]->emphases_cnt;
}

/******************************************************************************/

/* Returns the attributes of the character at input_crs or at using the
 * attributes set in the table at table_crs.
*/

static inline unsigned int translate_get_attributes_at(const struct translate *translate, const int at)
{
	if(at < 0 || at >= translate->input_len)
		return 0;

	return table_get_unichar_attributes(translate->tables[translate->table_crs], translate->input[at]);
}

static inline unsigned int translate_get_attributes(const struct translate *translate)
{
	return translate_get_attributes_at(translate, translate->input_crs);
}


/* Convenience functions for testing character attributes.
*/

static inline int translate_has_attributes_at(const struct translate *translate, const int at, const unsigned int attrs)
{
	return translate_get_attributes_at(translate, at) & attrs;
}

static inline int translate_has_attributes_or_eoi_at(const struct translate *translate, const int at, const unsigned int attrs)
{
	if(at < 0 || at >= translate->input_len)
		return 1;
	return translate_get_attributes_at(translate, at) & attrs;
}

static inline int translate_has_attributes(const struct translate *translate, const unsigned int attrs)
{
	return translate_has_attributes_at(translate, translate->input_crs, attrs);
}

static inline int translate_has_attributes_or_eoi(const struct translate *translate, const unsigned int attrs)
{
	return translate_has_attributes_or_eoi_at(translate, translate->input_crs, attrs);
}

/******************************************************************************/

#endif /*   TRANSLATE_H   */
