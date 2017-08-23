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
