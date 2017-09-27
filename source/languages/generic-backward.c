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

#include "generic.h"

#ifdef CHECK_FOR_CHANGE
#define CHANGE_MARK  translate->changed = 1;
#else
#define CHANGE_MARK
#endif

/******************************************************************************/

/*   returns -1 on error, 0 when nothing skipped, <0 when input/output switch needed   */
static int convert_indicators_mode(struct translate *translate, const struct mode *mode, const Unicode delimiter)
{
	int cnt;

	cnt = 0;
	translate->input_crs =
	translate->output_len = 0;
	while(translate->input_crs < translate->input_len)
	{
		if(translate_copy_marked_indicators_or_modifiers(translate) > 0)
			continue;

		if(translate_is_equal(translate, mode->begin, mode->begin_len))
		{
			if(!translate_insert_dot(translate, delimiter))
				return -1;
			if(!translate_copy_to_output(translate, mode->begin_len, 1))
				return -1;
			if(!translate_insert_dot(translate, delimiter))
				return -1;
			cnt++;
		}
		else if(translate_is_equal(translate, mode->end, mode->end_len))
		{
			if(!translate_insert_dot(translate, delimiter))
				return -1;
			if(!translate_copy_to_output(translate, mode->end_len, 1))
				return -1;
			if(!translate_insert_dot(translate, delimiter))
				return -1;
			cnt++;
		}
		else if(translate_is_equal(translate, mode->word, mode->word_len))
		{
			if(!translate_insert_dot(translate, delimiter))
				return -1;
			if(!translate_copy_to_output(translate, mode->word_len, 1))
				return -1;
			if(!translate_insert_dot(translate, delimiter))
				return -1;
			cnt++;
		}
		else if(translate_is_equal(translate, mode->term, mode->term_len))
		{
			if(!translate_insert_dot(translate, delimiter))
				return -1;
			if(!translate_copy_to_output(translate, mode->term_len, 1))
				return -1;
			if(!translate_insert_dot(translate, delimiter))
				return -1;
			cnt++;
		}
		else if(translate_is_equal(translate, mode->symbol, mode->symbol_len))
		{
			if(!translate_insert_dot(translate, delimiter))
				return -1;
			if(!translate_copy_to_output(translate, mode->symbol_len, 1))
				return -1;
			if(!translate_insert_dot(translate, delimiter))
				return -1;
			cnt++;
		}
		else if(!translate_copy_to_output(translate, 1, 1))
			return -1;
	}

	return cnt;
}

static int convert_indicators_emphases(struct translate *translate, const struct table *table)
{
	struct mode *mode, mode_auto;
	int cnt;

	translate->input_crs =
	translate->output_len = 0;

	mode = table->emphases;
	while(mode)
	{
		cnt = convert_indicators_mode(translate, mode, table->marker_soft);
		if(cnt < 0)
			return 0;
#ifdef CHECK_FOR_CHANGE
		else if(cnt > 0)
			CHANGE_MARK
#endif
		mode = mode->nxt;

		if(cnt > 0)
		if(!translate_output_to_input(translate))
			return 0;
	}

	if(translate_is_nocontract_set(translate))
	{
		cnt = convert_indicators_mode(translate, &table->nocontract, table->marker_soft);
		if(cnt < 0)
			return 0;
		else if(cnt > 0)
		{
			CHANGE_MARK
			if(!translate_output_to_input(translate))
				return 0;
		}
	}

	if(translate_is_capital_set(translate))
	{
		cnt = convert_indicators_mode(translate, &table->capital, table->marker_soft);
		if(cnt < 0)
			return 0;
		else if(cnt > 0)
		{
			CHANGE_MARK
			if(!translate_output_to_input(translate))
				return 0;
		}
	}

	if(translate_is_numeric_set(translate))
	{
		mode_auto = table->numeric;
		mode_auto.symbol_len = 0;
		cnt = convert_indicators_mode(translate, &mode_auto, table->marker_soft);
		if(cnt < 0)
			return 0;
		else if(cnt > 0)
		{
			CHANGE_MARK
			if(!translate_output_to_input(translate))
				return 0;
		}
	}

#ifdef DEBUG
	translate->output[translate->output_len] = 0;
#endif

	return 1;
}

/******************************************************************************/

static int convert_indicators_capital(struct translate *translate)
{
	const struct table *table;
	int capital_in, numeric_in;
	Unicode upper;

	/*   only remove indicators contained in last table in tables   */
	table = translate->tables[translate->table_cnt - 1];
	translate->table_crs = translate->table_cnt - 1;

	capital_in =
	numeric_in = 0;

	translate->input_crs =
	translate->output_len = 0;
	while(translate->input_crs < translate->input_len)
	{
		switch(translate_get_mode_indicator(translate, table, &table->numeric))
		{
		case FAIL:  return 0;

		case BEGIN:
		case WORD:  numeric_in = 1;  break;

		case END:
		case TERM:

			if(capital_in < 3) 
				capital_in = 0;
			numeric_in = 0;
			break;

		/*   numeric space   */
		case SYMBOL:
		case NONE:  break;
		}

		if(numeric_in)
		{
			if(translate_copy_marked_indicators(translate) > 0)
				continue;
			if(!translate_copy_to_output(translate, 1, 1))
				return 0;
			continue;
		}

		switch(translate_get_mode_indicator(translate, table, &table->capital))
		{
		case FAIL:  return 0;
		case NONE:  break;

		case BEGIN:   capital_in = 3;  break;
		case WORD:    capital_in = 2;  break;
		case SYMBOL:  capital_in = 1;  break;

		case END:
		case TERM:  capital_in = 0; break;
		}


		if(translate_copy_marked_indicators(translate) > 0)
			continue;

		if(capital_in)
		{
			if(capital_in < 3 && translate_has_attributes(translate, (CHAR_SPACE | CHAR_SEQUENCE_DELIMITER)))
			{
				capital_in = 0;
				if(!translate_copy_to_output(translate, 1, 1))
					return 0;
				continue;
			}

			if(capital_in == 2 && !translate_has_attributes(translate, CHAR_LETTER))
			{
				capital_in = 0;
				if(!translate_copy_to_output(translate, 1, 1))
					return 0;
				continue;
			}

			upper = generic_lower_to_upper(translate->tables[translate->table_crs], translate->input[translate->input_crs]);
			if(upper != translate->input[translate->input_crs])
			{
				CHANGE_MARK
				if(!translate_insert_dot_for_chars(translate, upper, 1))
					return 0;
			}
			else if(!translate_copy_to_output(translate, 1, 1))
				return 0;
		}
		else if(!translate_copy_to_output(translate, 1, 1))
			return 0;

		if(capital_in == 1)
			capital_in = 0;
	}

#ifdef DEBUG
	translate->output[translate->output_len] = 0;
#endif

	return 1;
}

/******************************************************************************/

static int add_soft_terminators(struct translate *translate)
{
	const struct table *table;
	int numeric_in, numeric_passage_in, nocontract_in;

	numeric_in =
	numeric_passage_in =
	nocontract_in = 0;

	/*   only copy indicators contained in last table in tables   */
	table = translate->tables[translate->table_cnt - 1];
	translate->table_crs = translate->table_cnt - 1;

	translate->input_crs =
	translate->output_len = 0;
	while(translate->input_crs < translate->input_len)
	{
		switch(translate_get_mode_indicator(translate, table, &table->numeric))
		{
		case FAIL:  return 0;

		case BEGIN:

			numeric_passage_in = 1;

			if(!nocontract_in)
			{
				nocontract_in = 1;

				/*   don't start if there is no end   */
				if(table->nocontract.begin_len && table->nocontract.end_len)
				if(!generic_insert_marked(translate, table->nocontract.begin, table->nocontract.begin_len, table->marker_soft))
					return 0;
			}

			/*   copy indicator now so it doesn't turn off numeric mode later   */
			if(translate_copy_marked_indicators(translate) < 0)
				return 0;

			continue;

		case END:

			numeric_passage_in = 0;

			if(translate_copy_marked_indicators(translate) < 0)
				return 0;

			nocontract_in = 0;

			if(table->nocontract.end_len)
			if(!generic_insert_marked(translate, table->nocontract.end, table->nocontract.end_len, table->marker_soft))
				return 0;

			continue;

		case WORD:

			numeric_in = 1;

			if(!nocontract_in)
			{
				nocontract_in = 1;

				/*   don't start a word if there is no terminator   */
				if(table->nocontract.word_len && table->nocontract.term_len)
				if(!generic_insert_marked(translate, table->nocontract.word, table->nocontract.word_len, table->marker_soft))
					return 0;
			}

			/*   copy indicator now so it doesn't turn off numeric mode later   */
			if(translate_copy_marked_indicators(translate) < 0)
				return 0;

			continue;

		case TERM:  numeric_in = 0; break;

		/*   numeric space   */
		case SYMBOL:
		case NONE:  break;
		}

		if(numeric_passage_in)
		{
			if(!translate_copy_to_output(translate, 1, 1))
				return 0;
			continue;
		}

		/*   assume that valid digit chars are free of indicators and modifiers   */
		if(translate_on_indicator_or_modifier_marker(translate))
		{
			if(numeric_in)
			{
				numeric_in = 0;
				CHANGE_MARK

				/*   put end before marked indicator   */
				if(table->numeric.end_len)
				if(!generic_insert_marked(translate, table->numeric.end, table->numeric.end_len, table->marker_soft))
					return 0;
			}
			if(translate_copy_marked_indicators_or_modifiers(translate) < 0)
				return 0;

			continue;
		}

		if(numeric_in)
		{
			if(translate_has_attributes(translate, (CHAR_SPACE | CHAR_SEQUENCE_DELIMITER)))
			{
				numeric_in = 0;
				CHANGE_MARK

				if(table->numeric.end_len)
				if(!generic_insert_marked(translate, table->numeric.end, table->numeric.end_len, table->marker_soft))
					return 0;

				nocontract_in = 0;
				if(table->nocontract.term_len)
				{
					/*   put terminator after delimiter (because of dashes)   */
					if(!translate_copy_to_output(translate, 1, 1))
						return 0;

					if(!generic_insert_marked(translate, table->nocontract.term, table->nocontract.term_len, table->marker_soft))
						return 0;

					continue;
				}
			}
			else if(!translate_has_attributes(translate, CHAR_NUMERIC_UCHAR | CHAR_NUMERIC_CONT))
			{
				numeric_in = 0;
				CHANGE_MARK

				if(table->numeric.end_len)
				if(!generic_insert_marked(translate, table->numeric.end, table->numeric.end_len, table->marker_soft))
					return 0;
			}
		}
		else if(nocontract_in)
		{
			if(translate_has_attributes(translate, (CHAR_SPACE | CHAR_SEQUENCE_DELIMITER)))
			{
				nocontract_in = 0;
				if(table->nocontract.term_len)
				{
					/*   put terminator after delimiter (because of dashes)   */
					if(!translate_copy_to_output(translate, 1, 1))
						return 0;

					if(!generic_insert_marked(translate, table->nocontract.term, table->nocontract.term_len, table->marker_soft))
						return 0;

					continue;
				}
			}
		}

		if(!translate_copy_to_output(translate, 1, 1))
			return 0;
	}

	/*   this may not be necessary, here for consistency   */
	if(numeric_in)
	{
		if(table->numeric.end_len)
		if(!generic_insert_marked(translate, table->numeric.end, table->numeric.end_len, table->marker_soft))
			return 0;

		if(table->nocontract.term_len)
		if(!generic_insert_marked(translate, table->nocontract.term, table->nocontract.term_len, table->marker_soft))
			return 0;
	}
	else if(nocontract_in)
	if(table->nocontract.term_len)
	if(!generic_insert_marked(translate, table->nocontract.term, table->nocontract.term_len, table->marker_soft))
		return 0;

#ifdef DEBUG
	translate->output[translate->output_len] = 0;
#endif

	return 1;
}

/******************************************************************************/

static int convert_indicators_numeric(struct translate *translate)
{
	const struct table *table;
	int numeric_in, numeric_passage_in;
	Unicode uchar;

	/*   only remove indicators contained in last table in tables   */
	table = translate->tables[translate->table_cnt - 1];
	translate->table_crs = translate->table_cnt - 1;

	numeric_in =
	numeric_passage_in = 0;
	translate->input_crs =
	translate->output_len = 0;
	while(translate->input_crs < translate->input_len)
	{
		switch(translate_get_mode_indicator(translate, table, &table->numeric))
		{
		case FAIL:  return 0;
		case NONE:  break;

		case BEGIN:  numeric_passage_in = 1;
		case WORD:   numeric_in = 1;  break;

		case END:   numeric_passage_in = 0;
		case TERM:

			/*   numeric terminator is also nocontract symbol   */
			if(!numeric_passage_in)
				numeric_in = 0;
			break;

		/*   numeric space   */
		case SYMBOL:  break;
		}

		/*   treat nocontract symbol like an escape   */
		if(numeric_passage_in)
		if(translate_get_mode_indicator(translate, table, &table->nocontract) == SYMBOL)
		{
			if(!(translate_copy_marked_indicators(translate) > 0))
				return 0;
			if(!translate_copy_to_output(translate, 1, 1))
				return 0;
			continue;
		}

		if(translate_copy_marked_indicators(translate) > 0)
			continue;

		if(numeric_in)
		{
			/*   numeric space   */
			if(translate_is_equal(translate, table->numeric.symbol, table->numeric.symbol_len))
			{
				CHANGE_MARK
				if(!translate_insert_dot_for_chars(translate, u' ', table->numeric.symbol_len))
					return 0;
			}
			else if(!numeric_passage_in && !translate_has_attributes(translate, CHAR_NUMERIC_UCHAR | CHAR_NUMERIC_CONT))
			{
				numeric_in = 0;
				if(!translate_copy_to_output(translate, 1, 1))
					return 0;
			}
			else
			{
				uchar = generic_uchar_to_digit(table, translate->input[translate->input_crs]);
				if(uchar != translate->input[translate->input_crs])
				{
					CHANGE_MARK
					if(!translate_insert_dot_for_chars(translate, uchar, 1))
						return 0;
				}
				else if(!translate_copy_to_output(translate, 1, 1))
					return 0;
			}
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

#ifdef CHECK_FOR_CHANGE
#define CHANGE_RESET  translate->changed = 0;
#define CHANGE_CHECK  if(translate->changed)
#else
#define CHANGE_RESET
#define CHANGE_CHECK
#endif

int translate_generic_backward(struct translate *translate)
{
	int processed;

	processed = 0;

	if(translate_get_init_dots_hash_cnt(translate))
	{
		CHANGE_RESET
		if(!generic_process(translate, TABLE_HASH_INIT, BACKWARD))
			return 0;
		CHANGE_CHECK
		processed = 1;
	}

	CHANGE_CHECK
	if(!translate_output_to_input(translate))
		return 0;

	/*   does its own swapping   */
	if(!convert_indicators_emphases(translate, translate->tables[translate->table_cnt - 1]))
		return 0;
	processed = 0;

	CHANGE_RESET
	if(!add_soft_terminators(translate))
		return 0;
	CHANGE_CHECK
	processed = 1;

	CHANGE_CHECK
	if(!translate_output_to_input(translate))
		return 0;

	CHANGE_RESET
	if(!generic_remove_modifier_delimiters(translate))
		return 0;
	CHANGE_CHECK
	processed = 1;

	if(translate_get_posttrans_dots_hash_cnt(translate))
	{
		CHANGE_CHECK
		if(!translate_output_to_input(translate))
			return 0;

		CHANGE_RESET
		if(!generic_process(translate, TABLE_HASH_POSTTRANS, BACKWARD))
			return 0;
		CHANGE_CHECK
		processed = 1;
	}

	if(translate_get_trans_dots_hash_cnt(translate))
	{
		CHANGE_CHECK
		if(!translate_output_to_input(translate))
			return 0;

		CHANGE_RESET
		if(!generic_process(translate, TABLE_HASH_TRANS, BACKWARD))
			return 0;
		CHANGE_CHECK
		processed = 1;
	}

	if(translate_get_pretrans_dots_hash_cnt(translate))
	{
		CHANGE_CHECK
		if(!translate_output_to_input(translate))
			return 0;

		CHANGE_RESET
		if(!generic_process(translate, TABLE_HASH_PRETRANS, BACKWARD))
			return 0;
		CHANGE_CHECK
		processed = 1;
	}

	if(translate_get_postmode_dots_hash_cnt(translate))
	{
		CHANGE_CHECK
		if(!translate_output_to_input(translate))
			return 0;

		CHANGE_RESET
		if(!generic_process(translate, TABLE_HASH_POSTMODE, BACKWARD))
			return 0;
		CHANGE_CHECK
		processed = 1;
	}

	if(translate_is_capital_set(translate))
	{
		CHANGE_CHECK
		if(!translate_output_to_input(translate))
			return 0;

		CHANGE_RESET
		convert_indicators_capital(translate);
		CHANGE_CHECK
		processed = 1;
	}

	if(translate_is_numeric_set(translate))
	{
		CHANGE_CHECK
		if(!translate_output_to_input(translate))
			return 0;

		CHANGE_RESET
		convert_indicators_numeric(translate);
		CHANGE_CHECK
		processed = 1;
	}

	if(translate_get_premode_dots_hash_cnt(translate))
	{
		CHANGE_CHECK
		if(!translate_output_to_input(translate))
			return 0;

		CHANGE_RESET
		if(!generic_process(translate, TABLE_HASH_PREMODE, BACKWARD))
			return 0;
		CHANGE_CHECK
		processed = 1;
	}

	CHANGE_CHECK
	if(!translate_output_to_input(translate))
		return 0;

	CHANGE_RESET
	if(!generic_remove_soft_delimiters(translate))
		return 0;
	CHANGE_CHECK
	processed = 1;

	CHANGE_CHECK
	if(!translate_output_to_input(translate))
		return 0;

	CHANGE_RESET
	if(!generic_remove_hard_and_modifier_delimiters(translate))
		return 0;
	CHANGE_CHECK
	processed = 1;

	if(translate_get_fini_dots_hash_cnt(translate))
	{
		CHANGE_CHECK
		if(!translate_output_to_input(translate))
			return 0;

		CHANGE_RESET
		if(!generic_process(translate, TABLE_HASH_FINI, BACKWARD))
			return 0;
		CHANGE_CHECK
		processed = 1;
	}

	return processed;
}

/******************************************************************************/
