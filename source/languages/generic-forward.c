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

#include "generic.h"
#include "log.h"

#ifdef CHECK_FOR_CHANGE
#define CHANGE_MARK  translate->changed = 1;
#else
#define CHANGE_MARK
#endif

/******************************************************************************/

#define WORD_CHAR       0x01
#define WORD_WHOLE      0x02
#define WORD_INDICATOR  0x04
#define WORD_NONLETTER  0x08

#define EMP_BEGIN        0x00000001
#define EMP_END          0x00000002
#define EMP_WORD         0x00000004
#define EMP_SYMBOL       0x00000008
#define EMP_EMPHASIS     0x0000000f
#define EMP_RESET        0x00000010

/******************************************************************************/

static int is_marked_equal_to_at(const struct translate *translate, const Unicode *name, const int name_len, const int at)
{
	int i;

	/*   at least this much should be left   */
	if(name_len + 2 > translate->input_len - at)
		return 0;

	for(i = 0; i < name_len; i++)
	if(name[i] != translate->input[at + 1 + i])
		return 0;

	return translate->input[at + 1 + i] == translate->input[at];
}

static inline int is_marked_equal_to(const struct translate *translate, const Unicode *name, const int name_len)
{
	return is_marked_equal_to_at(translate, name, name_len, translate->input_crs);
}

static inline int is_marked_with_node_name_at(const struct translate *translate, const struct mode *mode, const int at)
{
	return is_marked_equal_to_at(translate, mode->name, mode->name_len, at);
}

static int is_marked_indicator_begin_at(const struct translate *translate, const struct mode *mode, const int at)
{
	/*   mode passage not defined if len == 0   */
	if(!mode->begin_len)
		return 0;

	return is_marked_equal_to_at(translate, mode->begin, mode->begin_len, at);
}

static inline int is_marked_indicator_begin(const struct translate *translate, const struct mode *mode)
{
	return is_marked_indicator_begin_at(translate, mode, translate->input_crs);
}

static int is_marked_indicator_end_at(const struct translate *translate, const struct mode *mode, const int at)
{
	/*   mode passage not defined if len == 0   */
	if(!mode->end_len)
		return 0;

	return is_marked_equal_to_at(translate, mode->end, mode->end_len, at);
}

static inline int is_marked_indicator_end(const struct translate *translate, const struct mode *mode)
{
	return is_marked_indicator_end_at(translate, mode, translate->input_crs);
}

/******************************************************************************/

static int convert_user_indicators(struct translate *translate)
{
	const struct table *table;

	/*   only copy indicators from last table in tables   */
	table = translate->tables[translate->table_cnt - 1];
	translate->table_crs = translate->table_cnt - 1;

	translate->input_crs =
	translate->output_len = 0;
	while(translate->input_crs < translate->input_len)
	if(translate->input[translate->input_crs] == table->marker_begin)
	{
		if(translate_is_nocontract_set(translate) && is_marked_equal_to(translate, u"nocontract", 10))
		{
			CHANGE_MARK
			if(!generic_insert_marked(translate, table->nocontract.begin, table->nocontract.begin_len, table->marker_soft))
				return 0;
			if(!translate_skip(translate, 12, 1))
				return 0;
		}
		else if(translate_is_numeric_set(translate) && is_marked_equal_to(translate, u"numeric", 7))
		{
			CHANGE_MARK
			if(!generic_insert_marked(translate, table->numeric.begin, table->numeric.begin_len, table->marker_soft))
				return 0;
			if(!translate_skip(translate, 9, 1))
				return 0;
		}
		else if(!translate_copy_marked_user(translate))
			return 0;
	}
	else if(translate->input[translate->input_crs] == table->marker_end)
	{
		if(translate_is_nocontract_set(translate) && is_marked_equal_to(translate, u"nocontract", 10))
		{
			CHANGE_MARK
			if(!generic_insert_marked(translate, table->nocontract.end, table->nocontract.end_len, table->marker_soft))
				return 0;
			if(!translate_skip(translate, 12, 1))
				return 0;
		}
		else if(translate_is_numeric_set(translate) && is_marked_equal_to(translate, u"numeric", 7))
		{
			CHANGE_MARK
			if(!generic_insert_marked(translate, table->numeric.end, table->numeric.end_len, table->marker_soft))
				return 0;
			if(!translate_skip(translate, 9, 1))
				return 0;
		}
		else if(!translate_copy_marked_user(translate))
			return 0;
	}
	else if(!translate_copy_to_output(translate, 1, 1))
		return 0;

	return 1;
}

/******************************************************************************/

static int get_after_next_delimiter(const struct translate *translate, const int at)
{
	int i;

	for(i = at + 1; i < translate->input_len; i++)
	if(translate->input[i] == translate->input[at])
		break;
	i++;
	if(i > translate->input_len)
	{
		i = translate->input_len;
		return i;
	}

	return i;
}

static int is_word_start(const unsigned char *words, const struct translate *translate, const int at)
{
	if(at >= translate->input_len)
		return 0;

	if(translate_on_marker_at(translate, at))
		return is_word_start(words, translate, get_after_next_delimiter(translate, at));

	if(!translate_has_attributes_at(translate, at, CHAR_SPACE))
		return 1;

	return 0;
}

static int get_before_indicators(unsigned char *words, const int at)
{
	int i;

	for(i = at; i >= 0; i--)
	if(!(words[i] & WORD_INDICATOR))
		break;
	return i + 1;
}

static void mark_mode(unsigned int *indicators, unsigned char *words, const struct translate *translate, const struct table *table, const struct mode *mode)
{
	unsigned int attrs;
	unsigned char word_mark;
	int emp_begin, user_begin_in, user_end_in, user_indicator_in, user_mode_in, marked_in, word_begin, space_prv, i;

	user_begin_in =
	user_end_in =
	user_indicator_in =
	marked_in = 0;
	emp_begin =
	user_mode_in =
	word_begin = -1;
	space_prv = 0;
	word_mark = WORD_INDICATOR;
	for(i = 0; i < translate->input_len; i++)
	{
		if(marked_in)
		{
			words[i] |= word_mark;
			if(translate_on_indicator_or_modifier_marker_at(translate, i))
				marked_in = 0;
		}
		else if(user_begin_in)
		{
			words[i] |= word_mark;
			if(translate->input[i] == table->marker_begin)
			{
				user_begin_in = 0;

				if(user_mode_in >= 0)
				{
					translate->input[i] = table->marker_internal;
					user_mode_in = -1;
				}
			}
			continue;
		}
		else if(user_end_in)
		{
			words[i] |= word_mark;
			if(translate->input[i] == table->marker_end)
			{
				user_end_in = 0;

				if(user_mode_in >= 0)
				{
					translate->input[i] = table->marker_internal;
					user_mode_in = -1;
				}
			}
			continue;
		}
		else if(user_indicator_in)
		{
			words[i] |= word_mark;
			if(translate->input[i] == table->marker_user)
			{
				user_indicator_in = 0;

				if(user_mode_in >= 0)
				{
					translate->input[i] = table->marker_internal;
					user_mode_in = -1;
				}
			}
			continue;
		}
		else if(translate->input[i] == table->marker_begin)
		{
			if(is_word_start(words, translate, i))
				word_mark = WORD_INDICATOR | WORD_CHAR;
			else
				word_mark = WORD_INDICATOR;
			words[i] |= word_mark;
			user_begin_in = 1;
			if(emp_begin < 0)
			{
				/*   set EMP_BEGIN at the spot of the marked
				     indicator in the text so that the order of
				     multiple begins can be distinguished by
				     different lengths   */
				if(is_marked_with_node_name_at(translate, mode, i))
				{
					emp_begin = i;
					user_mode_in = i;
					translate->input[i] = table->marker_internal;
				}
			}
			continue;
		}
		else if(translate->input[i] == table->marker_end)
		{
			if(is_word_start(words, translate, i))
				word_mark = WORD_INDICATOR | WORD_CHAR;
			else
				word_mark = WORD_INDICATOR;
			words[i] |= word_mark;
			user_end_in = 1;
			if(emp_begin >= 0)
			{
				if(is_marked_with_node_name_at(translate, mode, i))
				{
					indicators[emp_begin] = EMP_BEGIN;

					/*   set EMP_END before all contiguous
					     marked indicators   */
					indicators[get_before_indicators(words, i)] = EMP_END;
					emp_begin = -1;

					user_mode_in = i;
					translate->input[i] = table->marker_internal;
				}
			}
			continue;
		}
		else if(translate->input[i] == table->marker_user)
		{
			if(is_word_start(words, translate, i))
				word_mark = WORD_INDICATOR | WORD_CHAR;
			else
				word_mark = WORD_INDICATOR;
			words[i] |= word_mark;
			user_indicator_in = 1;
			if(emp_begin < 0)
			{
				if(is_marked_indicator_begin_at(translate, mode, i))
				{
					emp_begin = i;
					user_mode_in = i;
					translate->input[i] = table->marker_internal;
				}
			}
			else
			{
				if(is_marked_indicator_end_at(translate, mode, i))
				{
					indicators[emp_begin] = EMP_BEGIN;
					indicators[get_before_indicators(words, i)] = EMP_END;
					emp_begin = -1;

					user_mode_in = i;
					translate->input[i] = table->marker_internal;
				}
			}
			continue;
		}
		else if(translate_on_indicator_or_modifier_marker_at(translate, i))
		{
			if(is_word_start(words, translate, i))
				word_mark = WORD_INDICATOR | WORD_CHAR;
			else
				word_mark = WORD_INDICATOR;
			words[i] |= word_mark;
			marked_in = 1;
			continue;
		}

		/*   make sure no prefixed delimiters counting as word   */
		attrs = translate_get_attributes_at(translate, i);
		if(attrs & CHAR_SPACE)
		{
			space_prv = 1;
			word_begin = -1;
		}
		else if(attrs & CHAR_SEQUENCE_DELIMITER)
		{
			if(!space_prv)
			{
				words[i] |= WORD_CHAR;
				if(word_begin < 0)
					word_begin = i;
			}
		}
		else
		{
			words[i] |= WORD_CHAR;
			space_prv = 0;
			if(word_begin < 0)
				word_begin = i;
		}
	}
}

static void indicators_to_words(unsigned int *indicators, unsigned char *words, const struct translate *translate)
{
	int ind_in, emp_in, emp_len, word_in, word_begin, word_began, word_whole, word_stop, word_len, i;

	ind_in =
	emp_in =
	word_in =
	word_whole = 0;
	word_began = 0;
	word_begin = -1;
	word_len =
	emp_len = 0;

	for(i = 0; i < translate->input_len; i++)
	{
		/*   keep track of indicators   */
		if(words[i] & WORD_INDICATOR)
			ind_in = 1;
		else
			ind_in = 0;

		/*   clear out previous whole word markings   */
		words[i] &= ~WORD_WHOLE;

		/*   beginning of mode   */
		if(!emp_in)
		if(indicators[i] & EMP_BEGIN)
		{
			emp_in = 1;
			emp_len = 0;
			indicators[i] &= ~EMP_BEGIN;

			/*   mode starting inside word   */
			if(words[i] & WORD_CHAR)
			{
				word_begin = i;
				word_len = 0;
				if(word_began)
					word_whole = 0;
				else
					word_whole = WORD_WHOLE;
			}
		}

		/*   end of mode   */
		if(emp_in)
		if(indicators[i] & EMP_END)
		{
			emp_in = 0;
			indicators[i] &= ~EMP_END;

			if(word_in && word_begin >= 0)
			{
				/*   check if mode ended inside a word   */
				word_stop = EMP_END | EMP_WORD;
				if(words[i] & WORD_CHAR)
					word_whole = 0;
				else
					word_stop = 0;

				/*   if whole word is one symbol,
				     turn it into a symbol   */
				if(EMP_SYMBOL && word_len == 1)
					indicators[word_begin] |= EMP_SYMBOL;
				else
				{
					indicators[word_begin] |= EMP_WORD;
					indicators[i] |= word_stop;
				}
				words[word_begin] |= word_whole;
			}
		}
		else if(!ind_in)
			emp_len++;

		/*   beginning of word   */
		if(!word_in)
		if(words[i] & WORD_CHAR)
		{
			if(!(words[i] & WORD_INDICATOR))
				word_began = 1;
			word_in = 1;
			word_len = 0;
			if(emp_in)
			{
				word_begin = i;
				word_whole = WORD_WHOLE;
			}
		}

		/*   end of word   */
		if(word_in)
		if(!(words[i] & WORD_CHAR) && !ind_in)
		{
			/*   made it through whole word   */
			if(emp_in && word_begin >= 0)
			{
				/*   if word is one character,
				     turn it into a symbol   */
				if(EMP_SYMBOL && word_len == 1)
						indicators[word_begin] |= EMP_SYMBOL;
				else
					indicators[word_begin] |= EMP_WORD;
				words[word_begin] |= word_whole;
			}

			word_in = 0;
			word_whole = 0;
			word_begin = -1;
			word_began = 0;
		}
		else
		{
			/*   words don't start on indicators   */
			if(!(words[i] & WORD_INDICATOR))
			{
				word_began = 1;
				word_len++;
			}
		}
	}

	/*   input end   */
	if(emp_in)
	{
		indicators[i] &= ~EMP_END;

		if(word_in)
		if(word_begin >= 0)
		{
			/*   if word is one character,
			     turn it into a symbol   */
			if(EMP_SYMBOL && word_len == 1)
					indicators[word_begin] |= EMP_SYMBOL;
			else
				indicators[word_begin] |= EMP_WORD;
			words[word_begin] |= word_whole;
		}
	}
}

static void convert_to_passage(unsigned int *indicators, unsigned char *words, const int pass_begin, const int pass_end)
{
	int i;

	for(i = pass_begin; i <= pass_end; i++)
	{
		indicators[i] &= ~(EMP_SYMBOL | EMP_WORD);
		words[i] &= ~WORD_WHOLE;
	}

	indicators[pass_begin] |= EMP_BEGIN;
	indicators[pass_end] |= EMP_END;
}

static void words_to_passages(unsigned int *indicators, unsigned char *words, const struct translate *translate, const int passage_len)
{
	int word_in, word_cnt, pass_in, pass_begin, pass_end, i;

	pass_begin =
	pass_end = -1;
	pass_in =
	word_in = 0;
	word_cnt = 0;

	for(i = 0; i < translate->input_len; i++)
	{
		/*   beginning of word   */
		if(!word_in)
		if(words[i] & WORD_CHAR)
		{
			word_in = 1;
			if(pass_in)
			{
				if(!(indicators[i] & EMP_WORD || indicators[i] & EMP_SYMBOL))
				{
					if(word_cnt >= passage_len)
					if(pass_end >= 0)
						convert_to_passage(indicators, words, pass_begin, pass_end);
					pass_in = 0;
				}
				else
					word_cnt++;
			}
		}

		/*   end of word   */
		if(word_in)
		if(!(words[i] & WORD_CHAR))
		{
			word_in = 0;
			if(pass_in)
				pass_end = i;
		}

		/*   beginning of passage   */
		if(!pass_in)
		if(indicators[i] == EMP_WORD)
		{
			pass_in = 1;
			pass_begin = i;
			word_cnt = 1;
		}
		else if(indicators[i] == EMP_SYMBOL)
		{
			pass_begin = i;
			while(i < translate->input_len)
			if(words[i] & WORD_INDICATOR)
				i++;
			else
				break;

			if(!(words[i + 1] & WORD_CHAR))
			{
				pass_in = 1;
				word_cnt = 1;
			}
			else
				pass_begin = -1;
		}

		/*   end of passage   */
		if(pass_in)
		if(indicators[i] == (EMP_WORD | EMP_END))
		{
			if(word_cnt >= passage_len)
			if(pass_end >= 0)
				convert_to_passage(indicators, words, pass_begin, i);
			pass_in = 0;
		}
		else if(indicators[i] == EMP_SYMBOL)
		{
			while(i < translate->input_len)
			if(words[i] & WORD_INDICATOR)
				i++;
			else
				break;

			if(words[i + 1] & WORD_CHAR)
			{
				i++;
				if(word_cnt >= passage_len)
					convert_to_passage(indicators, words, pass_begin, i);
				pass_in = 0;
			}
		}
	}

	/*   input end   */
	if(pass_in)
	{
		if(word_cnt >= passage_len)
		if(pass_end >= 0)
		if(word_in)
			convert_to_passage(indicators, words, pass_begin, translate->input_len);
		else
			convert_to_passage(indicators, words, pass_begin, pass_end);
	}
}

/* The order of the indicators at the same place goes:
 *    symbol, word, end, begin
 * with the begins and ends being sorted based on their lengths.
*/

struct indicator
{
	struct indicator *prv, *nxt;
	struct mode *mode;
	unsigned int type;
	int len;
};

struct indicator_node
{
	struct indicator_node *nxt;
	struct indicator *indicator;
	int at;
};

static void indicator_free(struct indicator *indicator)
{
	if(!indicator)
		return;
	indicator_free(indicator->nxt);
	FREE(indicator);
}

static void indicator_node_free(struct indicator_node *node)
{
	if(!node)
		return;
	indicator_node_free(node->nxt);
	indicator_free(node->indicator);
	FREE(node);
}

static struct indicator *begin, *word;
static int begin_at, word_at;

static struct indicator_node* add_indicators_node(struct indicator_node *nodes, struct mode *mode, const unsigned int type, const int at)
{
	struct indicator_node *node, *node_crs;
	struct indicator *indicator, *indicator_crs;

	indicator = MALLOC(sizeof(struct indicator));
	indicator->prv =
	indicator->nxt = NULL;
	indicator->mode = mode;
	indicator->type = type;
	indicator->len = 0;

	node_crs = nodes;

	while(node_crs->nxt)
	{
		if(node_crs->nxt->at > at)
			break;
		node_crs = node_crs->nxt;
	}

	if(node_crs->at == at)
	{
		switch(type)
		{
		default:  ASSERT(0)

		case EMP_BEGIN:

			begin = indicator;
			begin_at = at;

			if(   node_crs->indicator->type != EMP_SYMBOL
			   && node_crs->indicator->type != EMP_WORD
			   && node_crs->indicator->type != (EMP_WORD | EMP_END)
			   && node_crs->indicator->type != EMP_END)
				goto insert_first;
			indicator_crs = node_crs->indicator;
			while(indicator_crs->nxt)
			{
				if(   indicator_crs->type != EMP_SYMBOL
				   && indicator_crs->type != EMP_WORD
				   && indicator_crs->type != (EMP_WORD | EMP_END)
				   && indicator_crs->type != EMP_END)
					break;
				indicator_crs = indicator_crs->nxt;
			}
			goto insert_after;

		case EMP_END:

			ASSERT(begin)
			indicator->len =
			begin->len = at - begin_at;

			if(   node_crs->indicator->type != EMP_SYMBOL
			   && node_crs->indicator->type != EMP_WORD
			   && node_crs->indicator->type != (EMP_WORD | EMP_END))
				goto insert_first;
			indicator_crs = node_crs->indicator;
			while(indicator_crs->nxt)
			{
				if(   indicator_crs->type != EMP_SYMBOL
				   && indicator_crs->type != EMP_WORD
				   && indicator_crs->type != (EMP_WORD | EMP_END))
					break;
				indicator_crs = indicator_crs->nxt;
			}
			goto insert_after;

		case EMP_WORD:

			word = indicator;
			word_at = at;

			if(   node_crs->indicator->type != EMP_SYMBOL
			   && node_crs->indicator->type != (EMP_WORD | EMP_END))
				goto insert_first;
			indicator_crs = node_crs->indicator;
			while(indicator_crs->nxt)
			{
				if(   indicator_crs->type != EMP_SYMBOL
				   && indicator_crs->type != (EMP_WORD | EMP_END))
					break;
				indicator_crs = indicator_crs->nxt;
			}
			goto insert_after;

		case EMP_WORD | EMP_END:

			ASSERT(word)
			indicator->len =
			word->len = at - word_at;

			if(node_crs->indicator->type != EMP_SYMBOL)
				goto insert_first;
			indicator_crs = node_crs->indicator;
			while(indicator_crs->nxt)
			{
				if(indicator_crs->nxt->type != EMP_SYMBOL)
					break;
				indicator_crs = indicator_crs->nxt;
			}

			insert_after:
			indicator->prv = indicator_crs;
			indicator->nxt = indicator_crs->nxt;
			if(indicator_crs->nxt)
				indicator_crs->nxt->prv = indicator;
			indicator_crs->nxt = indicator;
			break;

		case EMP_SYMBOL:

			insert_first:
			indicator->prv = NULL;
			indicator->nxt = node_crs->indicator;
			if(node_crs->indicator)
				node_crs->indicator->prv = indicator;
			node_crs->indicator = indicator;
			break;
		}
		return node_crs;
	}
	else
	{
		ASSERT(node_crs->at < at)
		node = MALLOC(sizeof(struct indicator_node));
		node->indicator = indicator;
		node->at = at;

		switch(type)
		{
		case EMP_BEGIN:

			begin = indicator;
			begin_at = at;
			break;

		case EMP_END:

			ASSERT(begin)
			indicator->len =
			begin->len = at - begin_at;
			break;

		case EMP_WORD:

			word = indicator;
			word_at = at;

		case EMP_WORD | EMP_END:

			ASSERT(word)
			indicator->len =
			word->len = at - word_at;
		}

		node->nxt = node_crs->nxt;
		node_crs->nxt = node;
		return node;
	}
}

static int add_indicators_nodes(struct indicator_node *nodes, struct mode *mode, unsigned int *indicators, const int indicators_len)
{
	int i;

	for(i = 0; i < indicators_len; i++)
	if(indicators[i])
		nodes = add_indicators_node(nodes, mode, indicators[i], i);

	return 1;
}

static void sort_word_end(struct indicator *indicator)
{
	struct indicator *nxt;

	if(!indicator->nxt)
		return;
	if(indicator->nxt->type != (EMP_WORD | EMP_END))
		return;

	sort_word_end(indicator->nxt);

	if(indicator->len < indicator->nxt->len)
	{
		nxt = indicator->nxt;

		if(indicator->prv)
			indicator->prv->nxt = nxt;
		if(nxt->nxt)
			nxt->nxt->prv = indicator;

		nxt->prv = indicator->prv;
		indicator->nxt = nxt->nxt;

		nxt->nxt = indicator;
		indicator->prv = nxt;

		sort_word_end(indicator);
	}
}

static void sort_word_begin(struct indicator *indicator)
{
	struct indicator *nxt;

	if(!indicator->nxt)
		return;
	if(indicator->nxt->type != EMP_WORD)
		return;

	sort_word_begin(indicator->nxt);

	if(indicator->len > indicator->nxt->len)
	{
		nxt = indicator->nxt;

		if(indicator->prv)
			indicator->prv->nxt = nxt;
		if(nxt->nxt)
			nxt->nxt->prv = indicator;

		nxt->prv = indicator->prv;
		indicator->nxt = nxt->nxt;

		nxt->nxt = indicator;
		indicator->prv = nxt;

		sort_word_begin(indicator);
	}
}

static void sort_passage_end(struct indicator *indicator)
{
	struct indicator *nxt;

	if(!indicator->nxt)
		return;
	if(indicator->nxt->type != EMP_END)
		return;

	sort_passage_end(indicator->nxt);

	if(indicator->len < indicator->nxt->len)
	{
		nxt = indicator->nxt;

		if(indicator->prv)
			indicator->prv->nxt = nxt;
		if(nxt->nxt)
			nxt->nxt->prv = indicator;

		nxt->prv = indicator->prv;
		indicator->nxt = nxt->nxt;

		nxt->nxt = indicator;
		indicator->prv = nxt;

		sort_passage_end(indicator);
	}
}

static void sort_passage_begin(struct indicator *indicator)
{
	struct indicator *nxt;

	if(!indicator->nxt)
		return;

	sort_passage_begin(indicator->nxt);

	if(indicator->len > indicator->nxt->len)
	{
		nxt = indicator->nxt;

		if(indicator->prv)
			indicator->prv->nxt = nxt;
		if(nxt->nxt)
			nxt->nxt->prv = indicator;

		nxt->prv = indicator->prv;
		indicator->nxt = nxt->nxt;

		nxt->nxt = indicator;
		indicator->prv = nxt;

		sort_passage_begin(indicator);
	}
}

static void sort_indicators(struct indicator_node *node)
{
	struct indicator *indicator;

	while(node)
	{
		indicator = node->indicator;

		while(indicator)
		if(indicator->type == (EMP_WORD | EMP_END))
			break;
		else
			indicator = indicator->nxt;
		if(indicator)
			sort_word_end(indicator);

		indicator = node->indicator;

		while(indicator)
		if(indicator->type == EMP_WORD)
			break;
		else
			indicator = indicator->nxt;
		if(indicator)
			sort_word_begin(indicator);

		indicator = node->indicator;

		while(indicator)
		if(indicator->type == EMP_END)
			break;
		else
			indicator = indicator->nxt;
		if(indicator)
			sort_passage_end(indicator);

		indicator = node->indicator;

		while(indicator)
		if(indicator->type == EMP_BEGIN)
			break;
		else
			indicator = indicator->nxt;
		if(indicator)
			sort_passage_begin(indicator);

		while(node->indicator->prv)
			node->indicator = node->indicator->prv;

		node = node->nxt;
	}
}

static int insert_indicator_node(struct translate *translate, const struct table *table, struct indicator *indicator, const int at)
{
	if(!indicator)
		return 1;
	insert_indicator_node(translate, table, indicator->nxt, at);

	switch(indicator->type)
	{
	case EMP_BEGIN:           return generic_insert_marked(translate, indicator->mode->begin, indicator->mode->begin_len, table->marker_hard);
	case EMP_END:             return generic_insert_marked(translate, indicator->mode->end, indicator->mode->end_len, table->marker_hard);
	case EMP_WORD:            return generic_insert_marked(translate, indicator->mode->word, indicator->mode->word_len, table->marker_hard);
	case EMP_WORD | EMP_END:  return generic_insert_marked(translate, indicator->mode->term, indicator->mode->term_len, table->marker_hard);
	case EMP_SYMBOL:          return generic_insert_marked(translate, indicator->mode->symbol, indicator->mode->symbol_len, table->marker_hard);
	}

	ASSERT(0)
	return 0;
}

static int insert_indicator_nodes(struct translate *translate, const struct table *table, struct indicator_node *node)
{
	if(!node)
		return 1;

	if(!insert_indicator_nodes(translate, table, node->nxt))
		return 0;

	translate->input_crs = 0;
	if(!translate_copy_to_output(translate, node->at, 1))
		return 0;

	if(!insert_indicator_node(translate, table, node->indicator, node->at))
		return 0;

	translate->input_crs = node->at;
	if(!translate_copy_to_output(translate, translate->input_len - node->at, 1))
		return 0;

	if(!translate_output_to_input(translate))
		return 0;

#ifdef DEBUG
	translate->output[translate->output_len] = 0;
#endif

	return 1;
}

static int add_indicators_emphases(struct translate *translate)
{
	const struct table *table;
	struct mode *mode;
	struct indicator_node node_auto;
	unsigned int *indicators;
	unsigned char *words;

	/*   only copy indicators from last table in tables   */
	table = translate->tables[translate->table_cnt - 1];
	translate->table_crs = translate->table_cnt - 1;

	translate->input_crs =
	translate->output_len = 0;

	indicators = MALLOC((translate->input_len + 1) * sizeof(unsigned int));
	if(!indicators)
	{
		LOG_ALLOCATE_FAIL
		return 0;
	}

	words = MALLOC((translate->input_len + 1) * sizeof(unsigned char));
	if(!words)
	{
		LOG_ALLOCATE_FAIL
		FREE(indicators);
		return 0;
	}

	memset(&node_auto, 0, sizeof(struct indicator_node));
	node_auto.at = -1;

	mode = table->emphases;
	while(mode)
	{
		memset(indicators, 0, (translate->input_len + 1) * sizeof(unsigned int));
		memset(words, 0, (translate->input_len + 1) * sizeof(unsigned char));
		begin =
		word = NULL;
		begin_at =
		word_at = 0;

		mark_mode(indicators, words, translate, table, mode);
		if(mode->word_len)
		{
			indicators_to_words(indicators, words, translate);
			if(mode->passage_len)
				words_to_passages(indicators, words, translate, mode->passage_len);
		}

		if(!add_indicators_nodes(&node_auto, mode, indicators, translate->input_len + 1))
			goto return_fail_free;

		mode = mode->nxt;
	}

	if(node_auto.nxt)
	{
		CHANGE_MARK
		sort_indicators(node_auto.nxt);
		insert_indicator_nodes(translate, table, node_auto.nxt);
		if(!generic_remove_internal(translate))
			goto return_fail_free;
	}

	indicator_node_free(node_auto.nxt);
	FREE(indicators);
	FREE(words);

#ifndef CHECK_FOR_CHANGE
	if(translate->output_len == 0)
	{
		utf16_copy(translate->output, translate->input, (translate->input_len + 1));
		translate->output_len = translate->input_len;

		if(translate->maps_use)
		{
			ASSERT(translate->output_max >= translate->input_len + 1)
			memcpy(translate->output_to_input_map, translate->input_map, (translate->input_len + 1) * sizeof(int));
		}
	}
#endif

#ifdef DEBUG
	translate->output[translate->output_len] = 0;
#endif

	return 1;

	return_fail_free:
	indicator_node_free(node_auto.nxt);
	FREE(indicators);
	FREE(words);

	return 0;
}

/******************************************************************************/

static int is_indicator_delimiter(const struct table *table, const Unicode uchar)
{
	if(uchar == table->marker_user)
		return 1;
	if(uchar == table->marker_begin)
		return 1;
	if(uchar == table->marker_end)
		return 1;
	if(uchar == table->marker_hard)
		return 1;
	if(uchar == table->marker_soft)
		return 1;
	return 0;
}

//NOTE:  the capitals must be marked before numeric mode is processed
static void mark_capitals(unsigned int *indicators, unsigned char *words, struct translate *translate, const struct table *table)
{
	unsigned int attrs;
	int caps_begin, caps_end, caps_cnt, nocaps_in, indicator_in, i;

	caps_begin =
	caps_end = -1;
	caps_cnt = 0;
	indicator_in =
	nocaps_in = 0;

	for(i = 0; i < translate->input_len; i++)
	{
		/*   marked nocapital   */
		if(nocaps_in)
		{
			if(translate->input[i] == table->marker_end)
			if(is_marked_equal_to_at(translate, u"nocapital", 9, i))
			{
				nocaps_in = 0;

				/*   convert indicators so they are removed later   */
				translate->input[i] = table->marker_soft;
				translate->input[i + 10] = table->marker_soft;

				i += 11;
			}
			continue;
		}
		else
		{
			if(translate->input[i] == table->marker_begin)
			if(is_marked_equal_to_at(translate, u"nocapital", 9, i))
			{
				nocaps_in = 1;

				/*   convert indicators so they are removed later   */
				translate->input[i] = table->marker_soft;
				translate->input[i + 10] = table->marker_soft;

				indicators[i] |= EMP_RESET;
				if(caps_begin >= 0)
				{
					indicators[caps_begin] |= EMP_BEGIN;
					if(caps_cnt > 0)
						indicators[i] |= EMP_END;
					else
						indicators[caps_end] |= EMP_END;
					caps_begin =
					caps_end = -1;
					caps_cnt = 0;
				}

				i += 11;
				continue;
			}
		}

		/*   marked indicators   */
		if(indicator_in)
		{
			words[i] |= WORD_INDICATOR;
			if(is_indicator_delimiter(table, translate->input[i]))
				indicator_in = 0;
			continue;
		}
		else if(is_indicator_delimiter(table, translate->input[i]))
		{
			words[i] |= WORD_INDICATOR;
			indicator_in = 1;
			continue;
		}

		attrs = translate_get_attributes_at(translate, i);

		/*   caps doesn't care if delimiters are counted as words,
		     they are dealt with separately   */
		if(!(attrs & CHAR_SPACE))
			words[i] |= WORD_CHAR;
		else if(caps_cnt > 0)
		{
			caps_end = i;
			caps_cnt = 0;
		}

		if(attrs & CHAR_UPPER)
		{
			if(caps_begin < 0)
				caps_begin = i;
			caps_cnt++;
		}
		else if(caps_begin >= 0)
		{
			if(attrs & CHAR_LETTER && attrs & CHAR_LOWER)
			{
				indicators[caps_begin] |= EMP_BEGIN;
				if(caps_cnt > 0)
					indicators[i] |= EMP_END;
				else
					indicators[caps_end] |= EMP_END;
				caps_begin =
				caps_end = -1;
				caps_cnt = 0;
			}
		}
	}

	/*   input end   */
	if(caps_begin >= 0)
	{
		indicators[caps_begin] |= EMP_BEGIN;
		if(caps_cnt > 0)
			indicators[translate->input_len] |= EMP_END;
		else
			indicators[caps_end] |= EMP_END;
	}
}

static void mark_nonalphabetic_words(unsigned int *indicators, unsigned char *words, const struct translate *translate)
{
	int word_begin, letter_cnt, i;

	word_begin = -1;
	letter_cnt = 0;

	for(i = 0; i < translate->input_len; i++)
	{
		/*   skip indicators   */
		if(words[i] & WORD_INDICATOR)
			continue;

		if(word_begin < 0)
		{
			if(indicators[i] & (EMP_WORD | EMP_SYMBOL))
			{
				word_begin = i;
				letter_cnt = 0;
			}
		}

		if(word_begin >= 0)
		{
			if(translate_has_attributes_at(translate, i, CHAR_LETTER))
				letter_cnt++;
			else if(translate_has_attributes_at(translate, i, CHAR_SPACE | CHAR_SEQUENCE_DELIMITER))
			{
				if(!letter_cnt)
					words[word_begin] |= WORD_NONLETTER;
				word_begin = -1;
			}
		}
	}
}

static void mark_capital_whole_words(unsigned int *indicators, unsigned char *words, const struct translate *translate)
{
	int emp_word, word_begin, letter_cnt, i;

	word_begin =
	emp_word = -1;
	letter_cnt = 0;

	for(i = 0; i < translate->input_len; i++)
	{
		/*   skip indicators   */
		if(words[i] & WORD_INDICATOR)
			continue;

		if(word_begin < 0)
		{
			if(words[i] & WORD_CHAR)
			{
				word_begin = i;
				emp_word = -1;
				letter_cnt = 0;
			}
		}

		if(word_begin >= 0)
		{
			if(emp_word < 0)
			if(indicators[i] & (EMP_WORD | EMP_SYMBOL))
				emp_word = i;

			if(translate_has_attributes_at(translate, i, CHAR_LOWER))
				letter_cnt++;

			if(!(words[i] & WORD_CHAR))
			{
				if(!letter_cnt)
				if(emp_word >= 0)
					words[emp_word] |= WORD_WHOLE;
				word_begin = -1;
				emp_word = -1;
				letter_cnt = 0;
			}
		}
	}
}

static int is_indicator_in_word(const struct translate *translate, const int at)
{
	int crs;

	for(crs = at + 1; crs < translate->input_len; crs++)
	if(translate->input[crs] == translate->input[at])
		break;

	crs++;
	if(translate_has_attributes_at(translate, crs, CHAR_UPPER))
		return 1;
	return 0;
}

static int is_indicator_delimiter_capital(const struct translate *translate, const struct table *table, const int at)
{
	if(translate->input[at] == table->marker_user)
		return is_indicator_in_word(translate, at);
	if(translate->input[at] == table->marker_begin)
		return is_indicator_in_word(translate, at);
	if(translate->input[at] == table->marker_end)
		return is_indicator_in_word(translate, at);
	if(translate->input[at] == table->marker_hard)
		return is_indicator_in_word(translate, at);
	if(translate->input[at] == table->marker_soft)
		return is_indicator_in_word(translate, at);
	return 0;
}

static int get_word_capital_whole(unsigned char *words, const int word_start, const struct translate *translate)
{
	int i;

	for(i = word_start; i < translate->input_len; i++)
	{
		if(!(words[i] & WORD_CHAR))
			break;
		if(words[i] & WORD_WHOLE)
			return i;
	}
	return -1;
}

static void capital_words_to_passages(unsigned int *indicators, unsigned char *words, const struct translate *translate, const struct table *table, const int passage_len)
{
	int word_in, word_cnt, pass_in, pass_begin, pass_end, indicator_in, word_whole, i;

	pass_begin =
	pass_end = -1;
	pass_in =
	word_in = 0;
	word_cnt = 0;
	indicator_in = 0;

	for(i = 0; i < translate->input_len; i++)
	{
		/*   indicators   */
		if(indicator_in)
		{
			if(is_indicator_delimiter(table, translate->input[i]))
				indicator_in = 0;
			continue;
		}
		else if(is_indicator_delimiter_capital(translate, table, i))
		{
			indicator_in = 1;
			continue;
		}

		if(!pass_in)
		{
			/*   word starting   */
			if(!word_in)
			{
				if(words[i] & WORD_CHAR)
				{
					word_in = 1;
					word_whole = get_word_capital_whole(words, i, translate);
					if(word_whole >= 0)
					if(!(words[word_whole] & WORD_NONLETTER))
					{
						pass_in = 1;
						pass_begin = word_whole;
						pass_end = -1;
						word_cnt = 1;
						i = word_whole;
					}
				}
			}

			/*   word ending   */
			else
			{
				if(!(words[i] & WORD_CHAR))
					word_in = 0;
			}
		}
		else
		{
			/*   word starting   */
			if(!word_in)
			{
				if(words[i] & WORD_CHAR)
				{
					word_in = 1;
					word_whole = get_word_capital_whole(words, i, translate);
					if(word_whole >= 0)
					{
						if(!(words[word_whole] & WORD_NONLETTER))
							word_cnt++;
					}
					else
					{
						if(word_cnt >= passage_len)
						if(pass_end >= 0)
							convert_to_passage(indicators, words, pass_begin, pass_end);
						pass_in = 0;
					}
				}
			}

			/*   word ending   */
			else
			{
				if(!(words[i] & WORD_CHAR))
				{
					word_in = 0;
					pass_end = i;
				}
			}
		}
	}

	/*   input end   */
	if(pass_in)
	if(word_cnt >= passage_len)
	if(pass_end >= 0)
	if(word_in)
		convert_to_passage(indicators, words, pass_begin, translate->input_len);
	else
		convert_to_passage(indicators, words, pass_begin, pass_end);
}

static void reset_words_in_passages(unsigned int *indicators, unsigned char *words, const struct translate *translate, const struct table *table)
{
	int pass_in, word_in, word_begin, word_reset, letter_cnt, indicator_in, at, i;

	word_begin =
	word_in =
	pass_in =
	word_reset =
	letter_cnt = 0;
	indicator_in = 0;

	for(i = 0; i < translate->input_len; i++)
	{
		/*   indicators   */
		if(indicator_in)
		{
			if(is_indicator_delimiter(table, translate->input[i]))
				indicator_in = 0;
			continue;
		}
		else if(is_indicator_delimiter(table, translate->input[i]))
		{
			indicator_in = 1;
			continue;
		}

		if(pass_in)
		if(indicators[i] & EMP_END)
			pass_in = 0;

		if(!pass_in)
		if(indicators[i] & EMP_BEGIN)
			pass_in = 1;
		else
		{
			/*   beginning of word   */
			if(!word_in)
			if(indicators[i] & EMP_WORD)
			{
				/*   handle case when reset
				     was at beginning of word   */
				if(!(translate_get_attributes_at(translate, i) & CHAR_LETTER))
				{
					at = i;

					/*   reset followed by marked sequence   */
					while(i + 1 < translate->input_len && words[i + 1] & WORD_INDICATOR)
						i++;

					/*   not just one reset by itself   */
					if(words[i + 1] & WORD_CHAR)
					{
						indicators[i + 1] |= EMP_WORD;
						if(words[at] & WORD_WHOLE)
							words[i + 1] |= WORD_WHOLE;
					}
					indicators[at] &= ~EMP_WORD;
					words[at] &= ~WORD_WHOLE;

					/*   if reset is a letter, make it a symbol   */
					if(translate_get_attributes_at(translate, at) & CHAR_LETTER)
						indicators[at] |= EMP_SYMBOL;

					continue;
				}

				word_in = 1;
				word_begin = i;
				letter_cnt = 0;
				word_reset = 0;
			}
			else if(indicators[i] & EMP_SYMBOL && words[i] & WORD_WHOLE)
			{
				/*   handle case when symbol is not a letter   */
				if(!(translate_get_attributes_at(translate, i) & CHAR_LETTER))
				{
					indicators[i] &= ~EMP_SYMBOL;
					words[i] &= ~WORD_WHOLE;
					continue;
				}
			}

			if(word_in)

			/*   end of word   */
			if(!(words[i] & WORD_CHAR) || (indicators[i] & EMP_WORD && indicators[i] & EMP_END))
			{
				word_in = 0;

				/*   handle symbol   */
				if(EMP_SYMBOL && letter_cnt == 1)
				{
					indicators[word_begin] |= EMP_SYMBOL;
					indicators[word_begin] &= ~EMP_WORD;
					words[word_begin] &= ~WORD_WHOLE;
					indicators[i] &= ~(EMP_END | EMP_WORD);
				}

				/*   if word ended on a reset or last char was a reset,
				     get rid of end bits   */
				if(word_reset || !(translate_get_attributes_at(translate, i) & CHAR_LETTER))
					indicators[i] &= ~(EMP_END | EMP_WORD);

				/*   if word ended when it began, get rid of all bits   */
				if(i == word_begin)
				{
					words[word_begin] &= ~WORD_WHOLE;
					indicators[i] &= ~(EMP_END | EMP_WORD);
				}
			}
			else
			{
				if(!(translate_get_attributes_at(translate, i) & CHAR_LETTER))
				{
					/*   handle symbol not already resetting   */
					if(EMP_SYMBOL && letter_cnt == 1)
					{
						indicators[word_begin] |= EMP_SYMBOL;
						indicators[word_begin] &= ~EMP_WORD;
						words[word_begin] &= ~WORD_WHOLE;
					}
					word_reset = 1;

					continue;
				}

				if(word_reset)
				{
					word_reset = 0;
					word_begin = i;
					letter_cnt = 0;
					indicators[i] |= EMP_WORD;
				}

				letter_cnt++;
			}
		}
	}

	/*   input end   */
	if(word_in)
	{
		/*   handle symbol   */
		if(EMP_SYMBOL && letter_cnt == 1)
		{
			indicators[word_begin] |= EMP_SYMBOL;
			indicators[word_begin] &= ~EMP_WORD;
			words[word_begin] &= ~WORD_WHOLE;
			indicators[i] &= ~(EMP_END | EMP_WORD);
		}

		if(word_reset)
			indicators[i] &= ~(EMP_END | EMP_WORD);
	}
}

static int insert_indicators_capital_at(struct translate *translate, const struct table *table, const unsigned int indicator, const struct mode *mode)
{
	switch(indicator & EMP_EMPHASIS)
	{
	case EMP_BEGIN:

		if(!generic_insert_marked(translate, mode->begin, mode->begin_len, table->marker_hard))
			return 0;
		break;

	case EMP_END:

		if(!generic_insert_marked(translate, mode->end, mode->end_len, table->marker_hard))
			return 0;
		break;

	case EMP_WORD:

		if(!generic_insert_marked(translate, mode->word, mode->word_len, table->marker_hard))
			return 0;
		break;

	case EMP_END | EMP_WORD:

		if(!generic_insert_marked(translate, mode->term, mode->term_len, table->marker_hard))
			return 0;
		break;

	case EMP_SYMBOL:

		if(!generic_insert_marked(translate, mode->symbol, mode->symbol_len, table->marker_hard))
			return 0;
		break;
	}

	return 1;
}

static int insert_indicators_capital(struct translate *translate, const struct table *table, const unsigned int *indicators)
{
	Unicode lower;

	translate->input_crs =
	translate->output_len = 0;
	while(translate->input_crs < translate->input_len)
	{
		if(!insert_indicators_capital_at(translate, table, indicators[translate->input_crs], &table->capital))
			return 0;

		/*   replace upper case with lower case   */
		lower = generic_upper_to_lower(table, translate->input[translate->input_crs]);
		if(lower != translate->input[translate->input_crs])
		{
			CHANGE_MARK
			if(!translate_insert_dot_for_chars(translate, lower, 1))
				return 0;
		}
		else if(!translate_copy_to_output(translate, 1, 1))
			return 0;
	}

	/*   after input   */
	if(!insert_indicators_capital_at(translate, table, indicators[translate->input_crs], &table->capital))
		return 0;

	return 1;
}

static int add_indicators_capital(struct translate *translate)
{
	const struct table *table;
	unsigned int *indicators;
	unsigned char *words;

	/*   only copy indicators from last table in tables   */
	table = translate->tables[translate->table_cnt - 1];
	translate->table_crs = translate->table_cnt - 1;

	indicators = MALLOC((translate->input_len + 1) * sizeof(unsigned int));
	if(!indicators)
	{
		LOG_ALLOCATE_FAIL
		return 0;
	}
	memset(indicators, 0, (translate->input_len + 1) * sizeof(unsigned int));

	words = MALLOC((translate->input_len + 1) * sizeof(unsigned char));
	if(!words)
	{
		LOG_ALLOCATE_FAIL
		FREE(indicators);
		return 0;
	}
	memset(words, 0, (translate->input_len + 1) * sizeof(unsigned char));

	mark_capitals(indicators, words, translate, table);
	if(table->capital.word_len)
	{
		indicators_to_words(indicators, words, translate);
		mark_nonalphabetic_words(indicators, words, translate);
		mark_capital_whole_words(indicators, words, translate);
		if(table->capital.begin_len && table->capital.passage_len)
		{
			capital_words_to_passages(indicators, words, translate, table, table->capital.passage_len);
			reset_words_in_passages(indicators, words, translate, table);
		}
	}

	if(!insert_indicators_capital(translate, table, indicators))
		goto return_fail_free;

	FREE(indicators);
	FREE(words);

#ifdef DEBUG
	translate->output[translate->output_len] = 0;
#endif

	return 1;

	return_fail_free:
	FREE(indicators);
	FREE(words);

	return 0;
}

/******************************************************************************/

static int is_letter_before(const struct translate *translate, const struct table *table)
{
	unsigned int attrs;
	int i;

	for(i = translate->input_crs - 1; i >= 0; i--)
	{
		attrs = table_get_unichar_attributes(table, translate->input[i]);
		if(attrs & CHAR_LETTER)
			return 1;
		if(!(attrs & CHAR_NUMERIC_CONT))
			break;
	}
	return 0;
}

static int is_digit_after(const struct translate *translate, const struct table *table)
{
	unsigned int attrs;
	int i;

	for(i = translate->input_crs + 1; i < translate->input_len; i++)
	{
		attrs = table_get_unichar_attributes(table, translate->input[i]);
		if(attrs & CHAR_NUMERIC_DIGIT)
			return 1;
		if(!(attrs & CHAR_NUMERIC_CONT))
			break;
	}
	return 0;
}

static int add_indicators_numeric(struct translate *translate)
{
	const struct table *table;
	unsigned int attrs;
	int numeric_in, numeric_passage_in, nocontract_in;
	Unicode uchar;

	/*   only copy indicators from last table in tables   */
	table = translate->tables[translate->table_cnt - 1];
	translate->table_crs = translate->table_cnt - 1;

	numeric_in =
	numeric_passage_in =
	nocontract_in = 0;

	translate->input_crs =
	translate->output_len = 0;
	while(translate->input_crs < translate->input_len)
	{
		/*   numeric passages   */
		if(!numeric_passage_in)
		{
			if(is_marked_indicator_begin(translate, &table->numeric))
			{
				if(!nocontract_in)
				{
					nocontract_in = 1;
					if(table->nocontract.begin_len)
					if(!generic_insert_marked(translate, table->nocontract.begin, table->nocontract.begin_len, table->marker_soft))
						return 0;
				}

				numeric_passage_in = 1;
				translate_copy_marked_indicators(translate);
				continue;
			}
		}
		else
		{
			if(is_marked_indicator_end(translate, &table->numeric))
			{
				numeric_passage_in = 0;
				translate_copy_marked_indicators(translate);

				ASSERT(nocontract_in)
				nocontract_in = 0;
				if(table->nocontract.end_len)
				if(!generic_insert_marked(translate, table->nocontract.end, table->nocontract.end_len, table->marker_soft))
					return 0;
			}
			else
			{
				if(translate_has_attributes(translate, CHAR_NUMERIC_UCHAR))
				{
					if(table->nocontract.symbol_len)
					if(!generic_insert_marked(translate, table->nocontract.symbol, table->nocontract.symbol_len, table->marker_hard))
						return 0;
				}

				uchar = generic_digit_to_uchar(table, translate->input[translate->input_crs]);
				if(uchar != translate->input[translate->input_crs])
				{
					CHANGE_MARK
					if(!translate_insert_dot_for_chars(translate, uchar, 1))
						return 0;
				}
				else if(!translate_copy_to_output(translate, 1, 1))
					return 0;
			}
			continue;
		}

		/*   numeric mode   */
		attrs = table_get_unichar_attributes(table, translate->input[translate->input_crs]);
		if(!numeric_in)
		{
			if(attrs & CHAR_NUMERIC_DIGIT)
			{
				if(!nocontract_in)
				{
					nocontract_in = 1;
					if(table->nocontract.word_len)
					if(!generic_insert_marked(translate, table->nocontract.word, table->nocontract.word_len, table->marker_soft))
						return 0;
				}

				numeric_in = 1;
				if(!generic_insert_marked(translate, table->numeric.word, table->numeric.word_len, table->marker_hard))
					return 0;
			}
			else if(attrs & CHAR_NUMERIC_CONT)
			{
				/*   for a CHAR_NUMERIC_CONT to start numeric
				     mode, it must not be preceded by a letter,
				     and must be followed by a digit   */
				if(!is_letter_before(translate, table) && is_digit_after(translate, table))
				{
					numeric_in =
					nocontract_in = 1;
					if(table->nocontract.word_len)
					if(!generic_insert_marked(translate, table->nocontract.word, table->nocontract.word_len, table->marker_soft))
						return 0;
					if(!generic_insert_marked(translate, table->numeric.word, table->numeric.word_len, table->marker_hard))
						return 0;
				}
				else if(!translate_copy_to_output(translate, 1, 1))
					return 0;
			}
			else if(nocontract_in && (attrs & (CHAR_SPACE | CHAR_SEQUENCE_DELIMITER)))
			{
				nocontract_in = 0;
				if(table->nocontract.term_len)
				{
					CHANGE_MARK
					if(!generic_insert_marked(translate, table->nocontract.term, table->nocontract.term_len, table->marker_soft))
						return 0;
				}
			}
			else if(!translate_copy_to_output(translate, 1, 1))
				return 0;
		}
		else
		{
			if(attrs & (CHAR_SPACE | CHAR_SEQUENCE_DELIMITER))
			{
				numeric_in = 0;
				CHANGE_MARK

				if(!generic_insert_marked(translate, table->numeric.end, table->numeric.end_len, table->marker_soft))
					return 0;

				ASSERT(nocontract_in)
				nocontract_in = 0;
				if(table->nocontract.term_len)
				if(!generic_insert_marked(translate, table->nocontract.term, table->nocontract.term_len, table->marker_soft))
					return 0;
			}
			else if(!(attrs & (CHAR_NUMERIC_DIGIT | CHAR_NUMERIC_CONT)))
			{
				CHANGE_MARK
				if(!generic_insert_marked(translate, table->numeric.end, table->numeric.end_len, table->marker_soft))
					return 0;
				if(attrs & CHAR_NUMERIC_TERM)
				if(!generic_insert_marked(translate, table->numeric.term, table->numeric.term_len, table->marker_hard))
					return 0;
				numeric_in = 0;
			}
			else
			{
				uchar = generic_digit_to_uchar(table, translate->input[translate->input_crs]);
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
	}

	if(nocontract_in)
	if(table->nocontract.term_len)
	{
		CHANGE_MARK
		if(!generic_insert_marked(translate, table->nocontract.term, table->nocontract.term_len, table->marker_soft))
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

int translate_generic_forward(struct translate *translate)
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

	CHANGE_CHECK
	if(!translate_output_to_input(translate))
		return 0;

	CHANGE_RESET
	convert_user_indicators(translate);
	CHANGE_CHECK
	processed = 1;

	if(translate_get_emphases_cnt(translate))
	{
		CHANGE_CHECK
		if(!translate_output_to_input(translate))
			return 0;

		CHANGE_RESET
		if(!add_indicators_emphases(translate))
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

	if(translate_is_capital_set(translate))
	{
		CHANGE_CHECK
		if(!translate_output_to_input(translate))
			return 0;

		CHANGE_RESET
		add_indicators_capital(translate);
		CHANGE_CHECK
		processed = 1;
	}

	if(translate_is_numeric_set(translate))
	{
		CHANGE_CHECK
		if(!translate_output_to_input(translate))
			return 0;

		CHANGE_RESET
		add_indicators_numeric(translate);
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
