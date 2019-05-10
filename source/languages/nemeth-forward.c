/*

   Copyright 2018 American Printing House for the Blind Inc.

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

#include "generic.h"
#include "log.h"

#ifdef CHECK_FOR_CHANGE
#define CHANGE_MARK  translate->changed = 1;
#else
#define CHANGE_MARK
#endif

/******************************************************************************/

enum NEMETH_CHAR_DOT_ATTRIBUTE
{
	NEMETH_SPACE = BIT(0),
	NEMETH_DIGIT = BIT(1),
	NEMETH_LETTER = BIT(2),
	NEMETH_DECIMAL_SEPARATOR = BIT(3),
	NEMETH_DECIMAL_MINUS = BIT(4),
	NEMETH_SCRIPT_THRU = BIT(5),
	NEMETH_COMPARATOR = BIT(6),
};

/******************************************************************************/

#define SEPS_MAX 225

static int convert_nemeth_roots(struct translate *translate)
{
	unichar levels[SEPS_MAX];
	int level_cnt;

	translate->table_crs = translate->table_cnt - 1;

	level_cnt =
	translate->input_crs =
	translate->output_len = 0;
	while(translate->input_crs < translate->input_len)
	{
		switch(translate->input[translate->input_crs])
		{

		case u'\uf5b0':/*   start root   */
		case u'\uf5b3':/*   start square root   */

			CHANGE_MARK
			if(level_cnt)
			if(!translate_insert_dots(translate, levels, level_cnt))
				return 0;
			levels[level_cnt++] = u'⠨';
			break;

		case u'\uf5b2':/*   end root   */
		case u'\uf5b4':/*   end square root   */

			CHANGE_MARK
			level_cnt--;
			if(level_cnt)
			if(!translate_insert_dots(translate, levels, level_cnt))
				return 0;
			break;

		case u'\uf5b1':/*   enter root   */
		default: ;
		}

		if(!translate_copy_to_output(translate, 1, 1))
			return 0;
	}

#ifdef DEBUG
	translate->output[translate->output_len] = 0;
#endif

	return 1;
}

/******************************************************************************/

static int convert_nemeth_scripts(struct translate *translate)
{
//	const unichar sub_beg       = u'\uf580';
	const unichar sub_sep       = u'\uf581';
	const unichar sub_end       = u'\uf582';
//	const unichar sup_beg       = u'\uf583';
//	const unichar sup_sep       = u'\uf584';
	const unichar sup_end       = u'\uf585';
//	const unichar sbp_beg       = u'\uf586';
	const unichar sbp_sep       = u'\uf587';
	const unichar sbp_end       = u'\uf588';
	const unichar base_sub      = u'⠰';
	const unichar base_sup      = u'⠘';
	const unichar base_reset    = u'⠐';
	const unichar script_comma  = u'⠪';
	const unichar not_slash     = u'⠌';
	unichar seps[SEPS_MAX];
	int sep_cnt, sub_letter_digit, need_reset, sbp_cnt, crs, seq;

	translate->table_crs = translate->table_cnt - 1;

	sep_cnt =
	sbp_cnt =
	sub_letter_digit =
	translate->input_crs =
	translate->output_len = 0;

	while(translate->input_crs < translate->input_len)
	{
		switch(translate->input[translate->input_crs])
		{
		case TABLE_MARKER_INTERNAL:

			if(!translate_copy_to_output(translate, 1, 1))
				return 0;

			/*   find ending marker   */
			crs = translate->input_crs;
			while(crs < translate->input_len)
			{
				if(translate->input[crs] == TABLE_MARKER_INTERNAL)
					break;
				crs++;
			}
			if(crs >= translate->input_len)
				return 0;//TODO:  log error

			/*   check thru-comparator rule   */
			if(sep_cnt)
			{
				if(translate_has_attributes(translate, NEMETH_SCRIPT_THRU))
				{
					if(crs + 2 < translate->input_len)
					if(translate->input[crs + 1] == TABLE_MARKER_INTERNAL)
					if(translate_has_attributes_at(translate, crs + 2, NEMETH_COMPARATOR))
					{
						sep_cnt = 0;
						crs += 2;
						while(crs < translate->input_len)
						{
							if(translate->input[crs] == TABLE_MARKER_INTERNAL)
								break;
							crs++;
						}
						if(crs >= translate->input_len)
							return 0;//TODO:  log error
					}
				}
				else if(translate_has_attributes(translate, NEMETH_COMPARATOR))
				{
					CHANGE_MARK
					if(!translate_insert_dots(translate, seps, sep_cnt))
						return 0;
				}
				else if(translate->input[translate->input_crs] == not_slash)
				{
					if(translate_has_attributes_at(translate, translate->input_crs + 1, NEMETH_COMPARATOR))
					if(!translate_insert_dots(translate, seps, sep_cnt))
						return 0;
				}
			}

			if(!translate_copy_to_output(translate, crs - translate->input_crs + 1, 1))
				return 0;
			break;

		case u'\uf580':/*   start subscript   */

			/*   first level letter-number subscript rule   */
			sub_letter_digit = 0;
			if(sep_cnt == 0)
			{
				crs = translate->input_crs + 1;

				/*   check letter   */
				if(translate_has_attributes_at(translate, crs, NEMETH_LETTER))
				{
					crs++;

					/*   check primes   */
					while(crs < translate->input_len &&
					      (   translate->input[crs] == u'\u2032'
					       || translate->input[crs] == u'\u2033'
					       || translate->input[crs] == u'\u2034'
					       || translate->input[crs] == u'\u2057')
					      )
						crs++;

					/*   check separator indicator   */
					if(crs < translate->input_len)
					if(translate->input[crs] == sub_sep)
					{
						crs++;

						/*   check digits   */
						while(crs < translate->input_len)
						{
							if(!translate_has_attributes_at(translate, crs, NEMETH_DIGIT))
								break;
							crs++;
						}

						/*   check end indicator   */
						if(crs < translate->input_len)
						if(translate->input[crs] == sub_end)
							sub_letter_digit = 1;
					}
				}
			}
			if(sub_letter_digit)
			{
				CHANGE_MARK

				/*   skip begin indicator   */
				translate_skip(translate, 1, 1);

				/*   copy letter   */
				if(!translate_copy_to_output(translate, 1, 1))
					return 0;

				/*   copy primes   */
				while(   translate->input[translate->input_crs] == u'\u2032'
				      || translate->input[translate->input_crs] == u'\u2033'
				      || translate->input[translate->input_crs] == u'\u2034'
				      || translate->input[translate->input_crs] == u'\u2057')
				if(!translate_copy_to_output(translate, 1, 1))
					return 0;

				/*   skip separator indicator   */
				translate_skip(translate, 1, 1);

				/*   copy digits   */
				while(translate->input[translate->input_crs] != sub_end)
				if(!translate_copy_to_output(translate, 1, 1))
					return 0;
			}
			goto start_script;

		case u'\uf586':/*   start sbpscript   */

			/*   first level letter-number subscript rule   */
			sub_letter_digit = 0;
			if(sep_cnt == 0)
			{
				crs = translate->input_crs + 1;

				/*   check letter   */
				if(translate_has_attributes_at(translate, crs, NEMETH_LETTER))
				{
					crs++;

					/*   check primes   */
					while(crs < translate->input_len &&
					      (   translate->input[crs] == u'\u2032'
					       || translate->input[crs] == u'\u2033'
					       || translate->input[crs] == u'\u2034'
					       || translate->input[crs] == u'\u2057')
					      )
						crs++;

					/*   check separator indicator   */
					if(crs < translate->input_len)
					if(translate->input[crs] == sbp_sep)
					{
						crs++;

						/*   check digits   */
						while(crs < translate->input_len)
						{
							if(!translate_has_attributes_at(translate, crs, NEMETH_DIGIT))
								break;
							crs++;
						}

						/*   check end indicator   */
						if(crs < translate->input_len)
						if(translate->input[crs] == sbp_sep)
							sub_letter_digit = 1;
					}
				}
			}
			if(sub_letter_digit)
			{
				CHANGE_MARK

				/*   skip begin indicator   */
				translate_skip(translate, 1, 1);

				/*   copy letter   */
				if(!translate_copy_to_output(translate, 1, 1))
					return 0;

				/*   copy primes   */
				while(   translate->input[translate->input_crs] == u'\u2032'
				      || translate->input[translate->input_crs] == u'\u2033'
				      || translate->input[translate->input_crs] == u'\u2034'
				      || translate->input[translate->input_crs] == u'\u2057')
				if(!translate_copy_to_output(translate, 1, 1))
					return 0;

				/*   skip separator indicator   */
				translate_skip(translate, 1, 1);

				/*   copy digits   */
				while(translate->input[translate->input_crs] != sbp_sep)
				if(!translate_copy_to_output(translate, 1, 1))
					return 0;

				/*   switch to superscript   */
				seps[sep_cnt++] = base_sup;
				if(!translate_insert_dots(translate, seps, sep_cnt))
					return 0;
			}
			else
				sbp_cnt = 0;

		case u'\uf583':/*   start supscript   */

			start_script:

			/*   skip start/fiinish indicator   */
			translate_skip(translate, 1, 1);
			break;

		case u'\uf581':/*   enter subscript   */

			CHANGE_MARK
			seps[sep_cnt++] = base_sub;
			goto enter_script;
			break;

		case u'\uf584':/*   enter supscript   */

			CHANGE_MARK
			seps[sep_cnt++] = base_sup;
			goto enter_script;
			break;

		case u'\uf587':/*   enter sbpscript   */

			enter_sbpscript:
			CHANGE_MARK
			if(sbp_cnt == 0)
			{
				sbp_cnt++;
				seps[sep_cnt++] = base_sub;
			}
			else
			{
				sep_cnt--;
				seps[sep_cnt++] = base_sup;
			}

			enter_script:
			translate_skip(translate, 1, 1);
			if(!translate_insert_dots(translate, seps, sep_cnt))
				return 0;
			if(translate->input[translate->input_crs] == TABLE_MARKER_INTERNAL)
			{
				translate_skip(translate, 1, 1);
				crs = translate->input_crs;
				while(crs < translate->input_len)
				{
					if(translate->input[crs] == TABLE_MARKER_INTERNAL)
						break;
					crs++;
				}
				if(crs >= translate->input_len)
					return 0;//TODO:  log error
				if(!translate_copy_to_output(translate, crs - translate->input_crs + 1, 1))
					return 0;
			}
			break;

		case u'\uf588':  sbp_cnt--;  /*   finish sbpscript   */
		case u'\uf582':              /*   finish subscript   */
		case u'\uf585':              /*   finish supscript   */

			sep_cnt--;

			/*   skip all finishes   */
			crs = translate->input_crs + 1;
			while(crs < translate->input_len)
			{
				if(   translate->input[crs] == sub_end
				   || translate->input[crs] == sup_end
				   || translate->input[crs] == sbp_end)
				{
					sep_cnt--;
					crs++;
				}
				else
					break;
			}
			translate_skip(translate, crs - translate->input_crs, 1);

			/*   is reset needed?   */
			if(translate->input[translate->input_crs] == u'\uf587')
				goto enter_sbpscript;
			need_reset =
			crs = 0;
			if(translate->input_crs < translate->input_len)
			{
				if(translate->input[translate->input_crs] == TABLE_MARKER_INTERNAL)
				{
					/*   find ending marker   */
					crs = translate->input_crs + 1;
					while(crs < translate->input_len)
					{
						if(translate->input[crs] == TABLE_MARKER_INTERNAL)
							break;
						crs++;
					}
					if(crs >= translate->input_len)
						return 0;//TODO:  log error

					if(translate_has_attributes_at(translate, translate->input_crs + 1, NEMETH_SCRIPT_THRU))
					{
						if(crs + 1 >= translate->input_len)
							need_reset = 1;
						else if(translate->input[crs + 1] != TABLE_MARKER_INTERNAL)
							need_reset = 1;
						else if(translate_has_attributes_at(translate, crs + 2, NEMETH_COMPARATOR))
						{
							crs += 2;
							while(crs < translate->input_len)
							{
								if(translate->input[crs] == TABLE_MARKER_INTERNAL)
									break;
								crs++;
							}
							if(crs >= translate->input_len)
								return 0;//TODO:  log error
						}
						else if(crs + 2 >= translate->input_len)
							need_reset = 1;
						else if(translate->input[crs + 2] != not_slash)
							need_reset = 1;
						else if(translate_has_attributes_at(translate, crs + 3, NEMETH_COMPARATOR))
						{
							crs += 3;
							while(crs < translate->input_len)
							{
								if(translate->input[crs] == TABLE_MARKER_INTERNAL)
									break;
								crs++;
							}
							if(crs >= translate->input_len)
								return 0;//TODO:  log error
						}
					}

				}
				else if(!translate_has_attributes(translate, NEMETH_SPACE))
					need_reset = 1;
			}
			if(need_reset)
			{
				CHANGE_MARK
				if(sep_cnt)
				{
					if(!translate_insert_dots(translate, seps, sep_cnt))
						return 0;
				}
				else
				{
					if(!translate_insert_dots(translate, &base_reset, 1))
						return 0;
				}
			}
			if(crs)
			{
				if(need_reset)
					translate_skip(translate, 1, 1);
				if(!translate_copy_to_output(translate, crs - translate->input_crs + 1, 1))
					return 0;
			}
			break;

		default:

			if(sep_cnt > 0 && translate->input[translate->input_crs] == u',')
			{
				/*   maybe a sequence?   */
				seq = 0;
				if(translate->input_crs + 3 < translate->input_len)
				if(translate_has_attributes_at(translate, translate->input_crs + 1, NEMETH_DIGIT))
				if(translate_has_attributes_at(translate, translate->input_crs + 2, NEMETH_DIGIT))
				if(translate_has_attributes_at(translate, translate->input_crs + 3, NEMETH_DIGIT))
				if(translate->input_crs > 0)
				if(translate_has_attributes_at(translate, translate->input_crs - 1, NEMETH_DIGIT))
					seq = 1;

				if(seq == 0)
				{
					CHANGE_MARK
					if(!translate_insert_dots_for_chars(translate, &script_comma, 1, 1))
						return 0;
					if(translate_has_attributes(translate, NEMETH_SPACE))
						translate_skip(translate, 1, 1);
				}
				else
				{
					if(!translate_copy_to_output(translate, 1, 1))
						return 0;
				}
			}
			else if(!translate_copy_to_output(translate, 1, 1))
				return 0;
		}
	}

#ifdef DEBUG
	translate->output[translate->output_len] = 0;
#endif

	return 1;
}

/******************************************************************************/

static int add_numeric_indicators(struct translate *translate)
{
	int do_insert;
	const unichar indicator = u'⠼';

	translate->table_crs = translate->table_cnt - 1;

	translate->input_crs =
	translate->output_len = 0;

	if(translate_has_attributes(translate, NEMETH_DIGIT | NEMETH_DECIMAL_SEPARATOR))
	{
		CHANGE_MARK
		if(!translate_insert_dots(translate, &indicator, 1))
			return 0;
	}
	if(!translate_copy_to_output(translate, 1, 1))
		return 0;

	do_insert = 0;
	while(translate->input_crs < translate->input_len)
	{
		if(translate_has_attributes(translate, NEMETH_DIGIT | NEMETH_DECIMAL_SEPARATOR))
		{
			if(   translate_has_attributes_at(translate, translate->input_crs - 1, NEMETH_SPACE)
			   || translate->input[translate->input_crs - 1] == TABLE_MARKER_INTERNAL)
					do_insert = 1;
			else if(translate_has_attributes_at(translate, translate->input_crs - 1, NEMETH_DECIMAL_MINUS))
			{
				if(translate_has_attributes_at(translate, translate->input_crs - 2, NEMETH_SPACE))
					do_insert = 1;
				else if(   translate->input_crs - 2 < 0
				        || translate->input[translate->input_crs - 2] == TABLE_MARKER_INTERNAL)
					do_insert = 1;
			}
		}
		if(do_insert)
		{
			do_insert = 0;
			CHANGE_MARK
			if(!translate_insert_dots(translate, &indicator, 1))
				return 0;
		}

		if(!translate_copy_to_output(translate, 1, 1))
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

int translate_nemeth_forward(struct translate *translate)
{
	int processed;

	processed = 0;

	if(translate_get_init_chars_hash_cnt(translate))
	{
		CHANGE_RESET
		if(!generic_process(translate, TABLE_HASH_INIT, FORWARD))
			return 0;
		CHANGE_CHECK
		processed = 1;
	}

	if(translate_get_premode_chars_hash_cnt(translate))
	{
		CHANGE_CHECK
		if(!translate_output_to_input(translate))
			return 0;

		CHANGE_RESET
		if(!generic_process(translate, TABLE_HASH_PREMODE, FORWARD))
			return 0;
		CHANGE_CHECK
		processed = 1;
	}

	if(translate_get_postmode_chars_hash_cnt(translate))
	{
		CHANGE_CHECK
		if(!translate_output_to_input(translate))
			return 0;

		CHANGE_RESET
		if(!generic_process(translate, TABLE_HASH_POSTMODE, FORWARD))
			return 0;
		CHANGE_CHECK
		processed = 1;
	}

	/*   handle roots   */
	CHANGE_CHECK
	if(!translate_output_to_input(translate))
		return 0;

	CHANGE_RESET
	if(!convert_nemeth_roots(translate))
		return 0;
	CHANGE_CHECK
	processed = 1;

	/*   handle subscripts   */
	CHANGE_CHECK
	if(!translate_output_to_input(translate))
		return 0;

	CHANGE_RESET
	if(!convert_nemeth_scripts(translate))
		return 0;
	CHANGE_CHECK
	processed = 1;

	/*   handle numeric indicator   */
	CHANGE_CHECK
	if(!translate_output_to_input(translate))
		return 0;

	CHANGE_RESET
	if(!add_numeric_indicators(translate))
		return 0;
	CHANGE_CHECK
	processed = 1;

	if(translate_get_pretrans_chars_hash_cnt(translate))
	{
		CHANGE_CHECK
		if(!translate_output_to_input(translate))
			return 0;

		CHANGE_RESET
		if(!generic_process(translate, TABLE_HASH_PRETRANS, FORWARD))
			return 0;
		CHANGE_CHECK
		processed = 1;
	}

	if(translate_get_trans_chars_hash_cnt(translate))
	{
		CHANGE_CHECK
		if(!translate_output_to_input(translate))
			return 0;

		CHANGE_RESET
		if(!generic_process(translate, TABLE_HASH_TRANS, FORWARD))
			return 0;
		CHANGE_CHECK
		processed = 1;
	}

	if(translate_get_posttrans_chars_hash_cnt(translate))
	{
		CHANGE_CHECK
		if(!translate_output_to_input(translate))
			return 0;

		CHANGE_RESET
		if(!generic_process(translate, TABLE_HASH_POSTTRANS, FORWARD))
			return 0;
		CHANGE_CHECK
		processed = 1;
	}

	if(translate_get_fini_chars_hash_cnt(translate))
	{
		CHANGE_CHECK
		if(!translate_output_to_input(translate))
			return 0;

		CHANGE_RESET
		if(!generic_process(translate, TABLE_HASH_FINI, FORWARD))
			return 0;
		CHANGE_CHECK
		processed = 1;
	}

	return processed;
}

/******************************************************************************/
