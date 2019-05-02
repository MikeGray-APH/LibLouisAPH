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

#ifndef TABLE_H
#define TABLE_H

/* When defined, allocates memory for a hash type only when it is needed.
*/
#define TABLE_ALLOCATE_HASHES

#include "type.h"
#include "utf.h"
#include "pattern.h"

/******************************************************************************/

#define UNICHAR_JOIN_MAX  3

struct character
{
	struct character *nxt, *joins[UNICHAR_JOIN_MAX];
	unichar uchar;
	unsigned int attrs;
};


/* If a filter's name is NULL, then it was only associated with one rule and
 * not stored in the rule's table.
*/
struct filter
{
	struct filter *nxt;
	unichar *before, *after;
	int before_len, after_len;
	unichar *name;
	int name_len;

};

/*   small enough to not bother allocating   */
#define INDICATOR_MAX 7

enum mode_type
{
	FAIL,
	NONE,
	BEGIN,
	END,
	WORD,
	TERM,
	SYMBOL,
};

struct mode
{
	struct mode *nxt;
	int id;
	unichar begin[INDICATOR_MAX];
	unichar end[INDICATOR_MAX];
	unichar word[INDICATOR_MAX];
	unichar term[INDICATOR_MAX];
	unichar symbol[INDICATOR_MAX];
	int begin_len, end_len, word_len, term_len, symbol_len, passage_len;
	unichar *name;
	int name_len;
};


#define RULE_CHARS_MAX  23
#define RULE_DOTS_MAX   23

enum rule_direction
{
	FORWARD  = +1,
	BOTH     =  0,
	BACKWARD = -1,
};

struct rule
{
	unsigned int attrs;
	enum rule_direction direction;
	struct rule *chars_nxt, *dots_nxt;
	unichar chars[RULE_CHARS_MAX], dots[RULE_DOTS_MAX];
	int chars_len, dots_len;
	struct filter *filter_forward, *filter_backward;
};

#define TABLE_MARKER_USER      (u'\uf001')
#define TABLE_MARKER_BEGIN     (u'\uf002')
#define TABLE_MARKER_END       (u'\uf003')
#define TABLE_MARKER_MODIFIER  (u'\uf004')
#define TABLE_MARKER_HARD      (u'\uf005')
#define TABLE_MARKER_SOFT      (u'\uf006')
#define TABLE_MARKER_INTERNAL  (u'\uf007')

#define TABLE_NUMERIC_MAX 16

#ifdef DEBUG
#define TABLE_UNICHAR_HASH_SIZE    0x10
#define TABLE_INIT_HASH_SIZE       0x100
#define TABLE_PREMODE_HASH_SIZE    0x100
#define TABLE_POSTMODE_HASH_SIZE   0x100
#define TABLE_PRETRANS_HASH_SIZE   0x100
#define TABLE_POSTTRANS_HASH_SIZE  0x100
#define TABLE_TRANS_HASH_SIZE      0x100
#define TABLE_FINI_HASH_SIZE       0x100
#define TABLE_DOTS_HASH_SIZE       0x100
#else
#define TABLE_UNICHAR_HASH_SIZE    0x100
#define TABLE_INIT_HASH_SIZE       0x1000
#define TABLE_PREMODE_HASH_SIZE    0x1000
#define TABLE_POSTMODE_HASH_SIZE   0x1000
#define TABLE_PRETRANS_HASH_SIZE   0x1000
#define TABLE_TRANS_HASH_SIZE      0x1000
#define TABLE_POSTTRANS_HASH_SIZE  0x1000
#define TABLE_FINI_HASH_SIZE       0x1000
#define TABLE_DOTS_HASH_SIZE       0x100
#endif

enum table_process_type
{
	PROCESS_GENERIC = 0,
	PROCESS_NEMETH_UEB,
};

enum table_hash_type
{
	TABLE_HASH_NONE = 0,
	TABLE_HASH_INIT,
	TABLE_HASH_PREMODE,
	TABLE_HASH_POSTMODE,
	TABLE_HASH_PRETRANS,
	TABLE_HASH_TRANS,
	TABLE_HASH_POSTTRANS,
	TABLE_HASH_FINI,
};

struct table
{
	struct table *nxt, *depends;
	char *file_name;

	enum table_process_type process;

	struct filter *filters;
	struct subpattern *subpatterns;
	char attrs_chars[32];

	struct mode nocontract, capital, numeric, *emphases;
	int nocontract_set, capital_set, numeric_set, emphases_cnt;

	unichar marker_user, marker_begin, marker_end, marker_modifier, marker_hard, marker_soft, marker_internal;

	struct character *character_hash[TABLE_UNICHAR_HASH_SIZE];

#ifdef TABLE_ALLOCATE_HASHES
	struct rule **init_chars_hash, **init_dots_hash;
	int init_chars_hash_cnt, init_dots_hash_cnt;

	struct rule **premode_chars_hash, **premode_dots_hash;
	int premode_chars_hash_cnt, premode_dots_hash_cnt;

	struct rule **postmode_chars_hash, **postmode_dots_hash;
	int postmode_chars_hash_cnt, postmode_dots_hash_cnt;

	struct rule **pretrans_chars_hash, **pretrans_dots_hash;
	int pretrans_chars_hash_cnt, pretrans_dots_hash_cnt;

	struct rule **trans_chars_hash, **trans_dots_hash;
	int trans_chars_hash_cnt, trans_dots_hash_cnt;

	struct rule **posttrans_chars_hash, **posttrans_dots_hash;
	int posttrans_chars_hash_cnt, posttrans_dots_hash_cnt;

	struct rule **fini_chars_hash, **fini_dots_hash;
	int fini_chars_hash_cnt, fini_dots_hash_cnt;
#else
	struct rule *init_chars_hash[TABLE_INIT_HASH_SIZE], *init_dots_hash[TABLE_DOTS_HASH_SIZE];
	int init_chars_hash_cnt, init_dots_hash_cnt;

	struct rule *premode_chars_hash[TABLE_PREMODE_HASH_SIZE], *premode_dots_hash[TABLE_DOTS_HASH_SIZE];
	int premode_chars_hash_cnt, premode_dots_hash_cnt;

	struct rule *postmode_chars_hash[TABLE_POSTMODE_HASH_SIZE], *postmode_dots_hash[TABLE_DOTS_HASH_SIZE];
	int postmode_chars_hash_cnt, postmode_dots_hash_cnt;

	struct rule *pretrans_chars_hash[TABLE_PRETRANS_HASH_SIZE], *pretrans_dots_hash[TABLE_DOTS_HASH_SIZE];
	int pretrans_chars_hash_cnt, pretrans_dots_hash_cnt;

	struct rule *trans_chars_hash[TABLE_TRANS_HASH_SIZE], *trans_dots_hash[TABLE_DOTS_HASH_SIZE];
	int trans_chars_hash_cnt, trans_dots_hash_cnt;

	struct rule *posttrans_chars_hash[TABLE_POSTTRANS_HASH_SIZE], *posttrans_dots_hash[TABLE_DOTS_HASH_SIZE];
	int posttrans_chars_hash_cnt, posttrans_dots_hash_cnt;

	struct rule *fini_chars_hash[TABLE_FINI_HASH_SIZE], *fini_dots_hash[TABLE_DOTS_HASH_SIZE];
	int fini_chars_hash_cnt, fini_dots_hash_cnt;
#endif

};

/******************************************************************************/

/* Memory mananagment functions.
*/

int  table_init(struct table *table);
void table_fini(struct table *table);
struct table* table_allocate(void) ATTRIBUTE_FUNCTION_MALLOC;
void table_free(struct table *table);

struct character* character_allocate(void) ATTRIBUTE_FUNCTION_MALLOC;
void character_free(struct character *character);

struct mode* mode_allocate(void) ATTRIBUTE_FUNCTION_MALLOC;
void mode_free(struct mode *mode);

struct filter* filter_allocate(void) ATTRIBUTE_FUNCTION_MALLOC;
void filter_free(struct filter *filter);

struct rule* rule_allocate(void) ATTRIBUTE_FUNCTION_MALLOC;
void rule_free(struct rule *rule);
void rule_free_backward(struct rule *rule);


/* Scans at most uchars_len characters in uchars and converts escape marker
 * characters in uchars that correspond to markers.
 *
 * Returns the adjusted length of uchars.
*/
int table_convert_escape_markers(const struct table *table, unichar *uchars, const int uchars_len);


/* Returns new rule that was added depending on hash_type, direction, chars,
 * dots, weights, and filters, or NULL if an error occurred.
 *
 * Both filter_forward or filter_backward may be NULL to indicate no filtering.
 * Both chars_weight and dots_weight must be either 0 or 1.
*/
struct rule* table_add_rule(
	struct table *table,
	const enum table_hash_type hash_type,
	const enum rule_direction direction,
	struct filter *filter_forward,
	struct filter *filter_backward,
	const unichar *chars,
	const int chars_len,
	const unichar *dots,
	const int dots_len,
	const int chars_weight,
	const int dots_weight);


/* Finds rule from hash_type whose chars or dots, depending on direction,
 * matches uchars.  The search will start after at, or from the beginning if at
 * is NULL.
 *
 * Returns the matching rule, or NULL is no rule matched.
*/
const struct rule* table_match_rule(
	const struct table *table,
	const enum table_hash_type hash_type,
	const enum rule_direction direction,
	const unichar *uchars,
	const int uchars_len,
	const struct rule *at);


/* Returns character that corresponds to uchar, or NULL if uchar does not
 * correspond to character.
*/
struct character* table_find_character(const struct table *table, const unichar uchar);


/* Returns character that corresponds to uchar, adding a new character if there is
 * not one corresponding to uchar.
*/
struct character* table_find_or_add_character(struct table *table, const unichar uchar);


/* Returns table that was loaded and compiled from file file_name, or NULL on
 * error.  Defined in compile.c.
*/
struct table* table_compile_from_file(const char *file_name);

/******************************************************************************/

/* Returns attributes of uchar.
*/
static inline unsigned int table_get_character_attributes(const struct table *table, const unichar uchar)
{
	struct character *character;

	character = table_find_character(table, uchar);
	if(character)
		return character->attrs;
	else
		return 0;
}

/******************************************************************************/

#endif /*   TABLE_H   */
