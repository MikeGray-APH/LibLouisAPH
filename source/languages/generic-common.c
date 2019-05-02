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

#include "pattern.h"
#include "generic.h"
#include "log.h"

#ifdef CHECK_FOR_CHANGE
#define CHANGE_MARK  translate->changed = 1;
#else
#define CHANGE_MARK
#endif

/******************************************************************************/

int generic_insert_marked(struct translate *translate, const unichar *indicator, const int indicator_len, const unichar delimiter)
{
	CHANGE_MARK

	if(delimiter)
	if(!translate_insert_dot(translate, delimiter))
		return 0;

	if(!translate_insert_dots(translate, indicator, indicator_len))
		return 0;

	if(delimiter)
	if(!translate_insert_dot(translate, delimiter))
		return 0;

	return 1;
}

/******************************************************************************/

static inline int get_next_delimiter(struct translate *translate, const int at, const unichar delimiter)
{
	int off;

	for(off = at + 1; off < translate->input_len; off++)
	if(translate->input[off] == delimiter)
		break;
	if(off >= translate->input_len)
		return 0;
	return off + 1;
}

int generic_remove_internal(struct translate *translate)
{
	const struct table *table;
	int off, crs;

	/*   only copy indicators from last table in tables   */
	table = translate->tables[translate->table_cnt - 1];
	translate->table_crs = translate->table_cnt - 1;

	off =
	crs = 0;
	while(off < translate->input_len)
	{
		if(translate->input[off] == table->marker_internal)
		{
			off = get_next_delimiter(translate, off, table->marker_internal);
			if(!off)
				return 0;
			CHANGE_MARK
		}
		else
		{
			translate->output[crs] = translate->input[off];
			if(translate->maps_use)
				translate->output_to_input_map[crs] = translate->input_map[off];
			off++;
			crs++;
			if(crs >= translate->output_max)
				return 0;
		}
	}

	translate->output_len = crs;

#ifdef DEBUG
	translate->output[translate->output_len] = 0;
#endif

	return 1;
}

int generic_remove_soft_delimiters(struct translate *translate)
{
	const struct table *table;
	int off, crs;

	/*   only copy indicators from last table in tables   */
	table = translate->tables[translate->table_cnt - 1];
	translate->table_crs = translate->table_cnt - 1;

	off =
	crs = 0;
	while(off < translate->input_len)
	{
		if(translate->input[off] == table->marker_soft)
		{
			off = get_next_delimiter(translate, off, table->marker_soft);
			if(!off)
				return 0;
			CHANGE_MARK
		}
		else
		{
			translate->output[crs] = translate->input[off];
			if(translate->maps_use)
				translate->output_to_input_map[crs] = translate->input_map[off];
			off++;
			crs++;
			if(crs >= translate->output_max)
				return 0;
		}
	}

	translate->output_len = crs;

#ifdef DEBUG
	translate->output[translate->output_len] = 0;
#endif

	return 1;
}

int generic_remove_modifier_delimiters(struct translate *translate)
{
	const struct table *table;

	/*   only remove indicators contained in last table in tables   */
	table = translate->tables[translate->table_cnt - 1];
	translate->table_crs = translate->table_cnt - 1;

	translate->input_crs =
	translate->output_len = 0;
	while(translate->input_crs < translate->input_len)
	{
		if(translate->input[translate->input_crs] == table->marker_modifier)
		{
			CHANGE_MARK
			if(!translate_skip(translate, 1, 0))
				return 0;
		}
		else if(!translate_copy_to_output(translate, 1, 1))
				return 0;
	}

#ifdef DEBUG
	translate->output[translate->output_len] = 0;
#endif

	return 1;
}

int generic_remove_hard_and_modifier_delimiters(struct translate *translate)
{
	const struct table *table;

	/*   only remove indicators contained in last table in tables   */
	table = translate->tables[translate->table_cnt - 1];
	translate->table_crs = translate->table_cnt - 1;

	translate->input_crs =
	translate->output_len = 0;
	while(translate->input_crs < translate->input_len)
	{
		if(   translate->input[translate->input_crs] == table->marker_modifier
		   || translate->input[translate->input_crs] == table->marker_hard)
		{
			CHANGE_MARK
			if(!translate_skip(translate, 1, 0))
				return 0;
		}
		else if(!translate_copy_to_output(translate, 1, 1))
			return 0;
	}

#ifdef DEBUG
	translate->output[translate->output_len] = 0;
#endif

	return 1;
}

/******************************************************************************/

#ifdef PATTERN_OUTPUT_TRACE

#include <stdio.h>

void debug_output_line(const unichar *uchars, const int uchars_len);
static enum table_hash_type current_hash_type;

static void output_hash_type(void)
{
	switch(current_hash_type)
	{
	case TABLE_HASH_NONE:       puts("TABLE_HASH_NONE");       break;
	case TABLE_HASH_INIT:       puts("TABLE_HASH_INIT");       break;
	case TABLE_HASH_PREMODE:    puts("TABLE_HASH_PREMODE");    break;
	case TABLE_HASH_POSTMODE:   puts("TABLE_HASH_POSTMODE");   break;
	case TABLE_HASH_PRETRANS:   puts("TABLE_HASH_PRETRANS");   break;
	case TABLE_HASH_TRANS:      puts("TABLE_HASH_TRANS");      break;
	case TABLE_HASH_POSTTRANS:  puts("TABLE_HASH_POSTTRANS");  break;
	case TABLE_HASH_FINI:       puts("TABLE_HASH_FINI");       break;
	}
}

#endif

static int rule_is_filtered(const struct translate *translate, const struct rule *rule, const enum rule_direction direction)
{
	if(direction == FORWARD)
	{
		if(!rule->filter_forward)
		{
#ifdef PATTERN_OUTPUT_TRACE
			puts("==========");
			output_hash_type();
			puts("forward = NULL");
			debug_output_line(rule->chars, rule->chars_len);
			debug_output_line(rule->dots, rule->dots_len);
			debug_output_line(translate->input, translate->input_len);
			for(int i = 0; i < translate->input_crs; i++)
				printf(" ");
			puts("^");
#endif
			return 0;
		}

		if(rule->filter_forward->before)
		{
#ifdef PATTERN_OUTPUT_TRACE
			puts("==========");
			output_hash_type();
			puts("forward-before");
			debug_output_line(rule->filter_forward->name, rule->filter_forward->name_len);
			debug_output_line(rule->chars, rule->chars_len);
			debug_output_line(rule->dots, rule->dots_len);
			debug_output_line(translate->input, translate->input_len);
			for(int i = 0; i < translate->input_crs; i++)
				printf(" ");
			puts("^");
#endif
			if(!pattern_check(translate, translate->input, translate->input_crs - 1, -1, -1, rule->filter_forward->before, NULL, translate->tables[translate->table_crs]->subpatterns))
				return 1;
		}

		if(rule->filter_forward->after)
		{
#ifdef PATTERN_OUTPUT_TRACE
			puts("==========");
			output_hash_type();
			puts("forward-after");
			debug_output_line(rule->filter_forward->name, rule->filter_forward->name_len);
			debug_output_line(rule->chars, rule->chars_len);
			debug_output_line(rule->dots, rule->dots_len);
			debug_output_line(translate->input, translate->input_len);
			for(int i = 0; i < translate->input_crs; i++)
				printf(" ");
			puts("^");
#endif
			if(!pattern_check(translate, translate->input, translate->input_crs + rule->chars_len, translate->input_len, 1, rule->filter_forward->after, NULL, translate->tables[translate->table_crs]->subpatterns))
				return 1;
		}
	}
	else
	{
		ASSERT(direction == BACKWARD)

		if(!rule->filter_backward)
		{
#ifdef PATTERN_OUTPUT_TRACE
			puts("==========");
			output_hash_type();
			puts("backward = NULL");
			debug_output_line(rule->chars, rule->chars_len);
			debug_output_line(rule->dots, rule->dots_len);
			debug_output_line(translate->input, translate->input_len);
			for(int i = 0; i < translate->input_crs; i++)
				printf(" ");
			puts("^");
#endif
			return 0;
		}

		if(rule->filter_backward->before)
		{
#ifdef PATTERN_OUTPUT_TRACE
			puts("==========");
			output_hash_type();
			puts("backward-before");
			debug_output_line(rule->filter_backward->name, rule->filter_backward->name_len);
			debug_output_line(rule->chars, rule->chars_len);
			debug_output_line(rule->dots, rule->dots_len);
			debug_output_line(translate->input, translate->input_len);
			for(int i = 0; i < translate->input_crs; i++)
				printf(" ");
			puts("^");
#endif
			if(!pattern_check(translate, translate->input, translate->input_crs - 1, -1, -1, rule->filter_backward->before, NULL, translate->tables[translate->table_crs]->subpatterns))
				return 1;
		}

		if(rule->filter_backward->after)
		{
#ifdef PATTERN_OUTPUT_TRACE
			puts("==========");
			output_hash_type();
			puts("backward-after");
			debug_output_line(rule->filter_backward->name, rule->filter_backward->name_len);
			debug_output_line(rule->chars, rule->chars_len);
			debug_output_line(rule->dots, rule->dots_len);
			debug_output_line(translate->input, translate->input_len);
			for(int i = 0; i < translate->input_crs; i++)
				printf(" ");
			puts("^");
#endif
			if(!pattern_check(translate, translate->input, translate->input_crs + rule->dots_len, translate->input_len, 1, rule->filter_backward->after, NULL, translate->tables[translate->table_crs]->subpatterns))
				return 1;
		}
	}

	return 0;
}

static const struct rule* generic_match_rule(struct translate *translate, const enum table_hash_type hash_type, const enum rule_direction direction, const unsigned int contract)
{
	const struct rule *rule;
	const unichar *input;
	int len;

	for(translate->table_crs = 0; translate->table_crs < translate->table_cnt; translate->table_crs++)
	{
		input = &translate->input[translate->input_crs];
		len = translate->input_len - translate->input_crs;

		rule = table_match_rule(translate->tables[translate->table_crs], hash_type, direction, input, len, NULL);

		while(rule)
		{
#ifdef PATTERN_OUTPUT_TRACE
			current_hash_type = hash_type;
#endif
			if(contract || !(rule->attrs & RULE_CONTRACTION))
			if(!rule_is_filtered(translate, rule, direction))
				return rule;

			rule = table_match_rule(translate->tables[translate->table_crs], hash_type, direction, input, len, rule);
		}
	}

	return NULL;
}

static int generic_apply_rule_forward(struct translate *translate, const struct rule *rule)
{
	int i;

	if(!translate_check_output_max(translate, rule->dots_len))
		return 0;

	for(i = 0; i < rule->dots_len; i++)
	{
		translate->output[translate->output_len + i] = rule->dots[i];

		if(translate->maps_use)
			translate->output_to_input_map[translate->output_len + i] = translate->input_map[translate->input_crs];
	}
	if(translate->maps_use)
	for(i = 0; i < rule->chars_len; i++)
		translate_remap_input(translate, i, 0);

	translate_increment(translate, rule->chars_len, rule->dots_len);

	return 1;
}

static int generic_apply_rule_backward(struct translate *translate, const struct rule *rule)
{
	int i;

	if(!translate_check_output_max(translate, rule->chars_len))
		return 0;

	for(i = 0; i < rule->chars_len; i++)
	{
		translate->output[translate->output_len + i] = rule->chars[i];

		if(translate->maps_use)
			translate->output_to_input_map[translate->output_len + i] = translate->input_map[translate->input_crs];
	}
	if(translate->maps_use)
	for(i = 0; i < rule->dots_len; i++)
		translate_remap_input(translate, i, 0);

	translate_increment(translate, rule->dots_len, rule->chars_len);

	return 1;
}

static int generic_apply_rule(struct translate *translate, const struct rule *rule, const enum rule_direction direction)
{
	switch(direction)
	{
	case FORWARD:   return generic_apply_rule_forward(translate, rule);
	case BACKWARD:  return generic_apply_rule_backward(translate, rule);
	case BOTH:  ;
	}

	ASSERT(0)
	return 0;
}

int generic_process(struct translate *translate, const enum table_hash_type hash_type, const enum rule_direction direction)
{
	const struct table *table;
	const struct rule *rule;
	enum mode_type nocontract_state;

	/*   only copy indicators from last table in tables   */
	table = translate->tables[translate->table_cnt - 1];

	/*   reset tracked cursor   */
	translate->cursor_set = 0;

	nocontract_state = NONE;

	translate->input_crs =
	translate->output_len = 0;
	while(translate->input_crs < translate->input_len)
	{
		/*   nocontract word stops on space   */
		if(nocontract_state == WORD)
		if(table_get_character_attributes(table, translate->input[translate->input_crs]) & CHAR_SPACE)
			nocontract_state = NONE;

		/*   nocontract   */
		switch(translate_get_mode_indicator(translate, table, &table->nocontract))
		{
		case FAIL:   return 0;
		case NONE:                              break;
		case BEGIN:  nocontract_state = BEGIN;  break;
		case WORD:   nocontract_state = WORD;   break;
		case END:
		case TERM:   nocontract_state = NONE;   break;

		case SYMBOL:

			/*   it is possible for symbol to be inside WORD or PASSAGE   */
			if(nocontract_state == NONE)
				nocontract_state = SYMBOL;
			break;
		}

		if(translate_copy_marked_indicators(translate) > 0)
			continue;

		/*   find rule   */
		rule = generic_match_rule(translate, hash_type, direction, nocontract_state == NONE);
		if(!rule)
		{
			if(!translate_copy_to_output(translate, 1, 1))
				return 0;
		}
		else
		{
			CHANGE_MARK
			if(!generic_apply_rule(translate, rule, direction))
				return 0;
		}

		/*   reset nocontract symbol   */
		if(nocontract_state == SYMBOL)
			nocontract_state = NONE;
	}

#ifdef DEBUG
	translate->output[translate->output_len] = 0;
#endif

	return 1;
}

/******************************************************************************/
