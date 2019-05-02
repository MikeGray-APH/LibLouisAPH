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

#include "table-output.h"
#include "utf-output.h"

/******************************************************************************/

static void process_output(FILE *output, const enum table_process_type process)
{
	fputs("process:  ", output);
	switch(process)
	{
	case PROCESS_GENERIC:     fputs("generic\n", output);     break;
	case PROCESS_NEMETH_UEB:  fputs("nemeth-ueb\n", output);  break;
	}
}

static void character_output(FILE *output, const struct character *character)
{
	int i;

	utf16_output_char_escape(output, character->uchar);
	fputs("\t", output);
	fprintf(output, "0x%04x   0x%08x", character->uchar, character->attrs);

	fputs("   ", output);
	for(i = 0; i < UNICHAR_JOIN_MAX; i++)
	{
		fputs("[", output);
		if(character->joins[i])
			utf16_output_char_escape(output, character->joins[i]->uchar);
		else
			fputs(" ", output);
		fputs("]", output);
	}

	fputs("\n", output);
}

static void character_output_all(FILE *output, const struct table *table)
{
	struct character *character;
	int i;

	for(i = 0; i < TABLE_UNICHAR_HASH_SIZE; i++)
	{
		character = table->character_hash[i];
		while(character)
		{
			character_output(output, character);
			character = character->nxt;
		}
	}
}

static void character_hash_output(FILE *output, const struct table *table)
{
	struct character *character;
	int i, cnt, most;

	most = 0;
	for(i = 0; i < TABLE_UNICHAR_HASH_SIZE; i++)
	if(table->character_hash[i])
	{
		fprintf(output, "[%5d]", i);
		character = table->character_hash[i];
		cnt = 0;
		while(character)
		{
			cnt++;

			fputs(" ", output);
			if(is_space(character->uchar))
				fputs(" ", output);
			else
				utf16_output_char_escape(output, character->uchar);
			character = character->nxt;
		}
		fputs("\n", output);

		if(cnt > most)
			most = cnt;
	}
	fprintf(output, "most = %d\n", most);
}

static void mode_output(FILE *output, const struct mode *mode, const char *name)
{
	int i;

	if(!mode)
		return;

	mode_output(output, mode->nxt, name);

	fputs("   ", output);

	if(!mode->begin_len)
		fputs("-", output);
	else
	for(i = 0; i < mode->begin_len; i++)
	if(mode->begin[i])
		utf16_output_char(output, mode->begin[i]);

	fputs("  ", output);


	if(!mode->end_len)
		fputs("-", output);
	else
	for(i = 0; i < mode->end_len; i++)
	if(mode->end[i])
		utf16_output_char(output, mode->end[i]);

	if(mode->word_len)
	{

		fputs("  ", output);

		if(!mode->word_len)
			fputs("-", output);
		else
		for(i = 0; i < mode->word_len; i++)
		if(mode->word[i])
			utf16_output_char(output, mode->word[i]);

		fputs("  ", output);

		if(!mode->term_len)
			fputs("-", output);
		else
		for(i = 0; i < mode->term_len; i++)
		if(mode->term[i])
			utf16_output_char(output, mode->term[i]);

		fputs("  ", output);

		if(!mode->symbol_len)
			fputs("-", output);
		else
		for(i = 0; i < mode->symbol_len; i++)
		if(mode->symbol[i])
			utf16_output_char(output, mode->symbol[i]);

		fprintf(output, "  %d", mode->passage_len);
	}
	else
		fprintf(output, "  -  -  -  %d", mode->passage_len);

	fputs("  ", output);

	if(name)
		fprintf(output, "%s", name);
	else
		utf16_output(output, mode->name, mode->name_len);

	fputs("\n", output);

	mode = mode->nxt;
}

static char attrs_chars[32];

void pattern_print(FILE *output, const unichar *expr_data, const char *attrs_chars);

static void pattern_print_reverse(FILE *output, unichar *expr_data, const int expr_len)
{
	unichar *expr_rev;

	expr_rev = MALLOC(expr_len * sizeof(unichar));
	memcpy(expr_rev, expr_data, expr_len * sizeof(unichar));
	pattern_reverse(expr_rev);
	pattern_print(output, expr_rev, attrs_chars);
	FREE(expr_rev);
}

static void subpattern_output(FILE *output, const struct subpattern *subpattern)
{
	int i;

	if(!subpattern)
		return;

	subpattern_output(output, subpattern->nxt);

	fputs("   ", output);

	utf16_output(output, subpattern->tag, subpattern->tag_len);

	fputs("   ", output);

	utf16_output(output, subpattern->src_data, subpattern->src_len);

	for(i = 0; i < subpattern->src_len; i++)
	{
		if(subpattern->src_data[i] == u'\\')
		{
			i++;
			continue;
		}
		if(subpattern->src_data[i] == u'@')
		{
			fputs("   ", output);
			pattern_print(output, subpattern->expr_data, attrs_chars);
			break;
		}
	}

	fputs("\n", output);
}

static void filter_output(FILE *output, const struct filter *filter)
{
	if(!filter)
		return;

	filter_output(output, filter->nxt);

	fputs("   ", output);
	if(filter->name)
		utf16_output(output, filter->name, filter->name_len);
	else
		fputs("   -", output);

	fputs("   ", output);
	if(filter->before)
		pattern_print_reverse(output, filter->before, filter->before_len);
	else
		fputs("-", output);

	fputs("   ", output);
	if(filter->after)
		pattern_print(output, filter->after, attrs_chars);
	else
		fputs("-", output);

	fputs("\n", output);
}

static void output_dots_string(FILE *output, const unichar *dots, const int dots_len)
{
	int i;

	for(i = 0; i < dots_len; i++)
	{
		if(!(dots[i] & 0xff))
			fputs("0", output);
		if(dots[i] & 0x01)
			fputs("1", output);
		if(dots[i] & 0x02)
			fputs("2", output);
		if(dots[i] & 0x04)
			fputs("3", output);
		if(dots[i] & 0x08)
			fputs("4", output);
		if(dots[i] & 0x10)
			fputs("5", output);
		if(dots[i] & 0x20)
			fputs("6", output);
		if(dots[i] & 0x40)
			fputs("7", output);
		if(dots[i] & 0x80)
			fputs("8", output);
		if(i < dots_len - 1)
			fputs("-", output);
	}
}

static void rules_output(FILE *output, const struct rule *const*rule_hash, const int rules_max, const enum rule_direction direction, const int use_dots)
{
	const struct rule *rule;
	int i, cnt, most;

#ifdef TABLE_ALLOCATE_HASHES
	if(!rule_hash)
		return;
#endif

	most = 0;
	for(i = 0; i < rules_max; i++)
	{
		rule = rule_hash[i];
		cnt = 0;
		while(rule)
		{
			cnt++;
			if(direction == FORWARD)
				rule = rule->chars_nxt;
			else
				rule = rule->dots_nxt;
		}
		if(cnt > most)
			most = cnt;
		if(!cnt)
			continue;

		fprintf(output, "[%5d] %5d", i, cnt);
		rule = rule_hash[i];
		while(rule)
		{
			fputs("\n   ", output);

			if(direction == FORWARD)
			{
				if(rule->chars_len == 1)
					utf16_output_char_escape(output, rule->chars[0]);
				else
					utf16_output(output, rule->chars, rule->chars_len);
				fputs(" ", output);
				if(use_dots)
					output_dots_string(output, rule->dots, rule->dots_len);
				else
				if(rule->dots_len == 1)
					utf16_output_char_escape(output, rule->dots[0]);
				else
					utf16_output(output, rule->dots, rule->dots_len);
			}
			else
			{
				if(use_dots)
					output_dots_string(output, rule->dots, rule->dots_len);
				else
				if(rule->dots_len == 1)
					utf16_output_char_escape(output, rule->dots[0]);
				else
					utf16_output(output, rule->dots, rule->dots_len);
				fputs(" ", output);
				if(rule->chars_len == 1)
					utf16_output_char_escape(output, rule->chars[0]);
				else
					utf16_output(output, rule->chars, rule->chars_len);
			}
			if(rule->attrs)
				fprintf(output, " <0x%08x>", rule->attrs);

			if(rule->filter_forward)
			{
				fputs("   ", output);
				if(!rule->filter_forward->name)
				{
					if(rule->filter_forward->before)
						pattern_print_reverse(output, rule->filter_forward->before, rule->filter_forward->before_len);
					else
						fputs("-", output);
					fputs("   ", output);
					if(rule->filter_forward->after)
						pattern_print(output, rule->filter_forward->after, attrs_chars);
					else
						fputs("-", output);
				}
				else
					utf16_output(output, rule->filter_forward->name, rule->filter_forward->name_len);
			}

			if(rule->filter_backward)
			{
				fputs("   ", output);
				if(!rule->filter_forward)
					fputs("--   ", output);
				if(!rule->filter_backward->name)
				{
					if(rule->filter_backward->before)
						pattern_print_reverse(output, rule->filter_backward->before, rule->filter_backward->before_len);
					else
						fputs("-", output);
					fputs("   ", output);
					if(rule->filter_backward->after)
						pattern_print(output, rule->filter_backward->after, attrs_chars);
					else
						fputs("-", output);
				}
				else
					utf16_output(output, rule->filter_backward->name, rule->filter_backward->name_len);
			}

			if(direction == FORWARD)
				rule = rule->chars_nxt;
			else
				rule = rule->dots_nxt;
		}
		fputs("\n", output);
	}
	fprintf(output, "most = %d\n", most);
}

void table_output(FILE *output, const struct table *table)
{
	int i;

	if(!table)
		return;

	for(i = 0; i < 32; i++)
		attrs_chars[i] = table->attrs_chars[i];

	fprintf(output, "%s\n", table->file_name);
	process_output(output, table->process);
	fprintf(output, "\ncontrol:  0x%04x   0x%04x   0x%04x   0x%04x   0x%04x   0x%04x   0x%04x\n", table->marker_user, table->marker_begin, table->marker_end, table->marker_modifier, table->marker_hard, table->marker_soft, table->marker_internal);
	fputs("\ncharacters:\n", output);
	character_output_all(output, table);
	fputs("\ncharacter hash:\n", output);
	character_hash_output(output, table);
	fprintf(output, "\nmodes:  [%d]\n", table->emphases_cnt);
	mode_output(output, &table->nocontract, "nocontract");
	mode_output(output, &table->capital, "capital");
	mode_output(output, &table->numeric, "numeric");
	fprintf(output, "\nemphases:  [%d]\n", table->emphases_cnt);
	mode_output(output, table->emphases, NULL);
	fputs("\nsubpatterns:\n", output);
	subpattern_output(output, table->subpatterns);
	fputs("\nfilters:\n", output);
	filter_output(output, table->filters);

	fprintf(output, "\ninit chars hash:  [%d]\n", table->init_chars_hash_cnt);
	rules_output(output, (const struct rule* const*)table->init_chars_hash, TABLE_INIT_HASH_SIZE, FORWARD, 0);
	fprintf(output, "\ninit dots hash:  [%d]\n", table->init_dots_hash_cnt);
	rules_output(output, (const struct rule* const*)table->init_dots_hash, TABLE_DOTS_HASH_SIZE, BACKWARD, 0);

	fprintf(output, "\npremode chars hash:  [%d]\n", table->premode_chars_hash_cnt);
	rules_output(output, (const struct rule* const*)table->premode_chars_hash, TABLE_PREMODE_HASH_SIZE, FORWARD, 0);
	fprintf(output, "\npremode dots hash:  [%d]\n", table->premode_dots_hash_cnt);
	rules_output(output, (const struct rule* const*)table->premode_dots_hash, TABLE_DOTS_HASH_SIZE, BACKWARD, 0);

	fprintf(output, "\npostmode chars hash:  [%d]\n", table->postmode_chars_hash_cnt);
	rules_output(output, (const struct rule* const*)table->postmode_chars_hash, TABLE_POSTMODE_HASH_SIZE, FORWARD, 0);
	fprintf(output, "\npostmode dots hash:  [%d]\n", table->postmode_dots_hash_cnt);
	rules_output(output, (const struct rule* const*)table->postmode_dots_hash, TABLE_DOTS_HASH_SIZE, BACKWARD, 0);

	fprintf(output, "\npretrans chars hash:  [%d]\n", table->pretrans_chars_hash_cnt);
	rules_output(output, (const struct rule* const*)table->pretrans_chars_hash, TABLE_PRETRANS_HASH_SIZE, FORWARD, 0);
	fprintf(output, "\npretrans dots hash:  [%d]\n", table->pretrans_dots_hash_cnt);
	rules_output(output, (const struct rule* const*)table->pretrans_dots_hash, TABLE_DOTS_HASH_SIZE, BACKWARD, 0);

	fprintf(output, "\ntrans chars hash:  [%d]\n", table->trans_chars_hash_cnt);
	rules_output(output, (const struct rule* const*)table->trans_chars_hash, TABLE_TRANS_HASH_SIZE, FORWARD, 0);
	fprintf(output, "\ntrans dots hash:  [%d]\n", table->trans_dots_hash_cnt);
	rules_output(output, (const struct rule* const*)table->trans_dots_hash, TABLE_DOTS_HASH_SIZE, BACKWARD, 0);

	fprintf(output, "\nposttrans chars hash:  [%d]\n", table->posttrans_chars_hash_cnt);
	rules_output(output, (const struct rule* const*)table->posttrans_chars_hash, TABLE_POSTTRANS_HASH_SIZE, FORWARD, 0);
	fprintf(output, "\nposttrans dots hash:  [%d]\n", table->posttrans_dots_hash_cnt);
	rules_output(output, (const struct rule* const*)table->posttrans_dots_hash, TABLE_DOTS_HASH_SIZE, BACKWARD, 0);

	fprintf(output, "\nfini chars hash:  [%d]\n", table->fini_chars_hash_cnt);
	rules_output(output, (const struct rule* const*)table->fini_chars_hash, TABLE_FINI_HASH_SIZE, FORWARD, 0);
	fprintf(output, "\nfini dots hash:  [%d]\n", table->fini_dots_hash_cnt);
	rules_output(output, (const struct rule* const*)table->fini_dots_hash, TABLE_DOTS_HASH_SIZE, BACKWARD, 0);

	fflush(output);
}

/******************************************************************************/
