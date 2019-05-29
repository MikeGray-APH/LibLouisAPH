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

#define MATH_SUBSCRIPT_BEGIN           u'\uf580'
#define MATH_SUBSCRIPT_SEPARATOR       u'\uf581'
#define MATH_SUBSCRIPT_END             u'\uf582'
#define MATH_SUPERSCRIPT_BEGIN         u'\uf583'
#define MATH_SUPERSCRIPT_SEPARATOR     u'\uf584'
#define MATH_SUPERSCRIPT_END           u'\uf585'
#define MATH_SUBSUPERSCRIPT_BEGIN      u'\uf586'
#define MATH_SUBSUPERSCRIPT_SEPARATOR  u'\uf587'
#define MATH_SUBSUPERSCRIPT_END        u'\uf588'

#define NEMETH_SUBSCRIPT     u'⠰'
#define NEMETH_SUPERSCRIPT   u'⠘'
#define NEMETH_BASE_RESET    u'⠐'
#define NEMETH_SCRIPT_COMMA  u'⠪'
#define NEMETH_NOT_SLASH     u'⠌'

static int convert_nemeth_scripts(struct translate *translate)
{
	unichar seps[SEPS_MAX];
	int sep_cnt, sub_letter_digit, need_reset, sbp_cnt, in_numeric, len, mrk, crs;

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

			/*   check script-thru/comparator rules   */
			if(sep_cnt)
			{
				/*   §79.f   */
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

				/*   §79.g   */
				else if(translate_has_attributes(translate, NEMETH_COMPARATOR))
				{
					CHANGE_MARK
					if(!translate_insert_dots(translate, seps, sep_cnt))
						return 0;
				}
				else if(translate->input[translate->input_crs] == NEMETH_NOT_SLASH)
				{
					if(translate_has_attributes_at(translate, translate->input_crs + 1, NEMETH_COMPARATOR))
					if(!translate_insert_dots(translate, seps, sep_cnt))
						return 0;
				}
			}

			if(!translate_copy_to_output(translate, crs - translate->input_crs + 1, 1))
				return 0;
			break;

		case MATH_SUBSCRIPT_BEGIN:/*   start subscript   */

			/*   §77   letter-number subscript rule   */
			sub_letter_digit = 0;
			if(sep_cnt == 0)
			{
				crs = translate->input_crs + 1;

				/*   check letter   */
				if(translate_has_attributes_at(translate, crs, NEMETH_LETTER))
				{
					crs++;

					/*   §83.a   check primes   */
					while(crs < translate->input_len &&
					      (   translate->input[crs] == u'\u2032'
					       || translate->input[crs] == u'\u2033'
					       || translate->input[crs] == u'\u2034'
					       || translate->input[crs] == u'\u2057')
					      )
						crs++;

					/*   check separator indicator   */
					if(crs < translate->input_len)
					if(translate->input[crs] == MATH_SUBSCRIPT_SEPARATOR)
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
						if(translate->input[crs] == MATH_SUBSCRIPT_END)
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
				while(translate->input[translate->input_crs] != MATH_SUBSCRIPT_END)
				if(!translate_copy_to_output(translate, 1, 1))
					return 0;
			}
			goto start_script;

		case MATH_SUBSUPERSCRIPT_BEGIN:/*   start sbpscript   */

			/*   first level letter-number subscript rule   */
			sub_letter_digit = 0;
			if(sep_cnt == 0)
			{
				crs = translate->input_crs + 1;

				/*   check letter   */
				if(translate_has_attributes_at(translate, crs, NEMETH_LETTER))
				{
					crs++;

					/*   §83.a   check primes   */
					while(crs < translate->input_len &&
					      (   translate->input[crs] == u'\u2032'
					       || translate->input[crs] == u'\u2033'
					       || translate->input[crs] == u'\u2034'
					       || translate->input[crs] == u'\u2057')
					      )
						crs++;

					/*   check separator indicator   */
					if(crs < translate->input_len)
					if(translate->input[crs] == MATH_SUBSUPERSCRIPT_SEPARATOR)
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
						if(translate->input[crs] == MATH_SUBSUPERSCRIPT_SEPARATOR)
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
				while(translate->input[translate->input_crs] != MATH_SUBSUPERSCRIPT_SEPARATOR)
				if(!translate_copy_to_output(translate, 1, 1))
					return 0;

				/*   switch to superscript   */
				seps[sep_cnt++] = NEMETH_SUPERSCRIPT;
				if(!translate_insert_dots(translate, seps, sep_cnt))
					return 0;
			}
			else
				sbp_cnt = 0;

		case MATH_SUPERSCRIPT_BEGIN:/*   start supscript   */

			start_script:

			/*   skip begin/end indicator   */
			translate_skip(translate, 1, 1);
			break;

		case MATH_SUBSCRIPT_SEPARATOR:/*   enter subscript   */

			CHANGE_MARK
			seps[sep_cnt++] = NEMETH_SUBSCRIPT;
			goto enter_script;
			break;

		case MATH_SUPERSCRIPT_SEPARATOR:/*   enter supscript   */

			CHANGE_MARK
			seps[sep_cnt++] = NEMETH_SUPERSCRIPT;
			goto enter_script;
			break;

		case MATH_SUBSUPERSCRIPT_SEPARATOR:/*   enter sbpscript   */

			enter_sbpscript:
			CHANGE_MARK
			if(sbp_cnt == 0)
			{
				sbp_cnt++;
				seps[sep_cnt++] = NEMETH_SUBSCRIPT;
			}
			else
			{
				sep_cnt--;
				seps[sep_cnt++] = NEMETH_SUPERSCRIPT;
			}

			enter_script:
			if(!translate_insert_dots_for_chars(translate, seps, sep_cnt, 1))
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

		case MATH_SUBSUPERSCRIPT_END:  sbp_cnt--;  /*   finish sbpscript   */
		case MATH_SUBSCRIPT_END:                   /*   finish subscript   */
		case MATH_SUPERSCRIPT_END:                 /*   finish supscript   */

			sep_cnt--;

			/*   skip all finishes   */
			crs = translate->input_crs + 1;
			while(crs < translate->input_len)
			{
				if(   translate->input[crs] == MATH_SUBSCRIPT_END
				   || translate->input[crs] == MATH_SUPERSCRIPT_END
				   || translate->input[crs] == MATH_SUBSUPERSCRIPT_END)
				{
					sep_cnt--;
					crs++;
				}
				else
					break;
			}
			len = crs - translate->input_crs;

			if(translate->input[crs] == u'\uf587')
			{
				translate_skip(translate, len, 1);
				goto enter_sbpscript;
			}

			/*   check for reset   */
			mrk = crs;
			need_reset =
			crs = 0;
			if(mrk < translate->input_len)
			{
				if(translate->input[mrk] == TABLE_MARKER_INTERNAL)
				{
					/*   find ending marker   */
					crs = mrk + 1;
					while(crs < translate->input_len)
					{
						if(translate->input[crs] == TABLE_MARKER_INTERNAL)
							break;
						crs++;
					}
					if(crs >= translate->input_len)
						return 0;//TODO:  log error

					/*   §79.f   */
					if(translate_has_attributes_at(translate, mrk + 1, NEMETH_SCRIPT_THRU))
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
						else if(translate->input[crs + 2] != NEMETH_NOT_SLASH)
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
				else if(!translate_has_attributes_at(translate, mrk, NEMETH_SPACE))
					need_reset = 1;
			}
			if(need_reset)
			{
				CHANGE_MARK
				if(sep_cnt)
				{
					if(!translate_insert_dots_for_chars(translate, seps, sep_cnt, len))
						return 0;
				}
				else
				{
					if(!translate_insert_dot_for_chars(translate, NEMETH_BASE_RESET, len))
						return 0;
				}
			}
			else
				translate_skip(translate, len, 1);
			if(crs)
			{
				if(need_reset)
					translate_skip(translate, 1, 1);
				if(!translate_copy_to_output(translate, crs - translate->input_crs + 1, 1))
					return 0;
			}
			break;

		default:

			/*   §78   comma in script level   */
			if(sep_cnt > 0 && translate->input[translate->input_crs] == u',')
			{
				/*   §79.b   comma as a numeric separator   */
				in_numeric = 0;
				if(translate->input_crs + 3 < translate->input_len)
				if(translate_has_attributes_at(translate, translate->input_crs + 1, NEMETH_DIGIT))
				if(translate_has_attributes_at(translate, translate->input_crs + 2, NEMETH_DIGIT))
				if(translate_has_attributes_at(translate, translate->input_crs + 3, NEMETH_DIGIT))
				if(translate->input_crs > 0)
				if(translate_has_attributes_at(translate, translate->input_crs - 1, NEMETH_DIGIT))
					in_numeric = 1;

				if(in_numeric == 0)
				{
					CHANGE_MARK
					if(!translate_insert_dot_for_chars(translate, NEMETH_SCRIPT_COMMA, 1))
						return 0;
					if(translate_has_attributes(translate, NEMETH_SPACE))
						translate_skip(translate, 1, 1);
				}
				else if(!translate_copy_to_output(translate, 1, 1))
						return 0;
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
