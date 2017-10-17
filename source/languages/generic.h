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

#ifndef GENERIC_H
#define GENERIC_H

#include "translate.h"

/******************************************************************************/

enum CHAR_DOT_ATTRIBUTE
{
	CHAR_SPACE = BIT(0),
	CHAR_SEQUENCE_DELIMITER = BIT(1),
	CHAR_SEQUENCE_BEFORE = BIT(2),
	CHAR_SEQUENCE_AFTER = BIT(3),
	CHAR_SEQUENCE_BEFORE_NO_INDICATOR = BIT(4),
	CHAR_SEQUENCE_AFTER_NO_INDICATOR = BIT(5),

	CHAR_LETTER = BIT(6),
	CHAR_UPPER = BIT(7),
	CHAR_LOWER = BIT(8),
	CHAR_CONSONENT = BIT(9),
	CHAR_VOWEL = BIT(10),

	CHAR_NUMERIC_DIGIT = BIT(11),
	CHAR_NUMERIC_UCHAR = BIT(12),
	CHAR_NUMERIC_CONT = BIT(13),
	CHAR_NUMERIC_TERM = BIT(14),

	CHAR_LOWER_DOTS = BIT(15),
	CHAR_UPPER_DOTS = BIT(16),
	CHAR_PRIVATE = BIT(17),
};

enum RULE_ATTRIBUTE
{
	RULE_CONTRACTION = BIT(0),
};

/******************************************************************************/

/* Appends indicator, with delimiter before and after, to output.  Output map is
 * set to -1.
 *
 * Returns status of successful insertion.
*/
int generic_insert_marked(struct translate *translate, const Unicode *indicator, const int indicator_len, const Unicode delimiter);


/* Removes all occurences of pairs of internal markers and the characters
 * between them.
 *
 * Returns status of successful removal.
*/
int generic_remove_internal(struct translate *translate);


/* Removes all occurences of pairs of soft indicator markers and the characters
 * between them.
 *
 * Returns status of successful removal.
*/
int generic_remove_soft_delimiters(struct translate *translate);


/* Removes all occurences of modifier markers.
 *
 * Returns status of successful removal.
*/
int generic_remove_modifier_delimiters(struct translate *translate);


/* Removes all occurences of modifier and hard indicator markers.
 *
 * Returns status of successful removal.
*/
int generic_remove_hard_and_modifier_delimiters(struct translate *translate);


/* Scans input, finding matching rules based on hash_type and direction, and
 * applies those rules to output.
 *
 * Returns status of successful process.
*/
int generic_process(struct translate *translate, const enum table_hash_type hash_type, const enum rule_direction direction);

/******************************************************************************/

/* Convenience functions that return the joined uchar that corresponds to uchar,
 * or the uchar itself if none corresponded.
*/

static inline Unicode generic_upper_to_lower(const struct table *table, const Unicode uchar)
{
	struct unichar *unichar;

	unichar = table_find_unichar(table, uchar);
	if(!unichar)
		return uchar;
	if(!(unichar->attrs & CHAR_UPPER))
		return uchar;

	return unichar->joins[0]->uchar;
}

static inline Unicode generic_lower_to_upper(const struct table *table, const Unicode uchar)
{
	struct unichar *unichar;

	unichar = table_find_unichar(table, uchar);
	if(!unichar)
		return uchar;
	if(!(unichar->attrs & CHAR_LOWER))
		return uchar;

	return unichar->joins[0]->uchar;
}

static inline Unicode generic_digit_to_uchar(const struct table *table, const Unicode digit)
{
	struct unichar *unichar;

	unichar = table_find_unichar(table, digit);
	if(!unichar)
		return digit;
	if(!(unichar->attrs & CHAR_NUMERIC_DIGIT))
		return digit;

	return unichar->joins[1]->uchar;
}

static inline Unicode generic_uchar_to_digit(const struct table *table, const Unicode uchar)
{
	struct unichar *unichar;

	unichar = table_find_unichar(table, uchar);
	if(!unichar)
		return uchar;
	if(!(unichar->attrs & CHAR_NUMERIC_UCHAR))
		return uchar;

	return unichar->joins[1]->uchar;
}

/******************************************************************************/

#endif /*   GENERIC_H   */
