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
#include <string.h>

#include "utf.h"
#include "pattern.h"
#include "translate.h"
#include "log.h"

/******************************************************************************/

#if 0
/* Checking stats of when keeping track of the previous character, the previous
 * character being looked up again happened about 0.03% at the time.  This does
 * not seem to help performance, so this function was inlined.
*/
unsigned int translate_get_attributes_at(const struct translate *translate, const int at)
{
	static unichar uchar_prv = 0;
	static unsigned int attrs_prv = 0;

	if(at < 0 || at >= translate->input_len)
		return 0;

	if(uchar_prv == translate->input[at])
		return attrs_prv;
	uchar_prv = translate->input[at];
	return attrs_prv = table_get_character_attributes(translate->tables[translate->table_crs], translate->input[at]);
}
#endif

/******************************************************************************/

int translate_is_marked_name_at(const struct translate *translate, const unichar mark, const unichar *name, const int name_len, const int at)
{
	int i;

	if(at < 0 || at + name_len + 1 >= translate->input_len)
		return 0;
	if(translate->input[at] != mark)
		return 0;
	if(translate->input[at + name_len + 1] != mark)
		return 0;
	for(i = 0; i < name_len; i++)
	if(translate->input[at + 1 + i] != name[i])
		return 0;

	return 1;
}

enum mode_type translate_get_mode_indicator(const struct translate *translate, const struct table *table, const struct mode *mode)
{

	if(translate->input[translate->input_crs] != table->marker_hard && translate->input[translate->input_crs] != table->marker_soft)
		return NONE;

	if(translate_is_equal_at(translate, mode->begin, mode->begin_len, translate->input_crs + 1))
		return BEGIN;
	if(translate_is_equal_at(translate, mode->end, mode->end_len, translate->input_crs + 1))
		return END;
	if(translate_is_equal_at(translate, mode->word, mode->word_len, translate->input_crs + 1))
		return WORD;
	if(translate_is_equal_at(translate, mode->term, mode->term_len, translate->input_crs + 1))
		return TERM;
	if(translate_is_equal_at(translate, mode->symbol, mode->symbol_len, translate->input_crs + 1))
		return SYMBOL;

	return NONE;
}

/******************************************************************************/

int translate_check_output_max(struct translate *translate, const int increment)
{
	if(translate->output_len + increment < translate->output_max)
		return 1;

	while(translate->output_len + increment >= translate->output_max)
		translate->output_max += translate->output_inc;
	translate->output = REALLOC(translate->output, translate->output_max * sizeof(unichar));
	if(!translate->output)
	{
		LOG_ALLOCATE_FAIL
		return 0;
	}
	if(translate->maps_use)
	{
		translate->output_to_input_map = REALLOC(translate->output_to_input_map, translate->output_max * sizeof(int));
		if(!translate->output_to_input_map)
			return 0;
	}

	return 1;
}

/******************************************************************************/

int translate_skip(struct translate *translate, const int chars_cnt, const int clear_map)
{
	int cnt, i;

	/*   ensure chars_cnt is still within range   */
	if(translate->input_crs + chars_cnt > translate->input_len)
		cnt = translate->input_len - translate->input_crs;
	else
		cnt = chars_cnt;

	if(clear_map)
	if(translate->maps_use)
	for(i = 0; i < cnt; i++)
	if(translate->input_map[translate->input_crs + i] >= 0)
	{
		ASSERT(translate->input_crs + i < translate->input_len)
		translate->input_to_output_map[translate->input_map[translate->input_crs + i]] = -1;
	}

	translate_increment(translate, cnt, 0);

	return 1;
}

int translate_insert_dots(struct translate *translate, const unichar *dots, const int dots_len)
{
	int i;

	if(!translate_check_output_max(translate, dots_len))
		return 0;

	for(i = 0; i < dots_len; i++)
	{
		ASSERT(translate->output_len + i < translate->output_max)
		translate->output[translate->output_len + i] = dots[i];
		translate->output_mask[translate->output_len + i] = 0;

		if(translate->maps_use)
			translate->output_to_input_map[translate->output_len + i] = -1;
	}

	translate->output_len += dots_len;

	return 1;
}

int translate_insert_dots_for_chars(struct translate *translate, const unichar *dots, const int dots_len, const int chars_cnt)
{
	int i;

	if(!translate_check_output_max(translate, dots_len))
		return 0;

	for(i = 0; i < dots_len; i++)
	{
		ASSERT(translate->output_len + i < translate->output_max)
		translate->output[translate->output_len + i] = dots[i];
		translate->output_mask[translate->output_len + i] = 0;

		if(translate->maps_use)
			translate->output_to_input_map[translate->output_len + i] = translate->input_map[translate->input_crs];
	}
	if(translate->maps_use)
	for(i = 0; i < chars_cnt; i++)
		translate_remap_input(translate, i, 0);

	translate_increment(translate, chars_cnt, dots_len);

	return 1;
}

/******************************************************************************/

int translate_copy_to_output(struct translate *translate, const int count, const int do_map)
{
	int cnt, i;

	/*   ensure count is still within range   */
	if(translate->input_crs + count > translate->input_len)
		cnt = translate->input_len - translate->input_crs;
	else
		cnt = count;

	if(!translate_check_output_max(translate, cnt))
		return 0;

	for(i = 0; i < cnt; i++)
	{
		ASSERT(translate->output_len + i < translate->output_max)
		translate->output[translate->output_len + i] = translate->input[translate->input_crs + i];
		translate->output_mask[translate->output_len + i] = translate->input_mask[translate->input_crs + i];
		if(translate->maps_use)
		if(do_map)
		{
			translate->output_to_input_map[translate->output_len + i] = translate->input_map[translate->input_crs + i];
			translate_remap_input(translate, i, 0);
		}
		else
		{
			translate->output_to_input_map[translate->output_len + i] = -1;
			translate_remap_input(translate, i, 1);
		}
	}

	translate_increment(translate, cnt, cnt);

	return 1;
}

int translate_copy_marked_user(struct translate *translate)
{
	const struct table *table;
	int i;

	/*   only copy indicators from last table in tables
	     don't change translate->table_crs   */
	table = translate->tables[translate->table_cnt - 1];

	if(   translate->input[translate->input_crs] != table->marker_user
	   && translate->input[translate->input_crs] != table->marker_begin
	   && translate->input[translate->input_crs] != table->marker_end)
		return -1;

	for(i = translate->input_crs + 1; i < translate->input_len; i++)
	if(translate->input[i] == translate->input[translate->input_crs])
		break;

	return translate_copy_to_output(translate, i - translate->input_crs + 1, 0);
}

int translate_copy_marked_indicators(struct translate *translate)
{
	const struct table *table;
	int i;

	/*   only copy indicators from last table in tables
	     don't change translate->table_crs   */
	table = translate->tables[translate->table_cnt - 1];

	if(   translate->input[translate->input_crs] != table->marker_hard
	   && translate->input[translate->input_crs] != table->marker_soft)
		return -1;

	for(i = translate->input_crs + 1; i < translate->input_len; i++)
	if(translate->input[i] == translate->input[translate->input_crs])
		break;

	return translate_copy_to_output(translate, i - translate->input_crs + 1, 0);
}

int translate_copy_marked_indicators_or_modifiers(struct translate *translate)
{
	const struct table *table;
	int i;

	/*   only copy indicators from last table in tables
	     don't change translate->table_crs   */
	table = translate->tables[translate->table_cnt - 1];

	if(   translate->input[translate->input_crs] != table->marker_modifier
	   && translate->input[translate->input_crs] != table->marker_hard
	   && translate->input[translate->input_crs] != table->marker_soft)
		return -1;

	for(i = translate->input_crs + 1; i < translate->input_len; i++)
	if(translate->input[i] == translate->input[translate->input_crs])
		break;

	return translate_copy_to_output(translate, i - translate->input_crs + 1, 1);
}

/******************************************************************************/

int translate_output_to_input(struct translate *translate)
{
	FREE(translate->input);
	FREE(translate->input_mask);
	translate->input = translate->output;
	translate->input_mask = translate->output_mask;
	translate->input_len = translate->output_len;
	translate->input_crs = 0;

	translate->output = MALLOC(translate->output_max * sizeof(unichar));
	if(!translate->output)
	{
		LOG_ALLOCATE_FAIL
		return 0;
	}
	DB_MEMSET(translate->output, 0, translate->output_max * sizeof(unichar));
	translate->output_len = 0;

	translate->output_mask = MALLOC(translate->output_max);
	if(!translate->output_mask)
	{
		LOG_ALLOCATE_FAIL
		return -1;
	}
	memset(translate->output_mask, 0, translate->output_max);

	if(!translate->maps_use)
		return 1;

	FREE(translate->input_map);
	translate->input_map = translate->output_to_input_map;

	translate->output_to_input_map = MALLOC(translate->output_max * sizeof(int));
	if(!translate->output_to_input_map)
	{
		LOG_ALLOCATE_FAIL
		return 0;
	}
	DB_MEMSET(translate->output_to_input_map, -1, translate->output_max * sizeof(int));

	return 1;
}

/******************************************************************************/

static void convert_output(struct translate *translate, const struct conversion *conversion)
{
	int i;

	ASSERT(conversion)

	for(i = 0; i < translate->output_len; i++)
	if(translate->output[i] >= 0x2800 && translate->output[i] <= 0x28ff)
		translate->output[i] = conversion->converts[translate->output[i] & 0xff];
	else if(conversion->unknown)
		translate->output[i] = conversion->unknown;
}

static unichar convert_from_output(const struct conversion *conversion, const unichar uchar)
{
	int i;

	for(i = 0; i < 0x100; i++)
	if(uchar == conversion->converts[i])
		return i + 0x2800;

	return conversion->unknown;
}

static void convert_input(struct translate *translate, const struct conversion *conversion)
{
	int i;

	ASSERT(conversion)

	for(i = 0; i < translate->input_len; i++)
		translate->input[i] = convert_from_output(conversion, translate->input[i]);
}

/******************************************************************************/

int translate_generic_forward(struct translate *translate);
int translate_generic_backward(struct translate *translate);
int translate_nemeth_forward(struct translate *translate);

int translate_start(unichar *dots,
                    const int dots_len,
                    const unichar *chars,
                    const int chars_len,
                    const struct table *const*tables,
                    const int table_cnt,
                    const struct conversion *conversion,
                    const enum rule_direction direction,
                    int *chars_to_dots_map,
                    int *dots_to_chars_map,
                    int *cursor)
{
	struct translate translate_auto;
	int input_len, i, status;

	/*   nothing to translate   */
	if(chars_len == 0)
		return 0;

	/*   get true chars_len   */
	for(input_len = 0; input_len < chars_len; input_len++)
	if(!chars[input_len])
		break;

	memset(&translate_auto, 0, sizeof(struct translate));

	translate_auto.tables = tables;
	translate_auto.table_cnt = table_cnt;
	translate_auto.dots = dots;
	translate_auto.dots_len = dots_len;
	translate_auto.chars = chars;
	translate_auto.chars_len = chars_len;
	translate_auto.chars_to_dots_map = chars_to_dots_map;
	translate_auto.dots_to_chars_map = dots_to_chars_map;

	if(chars_to_dots_map == NULL || dots_to_chars_map == NULL)
		translate_auto.maps_use = 0;
	else
		translate_auto.maps_use = 1;

	/*   initialize input/output   */

	translate_auto.input = MALLOC((input_len + 1) * sizeof(unichar));
	if(!translate_auto.input)
	{
		LOG_ALLOCATE_FAIL
		return -1;
	}
	utf16_copy(translate_auto.input, chars, (input_len + 1));
	translate_auto.input_len = input_len;
	translate_auto.input_crs = 0;

	translate_auto.input_mask = MALLOC(input_len + 1);
	if(!translate_auto.input_mask)
	{
		LOG_ALLOCATE_FAIL
		return -1;
	}
	memset(translate_auto.input_mask, 0, input_len + 1);

	translate_auto.output_max = input_len;
	translate_auto.output_inc = ((translate_auto.output_max * 3) / 2) - translate_auto.output_max;
	if(translate_auto.output_inc < 0x100)
		translate_auto.output_inc = 0x100;
	translate_auto.output_max += translate_auto.output_inc - input_len;
	translate_auto.output = MALLOC(translate_auto.output_max * sizeof(unichar));
	if(!translate_auto.output)
	{
		LOG_ALLOCATE_FAIL
		FREE(translate_auto.input);
		return -1;
	}
	DB_MEMSET(translate_auto.output, 0, translate_auto.output_max * sizeof(unichar));

	translate_auto.output_mask = MALLOC(translate_auto.output_max);
	if(!translate_auto.output_mask)
	{
		LOG_ALLOCATE_FAIL
		return -1;
	}
	memset(translate_auto.output_mask, 0, translate_auto.output_max);

	if(cursor)
		translate_auto.cursor_pos = *cursor;

#ifndef CHECK_FOR_CHANGE
	utf16_copy(translate_auto.output, chars, (input_len + 1));
	translate_auto.output_len = input_len;
#endif

	if(translate_auto.maps_use)
	{
		translate_auto.input_map = MALLOC((input_len + 1) * sizeof(int));
		if(!translate_auto.input_map)
		{
			LOG_ALLOCATE_FAIL
			FREE(translate_auto.input);
			FREE(translate_auto.output);
			return -1;
		}
		for(i = 0; i <= input_len; i++)
			translate_auto.input_map[i] = i;

		translate_auto.input_to_output_map = MALLOC((input_len + 1) * sizeof(int));
		if(!translate_auto.input_to_output_map)
		{
			LOG_ALLOCATE_FAIL
			FREE(translate_auto.input);
			FREE(translate_auto.output);
			FREE(translate_auto.input_map);
			return -1;
		}

		/*   prevent input block mappings   */
		for(i = 0; i <= input_len; i++)
			translate_auto.input_to_output_map[i] = i;

		translate_auto.output_to_input_map = MALLOC(translate_auto.output_max * sizeof(int));
		if(!translate_auto.output_to_input_map)
		{
			LOG_ALLOCATE_FAIL
			FREE(translate_auto.input);
			FREE(translate_auto.output);
			FREE(translate_auto.input_map);
			FREE(translate_auto.input_to_output_map);
			return -1;
		}
		DB_MEMSET(translate_auto.output_to_input_map, 0, translate_auto.output_max * sizeof(int));

#ifndef CHECK_FOR_CHANGE
		ASSERT(translate_auto.output_max >= input_len + 1)
		memcpy(translate_auto.output_to_input_map, translate_auto.input_map, (input_len + 1) * sizeof(int));
#endif
	}

	/*   start processing   */
	if(direction == FORWARD)
	{
		/*   only process from last table in tables   */
		switch(translate_auto.tables[translate_auto.table_cnt - 1]->process)
		{
		case PROCESS_GENERIC:     status = translate_generic_forward(&translate_auto);  break;
		case PROCESS_NEMETH_UEB:  status = translate_nemeth_forward(&translate_auto);   break;
		default:                  status = 0;
		}
		if(status < 1)
		{
			if(status == 0)
				log_message(LOG_WARNING, "no processing done");
			translate_auto.output_len = status;
			goto free_and_return;
		}

		if(conversion)
			convert_output(&translate_auto, conversion);
	}
	else
	{
		ASSERT(direction == BACKWARD)

		if(conversion)
			convert_input(&translate_auto, conversion);

		/*   only process from last table in tables   */
		switch(translate_auto.tables[translate_auto.table_cnt - 1]->process)
		{
		case PROCESS_GENERIC:  status = translate_generic_backward(&translate_auto);  break;
		default:               status = 0;
		}
		if(status < 1)
		{
			if(status == 0)
				log_message(LOG_WARNING, "no processing done");
			translate_auto.output_len = status;
			goto free_and_return;
		}
	}

	/*   copy input/output   */

	if(translate_auto.output_len > translate_auto.dots_len)
	{
		//log_message(LOG_WARNING, "output exceeded dots_len:  %d > %d", translate_auto.output_len, translate_auto.dots_len);
		memcpy(dots, translate_auto.output, dots_len * sizeof(unichar));
		if(dots_to_chars_map)
			memcpy(dots_to_chars_map, translate_auto.output_to_input_map, dots_len * sizeof(int));
	}
	else
	{
		memcpy(dots, translate_auto.output, translate_auto.output_len * sizeof(unichar));
		if(dots_to_chars_map)
			memcpy(dots_to_chars_map, translate_auto.output_to_input_map, translate_auto.output_len * sizeof(int));
	}
	if(chars_to_dots_map)
		memcpy(chars_to_dots_map, translate_auto.input_to_output_map, input_len * sizeof(int));
	if(cursor)
		*cursor = translate_auto.cursor_pos;

	/*   finalize input/output   */

	free_and_return:

	FREE(translate_auto.input);
	FREE(translate_auto.output);
	FREE(translate_auto.input_mask);
	FREE(translate_auto.output_mask);
	if(translate_auto.maps_use)
	{
		FREE(translate_auto.input_map);
		FREE(translate_auto.input_to_output_map);
		FREE(translate_auto.output_to_input_map);
	}

	return translate_auto.output_len;
}

/******************************************************************************/
