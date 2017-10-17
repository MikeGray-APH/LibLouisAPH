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

#include "table.h"
#include "log.h"

/******************************************************************************/

int table_init(struct table *table)
{
	ASSERT(table)

	memset(table, 0, sizeof(struct table));
	return 1;
}

void table_fini(struct table *table)
{
	struct rule rule_auto;
	int i;

	if(!table)
		return;

	memset(&rule_auto, 0, sizeof(struct rule));

	for(i = 0; i < TABLE_UNICHAR_HASH_SIZE; i++)
		unichar_free(table->unichar_hash[i]);

#ifdef TABLE_ALLOCATE_HASHES

	if(table->init_dots_hash)
	{
		for(i = 0; i < TABLE_DOTS_HASH_SIZE; i++)
		{
			rule_auto.dots_nxt = table->init_dots_hash[i];
			rule_free_backward(&rule_auto);
		}
		FREE(table->init_dots_hash);
	}
	if(table->init_chars_hash)
	{
		for(i = 0; i < TABLE_INIT_HASH_SIZE; i++)
			rule_free(table->init_chars_hash[i]);
		FREE(table->init_chars_hash);
	}

	if(table->premode_dots_hash)
	{
		for(i = 0; i < TABLE_DOTS_HASH_SIZE; i++)
		{
			rule_auto.dots_nxt = table->premode_dots_hash[i];
			rule_free_backward(&rule_auto);
		}
		FREE(table->premode_dots_hash);
	}
	if(table->premode_chars_hash)
	{
		for(i = 0; i < TABLE_PREMODE_HASH_SIZE; i++)
			rule_free(table->premode_chars_hash[i]);
		FREE(table->premode_chars_hash);
	}

	if(table->postmode_dots_hash)
	{
		for(i = 0; i < TABLE_DOTS_HASH_SIZE; i++)
		{
			rule_auto.dots_nxt = table->postmode_dots_hash[i];
			rule_free_backward(&rule_auto);
		}
		FREE(table->postmode_dots_hash);
	}
	if(table->postmode_chars_hash)
	{
		for(i = 0; i < TABLE_POSTMODE_HASH_SIZE; i++)
			rule_free(table->postmode_chars_hash[i]);
		FREE(table->postmode_chars_hash);
	}

	if(table->pretrans_dots_hash)
	{
		for(i = 0; i < TABLE_DOTS_HASH_SIZE; i++)
		{
			rule_auto.dots_nxt = table->pretrans_dots_hash[i];
			rule_free_backward(&rule_auto);
		}
		FREE(table->pretrans_dots_hash);
	}
	if(table->pretrans_chars_hash)
	{
		for(i = 0; i < TABLE_PRETRANS_HASH_SIZE; i++)
			rule_free(table->pretrans_chars_hash[i]);
		FREE(table->pretrans_chars_hash);
	}

	if(table->trans_dots_hash)
	{
		for(i = 0; i < TABLE_DOTS_HASH_SIZE; i++)
		{
			rule_auto.dots_nxt = table->trans_dots_hash[i];
			rule_free_backward(&rule_auto);
		}
		FREE(table->trans_dots_hash);
	}
	if(table->trans_chars_hash)
	{
		for(i = 0; i < TABLE_TRANS_HASH_SIZE; i++)
			rule_free(table->trans_chars_hash[i]);
		FREE(table->trans_chars_hash);
	}

	if(table->posttrans_dots_hash)
	{
		for(i = 0; i < TABLE_DOTS_HASH_SIZE; i++)
		{
			rule_auto.dots_nxt = table->posttrans_dots_hash[i];
			rule_free_backward(&rule_auto);
		}
		FREE(table->posttrans_dots_hash);
	}
	if(table->posttrans_chars_hash)
	{
		for(i = 0; i < TABLE_POSTTRANS_HASH_SIZE; i++)
			rule_free(table->posttrans_chars_hash[i]);
		FREE(table->posttrans_chars_hash);
	}

	if(table->fini_dots_hash)
	{
		for(i = 0; i < TABLE_DOTS_HASH_SIZE; i++)
		{
			rule_auto.dots_nxt = table->fini_dots_hash[i];
			rule_free_backward(&rule_auto);
		}
		FREE(table->fini_dots_hash);
	}
	if(table->fini_chars_hash)
	{
		for(i = 0; i < TABLE_FINI_HASH_SIZE; i++)
			rule_free(table->fini_chars_hash[i]);
		FREE(table->fini_chars_hash);
	}

#else

	for(i = 0; i < TABLE_DOTS_HASH_SIZE; i++)
	{
		rule_auto.dots_nxt = table->init_dots_hash[i];
		rule_free_backward(&rule_auto);
	}
	for(i = 0; i < TABLE_INIT_HASH_SIZE; i++)
		rule_free(table->init_chars_hash[i]);

	for(i = 0; i < TABLE_DOTS_HASH_SIZE; i++)
	{
		rule_auto.dots_nxt = table->premode_dots_hash[i];
		rule_free_backward(&rule_auto);
	}
	for(i = 0; i < TABLE_PREMODE_HASH_SIZE; i++)
		rule_free(table->premode_chars_hash[i]);

	for(i = 0; i < TABLE_DOTS_HASH_SIZE; i++)
	{
		rule_auto.dots_nxt = table->postmode_dots_hash[i];
		rule_free_backward(&rule_auto);
	}
	for(i = 0; i < TABLE_POSTMODE_HASH_SIZE; i++)
		rule_free(table->postmode_chars_hash[i]);

	for(i = 0; i < TABLE_DOTS_HASH_SIZE; i++)
	{
		rule_auto.dots_nxt = table->pretrans_dots_hash[i];
		rule_free_backward(&rule_auto);
	}
	for(i = 0; i < TABLE_PRETRANS_HASH_SIZE; i++)
		rule_free(table->pretrans_chars_hash[i]);

	for(i = 0; i < TABLE_DOTS_HASH_SIZE; i++)
	{
		rule_auto.dots_nxt = table->trans_dots_hash[i];
		rule_free_backward(&rule_auto);
	}
	for(i = 0; i < TABLE_TRANS_HASH_SIZE; i++)
		rule_free(table->trans_chars_hash[i]);

	for(i = 0; i < TABLE_DOTS_HASH_SIZE; i++)
	{
		rule_auto.dots_nxt = table->posttrans_dots_hash[i];
		rule_free_backward(&rule_auto);
	}
	for(i = 0; i < TABLE_POSTTRANS_HASH_SIZE; i++)
		rule_free(table->posttrans_chars_hash[i]);

	for(i = 0; i < TABLE_DOTS_HASH_SIZE; i++)
	{
		rule_auto.dots_nxt = table->fini_dots_hash[i];
		rule_free_backward(&rule_auto);
	}
	for(i = 0; i < TABLE_FINI_HASH_SIZE; i++)
		rule_free(table->fini_chars_hash[i]);

#endif

	mode_free(table->emphases);
	filter_free(table->filters);
	subpattern_free(table->subpatterns);
	if(table->file_name)
		FREE(table->file_name);
}

ATTRIBUTE_FUNCTION_MALLOC
struct table* table_allocate(void)
{
	struct table *table;

	table = MALLOC(sizeof(struct table));
	LOG_ALLOCATE_FAIL_RETURN_NULL(table)
	table_init(table);
	return table;
}

void table_free(struct table *table)
{
	if(!table)
		return;

	table_free(table->nxt);
	table_fini(table);
	FREE(table);
}

/******************************************************************************/

static inline int uchar_get_hash(const Unicode uchar, const unsigned int hash_size)
{
	return uchar % hash_size;
}

/******************************************************************************/

ATTRIBUTE_FUNCTION_MALLOC
struct unichar* unichar_allocate(void)
{
	struct unichar *unichar;

	unichar = MALLOC(sizeof(struct unichar));
	LOG_ALLOCATE_FAIL_RETURN_NULL(unichar)
	memset(unichar, 0, sizeof(struct unichar));
	return unichar;
}

void unichar_free(struct unichar *unichar)
{
	if(!unichar)
		return;

	unichar_free(unichar->nxt);
	FREE(unichar);
}

/******************************************************************************/

struct unichar* table_find_unichar(const struct table *table, const Unicode uchar)
{
	struct unichar *unichar;
	int hash;

	hash = uchar_get_hash(uchar, TABLE_UNICHAR_HASH_SIZE);
	unichar = table->unichar_hash[hash];

	while(unichar)
	if(unichar->uchar == uchar)
		break;
	else
		unichar = unichar->nxt;

	return unichar;
}

struct unichar* table_find_or_add_unichar(struct table *table, const Unicode uchar)
{
	struct unichar *unichar;
	int hash;

	hash = uchar_get_hash(uchar, TABLE_UNICHAR_HASH_SIZE);
	if(!table->unichar_hash[hash])
		table->unichar_hash[hash] =
		unichar = unichar_allocate();
	else
	{
		unichar = table->unichar_hash[hash];

		/*   find end of list, checking for match
		     along the way   */
		while(unichar->nxt)
		if(unichar->uchar == uchar)
			return unichar;
		else
			unichar = unichar->nxt;
		if(unichar->uchar == uchar)
			return unichar;

		unichar->nxt = unichar_allocate();
		unichar = unichar->nxt;
	}

	unichar->uchar = uchar;
	return unichar;
}

/******************************************************************************/

ATTRIBUTE_FUNCTION_MALLOC
struct mode* mode_allocate(void)
{
	struct mode *mode;

	mode = MALLOC(sizeof(struct mode));
	LOG_ALLOCATE_FAIL_RETURN_NULL(mode)
	memset(mode, 0, sizeof(struct mode));
	return mode;
}

void mode_free(struct mode *mode)
{
	if(!mode)
		return;

	mode_free(mode->nxt);
	ASSERT(mode->name)
	FREE(mode->name);
	FREE(mode);
}

/******************************************************************************/

ATTRIBUTE_FUNCTION_MALLOC
struct filter* filter_allocate(void)
{
	struct filter *filter;

	filter = MALLOC(sizeof(struct filter));
	LOG_ALLOCATE_FAIL_RETURN_NULL(filter)
	memset(filter, 0, sizeof(struct filter));
	return filter;
}

void filter_free(struct filter *filter)
{
	if(!filter)
		return;

	filter_free(filter->nxt);
	if(filter->before)
		FREE(filter->before);
	if(filter->after)
		FREE(filter->after);
	if(filter->name)
		FREE(filter->name);
	FREE(filter);
}

/******************************************************************************/

ATTRIBUTE_FUNCTION_MALLOC
struct rule* rule_allocate(void)
{
	struct rule *rule;

	rule = MALLOC(sizeof(struct rule));
	LOG_ALLOCATE_FAIL_RETURN_NULL(rule)
	memset(rule, 0, sizeof(struct rule));
	return rule;
}

void rule_free(struct rule *rule)
{
	if(!rule)
		return;

	rule_free(rule->chars_nxt);

	if(rule->filter_forward)
	if(!rule->filter_forward->name)
	{
		ASSERT(!rule->filter_forward->nxt)
		filter_free(rule->filter_forward);
	}
	if(rule->filter_backward)
	if(!rule->filter_backward->name)
	{
		ASSERT(!rule->filter_backward->nxt)
		filter_free(rule->filter_backward);
	}

	FREE(rule);
}

void rule_free_backward(struct rule *rule)
{
	struct rule *nxt;

	if(!rule)
		return;

	while(rule->dots_nxt)
	{
		if(rule->dots_nxt->direction != BACKWARD)
			break;

		nxt = rule->dots_nxt;
		rule->dots_nxt = nxt->dots_nxt;
		nxt->chars_nxt = NULL;
		rule_free(nxt);
	}

	rule_free_backward(rule->dots_nxt);
}

/******************************************************************************/

int table_convert_escape_markers(const struct table *table, Unicode *uchars, const int uchars_len)
{
	int crs, off;

	if(uchars_len < 2)
		return uchars_len;

	crs =
	off = 0;
	while(off < uchars_len)
	{
		if(!uchars[off])
			break;
		else if(uchars[off] == u'\\')
		{
			off++;
			if(!uchars[off])
				return 0;
			else if(off >= uchars_len)
				return 0;
			switch(uchars[off])
			{
			case u'U':  uchars[crs++] = table->marker_user;      off++;  break;
			case u'B':  uchars[crs++] = table->marker_begin;     off++;  break;
			case u'E':  uchars[crs++] = table->marker_end;       off++;  break;
			case u'M':  uchars[crs++] = table->marker_modifier;  off++;  break;
			case u'H':  uchars[crs++] = table->marker_hard;      off++;  break;
			case u'S':  uchars[crs++] = table->marker_soft;      off++;  break;
			case u'I':  uchars[crs++] = table->marker_internal;  off++;  break;

			default:

				uchars[crs++] = uchars[off - 1];
				uchars[crs++] = uchars[off++];
				break;
			}
		}
		else
			uchars[crs++] = uchars[off++];
	}

	if(crs <= uchars_len)
		uchars[crs] = 0;
#ifdef DEBUG
	else
		ASSERT(0)
#endif
	return crs;
}

/******************************************************************************/

static int rule_chars_compare(const struct rule *const rule0, const struct rule *const rule1)
{
	if(rule0->chars_len > rule1->chars_len)
		return -1;
	else if(rule0->chars_len == rule1->chars_len)
	{
		if(rule0->filter_forward)
		{
			if(rule1->filter_forward)
			{
				if(rule0->dots_len > rule1->dots_len)
					return -1;
				else if(rule0->dots_len == rule1->dots_len)
					return 0;
				else
					return 1;
			}
			else
				return -1;
		}
		else
		{
			if(rule1->filter_forward)
				return 1;
			else
			{
				if(rule0->dots_len > rule1->dots_len)
					return -1;
				else if(rule0->dots_len == rule1->dots_len)
					return 0;
				else
					return 1;
			}
		}
	}
	else
		return 1;
}

static int rule_dots_compare(const struct rule *const rule0, const struct rule *const rule1)
{
	if(rule0->dots_len > rule1->dots_len)
		return -1;
	else if(rule0->dots_len == rule1->dots_len)
	{
		if(rule0->filter_backward)
		{
			if(rule1->filter_backward)
			{
				if(rule0->chars_len > rule1->chars_len)
					return -1;
				else if(rule0->chars_len == rule1->chars_len)
					return 0;
				else
					return 1;
			}
			else
				return -1;
		}
		else
		{
			if(rule1->filter_backward)
				return 1;
			else
			{
				if(rule0->chars_len > rule1->chars_len)
					return -1;
				else if(rule0->chars_len == rule1->chars_len)
					return 0;
				else
					return 1;
			}
		}
	}
	else
		return 1;
}

static struct rule* rule_add_new(
	struct rule **chars_hash,
	int *chars_hash_cnt,
	const unsigned int chars_hash_size,
	struct rule **dots_hash,
	int *dots_hash_cnt,
	const unsigned int dots_hash_size,
	struct filter *filter_forward,
	struct filter *filter_backward,
	const Unicode *chars,
	const int chars_len,
	const Unicode *dots,
	const int dots_len,
	const int chars_weight,
	const int dots_weight)
{
	struct rule *rule_new, *rule_crs;
	int hash;
	int i;

	rule_new = rule_allocate();
	if(!rule_new)
		return NULL;

	for(i = 0; i < chars_len; i++)
		rule_new->chars[i] = chars[i];
	rule_new->chars_len = chars_len;

	for(i = 0; i < dots_len; i++)
		rule_new->dots[i] = dots[i];
	rule_new->dots_len = dots_len;

	/*   must be set before adding rule to chains   */
	rule_new->filter_forward = filter_forward;
	rule_new->filter_backward = filter_backward;

	/*   add to chars_hash   */

	if(!chars_hash)
		goto add_to_dots_hash;

	hash = uchar_get_hash(chars[0], chars_hash_size);
	rule_crs = chars_hash[hash];

	/*   empty chain   */
	if(!rule_crs)
	{
		chars_hash[hash] = rule_new;
		goto add_to_dots_hash;
	}

	/*   check first rule in chain   */
	if(rule_chars_compare(rule_crs, rule_new) >= chars_weight)
	{
		rule_new->chars_nxt = rule_crs;
		chars_hash[hash] = rule_new;
		goto add_to_dots_hash;
	}

	/*   find rule position in chain   */
	while(rule_crs->chars_nxt && rule_chars_compare(rule_crs->chars_nxt, rule_new) < chars_weight)
		rule_crs = rule_crs->chars_nxt;

	rule_new->chars_nxt = rule_crs->chars_nxt;
	rule_crs->chars_nxt = rule_new;

	/*   add to dots_hash   */
	add_to_dots_hash:

	if(!dots_hash)
		goto return_rule;

	hash = uchar_get_hash(dots[0], dots_hash_size);
	rule_crs = dots_hash[hash];

	/*   empty chain   */
	if(!rule_crs)
	{
		dots_hash[hash] = rule_new;
		goto return_rule;
	}

	/*   check first rule in chain   */
	if(rule_dots_compare(rule_crs, rule_new) >= dots_weight)
	{
		rule_new->dots_nxt = rule_crs;
		dots_hash[hash] = rule_new;
		goto return_rule;
	}

	/*   find rule position in chain   */
	while(rule_crs->dots_nxt && rule_dots_compare(rule_crs->dots_nxt, rule_new) < dots_weight)
		rule_crs = rule_crs->dots_nxt;

	rule_new->dots_nxt = rule_crs->dots_nxt;
	rule_crs->dots_nxt = rule_new;

	return_rule:

	if(chars_hash_cnt)
		*chars_hash_cnt = *chars_hash_cnt + 1;
	if(dots_hash_cnt)
		*dots_hash_cnt = *dots_hash_cnt + 1;

	return rule_new;
}

struct rule* table_add_rule(
	struct table *table,
	const enum table_hash_type hash_type,
	const enum rule_direction direction,
	struct filter *filter_forward,
	struct filter *filter_backward,
	const Unicode *chars,
	const int chars_len,
	const Unicode *dots,
	const int dots_len,
	const int chars_weight,
	const int dots_weight)
{
	struct rule **chars_hash, **dots_hash;
	int *chars_hash_cnt, *dots_hash_cnt;
	unsigned int chars_hash_size, dots_hash_size;

	//NOTE:  these affect the function above when compiling optimal
	chars_hash =
	dots_hash = NULL;
	chars_hash_cnt =
	dots_hash_cnt = NULL;

#ifdef TABLE_ALLOCATE_HASHES
	int size;
#endif

	switch(hash_type)
	{
#ifdef TABLE_ALLOCATE_HASHES

	case TABLE_HASH_INIT:

		if(!table->init_chars_hash)
		{
			size = TABLE_INIT_HASH_SIZE * sizeof(struct rule*);
			table->init_chars_hash = MALLOC(size);
			LOG_ALLOCATE_FAIL_RETURN_NULL(table->init_chars_hash)
			memset(table->init_chars_hash, 0, size);
		}
		if(!table->init_dots_hash)
		{
			ASSERT(table->init_chars_hash)
			size = TABLE_DOTS_HASH_SIZE * sizeof(struct rule*);
			table->init_dots_hash = MALLOC(size);
			LOG_ALLOCATE_FAIL_RETURN_NULL(table->init_dots_hash)
			memset(table->init_dots_hash, 0, size);
		}
		chars_hash = table->init_chars_hash;
		chars_hash_cnt = &table->init_chars_hash_cnt;
		chars_hash_size = TABLE_INIT_HASH_SIZE;
		dots_hash = table->init_dots_hash;
		dots_hash_cnt = &table->init_dots_hash_cnt;
		dots_hash_size = TABLE_DOTS_HASH_SIZE;
		break;

	case TABLE_HASH_PREMODE:

		if(!table->premode_chars_hash)
		{
			size = TABLE_PREMODE_HASH_SIZE * sizeof(struct rule*);
			table->premode_chars_hash = MALLOC(size);
			LOG_ALLOCATE_FAIL_RETURN_NULL(table->premode_chars_hash)
			memset(table->premode_chars_hash, 0, size);
		}
		if(!table->premode_dots_hash)
		{
			ASSERT(table->premode_chars_hash)
			size = TABLE_DOTS_HASH_SIZE * sizeof(struct rule*);
			table->premode_dots_hash = MALLOC(size);
			LOG_ALLOCATE_FAIL_RETURN_NULL(table->premode_dots_hash)
			memset(table->premode_dots_hash, 0, size);
		}
		chars_hash = table->premode_chars_hash;
		chars_hash_cnt = &table->premode_chars_hash_cnt;
		chars_hash_size = TABLE_PREMODE_HASH_SIZE;
		dots_hash = table->premode_dots_hash;
		dots_hash_cnt = &table->premode_dots_hash_cnt;
		dots_hash_size = TABLE_DOTS_HASH_SIZE;
		break;

	case TABLE_HASH_POSTMODE:

		if(!table->postmode_chars_hash)
		{
			size = TABLE_POSTMODE_HASH_SIZE * sizeof(struct rule*);
			table->postmode_chars_hash = MALLOC(size);
			LOG_ALLOCATE_FAIL_RETURN_NULL(table->postmode_chars_hash)
			memset(table->postmode_chars_hash, 0, size);
		}
		if(!table->postmode_dots_hash)
		{
			ASSERT(table->postmode_chars_hash)
			size = TABLE_DOTS_HASH_SIZE * sizeof(struct rule*);
			table->postmode_dots_hash = MALLOC(size);
			LOG_ALLOCATE_FAIL_RETURN_NULL(table->postmode_dots_hash)
			memset(table->postmode_dots_hash, 0, size);
		}
		chars_hash = table->postmode_chars_hash;
		chars_hash_cnt = &table->postmode_chars_hash_cnt;
		chars_hash_size = TABLE_POSTMODE_HASH_SIZE;
		dots_hash = table->postmode_dots_hash;
		dots_hash_cnt = &table->postmode_dots_hash_cnt;
		dots_hash_size = TABLE_DOTS_HASH_SIZE;
		break;

	case TABLE_HASH_PRETRANS:

		if(!table->pretrans_chars_hash)
		{
			size = TABLE_PRETRANS_HASH_SIZE * sizeof(struct rule*);
			table->pretrans_chars_hash = MALLOC(size);
			LOG_ALLOCATE_FAIL_RETURN_NULL(table->pretrans_chars_hash)
			memset(table->pretrans_chars_hash, 0, size);
		}
		if(!table->pretrans_dots_hash)
		{
			ASSERT(table->pretrans_chars_hash)
			size = TABLE_DOTS_HASH_SIZE * sizeof(struct rule*);
			table->pretrans_dots_hash = MALLOC(size);
			LOG_ALLOCATE_FAIL_RETURN_NULL(table->pretrans_dots_hash)
			memset(table->pretrans_dots_hash, 0, size);
		}
		chars_hash = table->pretrans_chars_hash;
		chars_hash_cnt = &table->pretrans_chars_hash_cnt;
		chars_hash_size = TABLE_PRETRANS_HASH_SIZE;
		dots_hash = table->pretrans_dots_hash;
		dots_hash_cnt = &table->pretrans_dots_hash_cnt;
		dots_hash_size = TABLE_DOTS_HASH_SIZE;
		break;

	case TABLE_HASH_TRANS:

		if(!table->trans_chars_hash)
		{
			ASSERT(!table->trans_dots_hash)
			size = TABLE_TRANS_HASH_SIZE * sizeof(struct rule*);
			table->trans_chars_hash = MALLOC(size);
			LOG_ALLOCATE_FAIL_RETURN_NULL(table->trans_chars_hash)
			memset(table->trans_chars_hash, 0, size);
		}
		if(!table->trans_dots_hash)
		{
			ASSERT(table->trans_chars_hash)
			size = TABLE_DOTS_HASH_SIZE * sizeof(struct rule*);
			table->trans_dots_hash = MALLOC(size);
			LOG_ALLOCATE_FAIL_RETURN_NULL(table->trans_dots_hash)
			memset(table->trans_dots_hash, 0, size);
		}
		chars_hash = table->trans_chars_hash;
		chars_hash_cnt = &table->trans_chars_hash_cnt;
		chars_hash_size = TABLE_TRANS_HASH_SIZE;
		dots_hash = table->trans_dots_hash;
		dots_hash_cnt = &table->trans_dots_hash_cnt;
		dots_hash_size = TABLE_DOTS_HASH_SIZE;
		break;

	case TABLE_HASH_POSTTRANS:

		if(!table->posttrans_chars_hash)
		{
			ASSERT(!table->posttrans_dots_hash)
			size = TABLE_TRANS_HASH_SIZE * sizeof(struct rule*);
			table->posttrans_chars_hash = MALLOC(size);
			LOG_ALLOCATE_FAIL_RETURN_NULL(table->posttrans_chars_hash)
			memset(table->posttrans_chars_hash, 0, size);
		}
		if(!table->posttrans_dots_hash)
		{
			ASSERT(table->posttrans_chars_hash)
			size = TABLE_DOTS_HASH_SIZE * sizeof(struct rule*);
			table->posttrans_dots_hash = MALLOC(size);
			LOG_ALLOCATE_FAIL_RETURN_NULL(table->posttrans_dots_hash)
			memset(table->posttrans_dots_hash, 0, size);
		}
		chars_hash = table->posttrans_chars_hash;
		chars_hash_cnt = &table->posttrans_chars_hash_cnt;
		chars_hash_size = TABLE_POSTTRANS_HASH_SIZE;
		dots_hash = table->posttrans_dots_hash;
		dots_hash_cnt = &table->posttrans_dots_hash_cnt;
		dots_hash_size = TABLE_DOTS_HASH_SIZE;
		break;

	case TABLE_HASH_FINI:

		if(!table->fini_chars_hash)
		{
			size = TABLE_FINI_HASH_SIZE * sizeof(struct rule*);
			table->fini_chars_hash = MALLOC(size);
			LOG_ALLOCATE_FAIL_RETURN_NULL(table->fini_chars_hash)
			memset(table->fini_chars_hash, 0, size);
		}
		if(!table->fini_dots_hash)
		{
			ASSERT(table->fini_chars_hash)
			size = TABLE_DOTS_HASH_SIZE * sizeof(struct rule*);
			table->fini_dots_hash = MALLOC(size);
			LOG_ALLOCATE_FAIL_RETURN_NULL(table->fini_dots_hash)
			memset(table->fini_dots_hash, 0, size);
		}
		chars_hash = table->fini_chars_hash;
		chars_hash_cnt = &table->fini_chars_hash_cnt;
		chars_hash_size = TABLE_FINI_HASH_SIZE;
		dots_hash = table->fini_dots_hash;
		dots_hash_cnt = &table->fini_dots_hash_cnt;
		dots_hash_size = TABLE_DOTS_HASH_SIZE;
		break;

#else

	case TABLE_HASH_INIT:

		chars_hash = table->init_chars_hash;
		chars_hash_cnt = &table->init_chars_hash_cnt;
		chars_hash_size = TABLE_INIT_HASH_SIZE;
		dots_hash = table->init_dots_hash;
		dots_hash_cnt = &table->init_dots_hash_cnt;
		dots_hash_size = TABLE_DOTS_HASH_SIZE;
		break;

	case TABLE_HASH_PREMODE:

		chars_hash = table->premode_chars_hash;
		chars_hash_cnt = &table->premode_chars_hash_cnt;
		chars_hash_size = TABLE_PREMODE_HASH_SIZE;
		dots_hash = table->premode_dots_hash;
		dots_hash_cnt = &table->premode_dots_hash_cnt;
		dots_hash_size = TABLE_DOTS_HASH_SIZE;
		break;

	case TABLE_HASH_POSTMODE:

		chars_hash = table->postmode_chars_hash;
		chars_hash_cnt = &table->postmode_chars_hash_cnt;
		chars_hash_size = TABLE_POSTMODE_HASH_SIZE;
		dots_hash = table->postmode_dots_hash;
		dots_hash_cnt = &table->postmode_dots_hash_cnt;
		dots_hash_size = TABLE_DOTS_HASH_SIZE;
		break;

	case TABLE_HASH_PRETRANS:

		chars_hash = table->pretrans_chars_hash;
		chars_hash_cnt = &table->pretrans_chars_hash_cnt;
		chars_hash_size = TABLE_PRETRANS_HASH_SIZE;
		dots_hash = table->pretrans_dots_hash;
		dots_hash_cnt = &table->pretrans_dots_hash_cnt;
		dots_hash_size = TABLE_DOTS_HASH_SIZE;
		break;

	case TABLE_HASH_TRANS:

		chars_hash = table->trans_chars_hash;
		chars_hash_cnt = &table->trans_chars_hash_cnt;
		chars_hash_size = TABLE_TRANS_HASH_SIZE;
		dots_hash = table->trans_dots_hash;
		dots_hash_cnt = &table->trans_dots_hash_cnt;
		dots_hash_size = TABLE_DOTS_HASH_SIZE;
		break;

	case TABLE_HASH_POSTTRANS:

		chars_hash = table->posttrans_chars_hash;
		chars_hash_cnt = &table->posttrans_chars_hash_cnt;
		chars_hash_size = TABLE_POSTTRANS_HASH_SIZE;
		dots_hash = table->posttrans_dots_hash;
		dots_hash_cnt = &table->posttrans_dots_hash_cnt;
		dots_hash_size = TABLE_DOTS_HASH_SIZE;
		break;

	case TABLE_HASH_FINI:

		chars_hash = table->fini_chars_hash;
		chars_hash_cnt = &table->fini_chars_hash_cnt;
		chars_hash_size = TABLE_FINI_HASH_SIZE;
		dots_hash = table->fini_dots_hash;
		dots_hash_cnt = &table->fini_dots_hash_cnt;
		dots_hash_size = TABLE_DOTS_HASH_SIZE;
		break;
#endif

	case TABLE_HASH_NONE:

		log_message(LOG_FATAL, "%s:%d  table_add_rule failed", __FILE__, __LINE__);
		ASSERT(0)
		return NULL;
	}

	switch(direction)
	{
	case BOTH:

		return rule_add_new(
			chars_hash, chars_hash_cnt, chars_hash_size,
			dots_hash, dots_hash_cnt, dots_hash_size,
			filter_forward, filter_backward, chars, chars_len, dots, dots_len, chars_weight, dots_weight);
	case FORWARD:

		return rule_add_new(
			chars_hash, chars_hash_cnt, chars_hash_size,
			NULL, NULL, 0,
			filter_forward, filter_backward, chars, chars_len, dots, dots_len, chars_weight, dots_weight);
	case BACKWARD:

		return rule_add_new(
			NULL, NULL, 0,
			dots_hash, dots_hash_cnt, dots_hash_size,
			filter_forward, filter_backward, chars, chars_len, dots, dots_len, chars_weight, dots_weight);
	}

	ASSERT(0);
	return NULL;
}

/******************************************************************************/

static int rule_chars_is_match(const struct rule *rule, const Unicode *uchars, const int uchars_len)
{
	int i;

	if(rule->chars_len > uchars_len)
		return 0;

	for(i = 0; i < rule->chars_len; i++)
	if(uchars[i] != rule->chars[i])
		return 0;

	return 1;
}

static int rule_dots_is_match(const struct rule *rule, const Unicode *uchars, const int uchars_len)
{
	int i;

	if(rule->dots_len > uchars_len)
		return 0;

	for(i = 0; i < rule->dots_len; i++)
	if(uchars[i] != rule->dots[i])
		return 0;

	return 1;
}

static const struct rule* rule_match_forward(
	const struct rule *const*rule_hash,
	const unsigned int hash_size,
	const Unicode *chars,
	const int chars_len,
	const struct rule *at)
{
	const struct rule *rule;
	int hash;

	if(!rule_hash)
		return NULL;

	if(at)
		rule = at->chars_nxt;
	else
	{
		hash = uchar_get_hash(chars[0], hash_size);
		rule = rule_hash[hash];
	}

	while(rule)
	{
		if(rule_chars_is_match(rule, chars, chars_len))
			break;
		else
			rule = rule->chars_nxt;
	}

	return rule;
}

static const struct rule* rule_match_backward(
	const struct rule * const *rule_hash,
	const unsigned int hash_size,
	const Unicode *chars,
	const int chars_len,
	const struct rule *at)
{
	const struct rule *rule;
	int hash;

	if(!rule_hash)
		return NULL;

	if(at)
		rule = at->dots_nxt;
	else
	{
		hash = uchar_get_hash(chars[0], hash_size);
		rule = rule_hash[hash];
	}

	while(rule)
	if(rule_dots_is_match(rule, chars, chars_len))
		break;
	else
		rule = rule->dots_nxt;

	return rule;
}

const struct rule* table_match_rule(
	const struct table *table,
	const enum table_hash_type hash_type,
	const enum rule_direction direction,
	const Unicode *uchars,
	const int uchars_len,
	const struct rule *at)
{
	switch(hash_type)
	{
#ifdef TABLE_ALLOCATE_HASHES
//NOTE:  this code will actually work whether TABLE_ALLOCATE_HASHES is defined or not

	case TABLE_HASH_INIT:

		if(direction == FORWARD)
			return rule_match_forward((const struct rule* const*)table->init_chars_hash, TABLE_INIT_HASH_SIZE, uchars, uchars_len, at);
		else
			return rule_match_backward((const struct rule* const*)table->init_dots_hash, TABLE_DOTS_HASH_SIZE, uchars, uchars_len, at);

	case TABLE_HASH_PREMODE:

		if(direction == FORWARD)
			return rule_match_forward((const struct rule* const*)table->premode_chars_hash, TABLE_PREMODE_HASH_SIZE, uchars, uchars_len, at);
		else
			return rule_match_backward((const struct rule* const*)table->premode_dots_hash, TABLE_DOTS_HASH_SIZE, uchars, uchars_len, at);

	case TABLE_HASH_POSTMODE:

		if(direction == FORWARD)
			return rule_match_forward((const struct rule* const*)table->postmode_chars_hash, TABLE_POSTMODE_HASH_SIZE, uchars, uchars_len, at);
		else
			return rule_match_backward((const struct rule* const*)table->postmode_dots_hash, TABLE_DOTS_HASH_SIZE, uchars, uchars_len, at);

	case TABLE_HASH_PRETRANS:

		if(direction == FORWARD)
			return rule_match_forward((const struct rule* const*)table->pretrans_chars_hash, TABLE_PRETRANS_HASH_SIZE, uchars, uchars_len, at);
		else
			return rule_match_backward((const struct rule* const*)table->pretrans_dots_hash, TABLE_DOTS_HASH_SIZE, uchars, uchars_len, at);

	case TABLE_HASH_TRANS:

		if(direction == FORWARD)
			return rule_match_forward((const struct rule* const*)table->trans_chars_hash, TABLE_TRANS_HASH_SIZE, uchars, uchars_len, at);
		else
			return rule_match_backward((const struct rule* const*)table->trans_dots_hash, TABLE_DOTS_HASH_SIZE, uchars, uchars_len, at);

	case TABLE_HASH_POSTTRANS:

		if(direction == FORWARD)
			return rule_match_forward((const struct rule* const*)table->posttrans_chars_hash, TABLE_POSTTRANS_HASH_SIZE, uchars, uchars_len, at);
		else
			return rule_match_backward((const struct rule* const*)table->posttrans_dots_hash, TABLE_DOTS_HASH_SIZE, uchars, uchars_len, at);

	case TABLE_HASH_FINI:

		if(direction == FORWARD)
			return rule_match_forward((const struct rule* const*)table->fini_chars_hash, TABLE_FINI_HASH_SIZE, uchars, uchars_len, at);
		else
			return rule_match_backward((const struct rule* const*)table->fini_dots_hash, TABLE_DOTS_HASH_SIZE, uchars, uchars_len, at);

#else

	case TABLE_HASH_INIT:

		if(direction == FORWARD)
			return rule_match_forward((const struct rule* const*)&table->init_chars_hash, TABLE_INIT_HASH_SIZE, uchars, uchars_len, at);
		else
			return rule_match_backward((const struct rule* const*)&table->init_dots_hash, TABLE_DOTS_HASH_SIZE, uchars, uchars_len, at);

	case TABLE_HASH_PREMODE:

		if(direction == FORWARD)
			return rule_match_forward((const struct rule* const*)&table->premode_chars_hash, TABLE_PREMODE_HASH_SIZE, uchars, uchars_len, at);
		else
			return rule_match_backward((const struct rule* const*)&table->premode_dots_hash, TABLE_DOTS_HASH_SIZE, uchars, uchars_len, at);

	case TABLE_HASH_POSTMODE:

		if(direction == FORWARD)
			return rule_match_forward((const struct rule* const*)&table->postmode_chars_hash, TABLE_POSTMODE_HASH_SIZE, uchars, uchars_len, at);
		else
			return rule_match_backward((const struct rule* const*)&table->postmode_dots_hash, TABLE_DOTS_HASH_SIZE, uchars, uchars_len, at);

	case TABLE_HASH_PRETRANS:

		if(direction == FORWARD)
			return rule_match_forward((const struct rule* const*)&table->pretrans_chars_hash, TABLE_PRETRANS_HASH_SIZE, uchars, uchars_len, at);
		else
			return rule_match_backward((const struct rule* const*)&table->pretrans_dots_hash, TABLE_DOTS_HASH_SIZE, uchars, uchars_len, at);

	case TABLE_HASH_TRANS:

		if(direction == FORWARD)
			return rule_match_forward((const struct rule* const*)&table->trans_chars_hash, TABLE_TRANS_HASH_SIZE, uchars, uchars_len, at);
		else
			return rule_match_backward((const struct rule* const*)&table->trans_dots_hash, TABLE_DOTS_HASH_SIZE, uchars, uchars_len, at);

	case TABLE_HASH_POSTTRANS:

		if(direction == FORWARD)
			return rule_match_forward((const struct rule* const*)&table->posttrans_chars_hash, TABLE_POSTTRANS_HASH_SIZE, uchars, uchars_len, at);
		else
			return rule_match_backward((const struct rule* const*)&table->posttrans_dots_hash, TABLE_DOTS_HASH_SIZE, uchars, uchars_len, at);

	case TABLE_HASH_FINI:

		if(direction == FORWARD)
			return rule_match_forward((const struct rule* const*)&table->fini_chars_hash, TABLE_FINI_HASH_SIZE, uchars, uchars_len, at);
		else
			return rule_match_backward((const struct rule* const*)&table->fini_dots_hash, TABLE_DOTS_HASH_SIZE, uchars, uchars_len, at);

#endif

	case TABLE_HASH_NONE:  ;
	}

	log_message(LOG_FATAL, "%s:%d  table_match_rule failed", __FILE__, __LINE__);
	ASSERT(0)
	return NULL;
}

/******************************************************************************/
