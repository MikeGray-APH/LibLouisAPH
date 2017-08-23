/*

LibLouisAPH Braille Translation and Back-Translation Library

Copyright (C) 2017 Mike Gray, American Printing House for the Blind, Inc.

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

#ifndef PATTERN_PRIVATE_H
#define PATTERN_PRIVATE_H

/******************************************************************************/

enum pattern_type
{
	PTN_ERROR,

	PTN_START,
	PTN_GROUP,
	PTN_NOT,

	PTN_ONE_MORE,
	PTN_ZERO_MORE,
	PTN_OPTIONAL,

	PTN_ALTERNATE,

	PTN_ANY,
	PTN_ATTRIBUTES,
	PTN_CHARS,
	PTN_SUBPATTERN,
	PTN_END_OF_INPUT,

	PTN_END = 0xffff,
};

#define EXPR_TYPE_IN(at, buffer)        (buffer[(at) + 0])
#define EXPR_PRV_IN(at, buffer)         (buffer[(at) + 1])
#define EXPR_NXT_IN(at, buffer)         (buffer[(at) + 2])
#define EXPR_DATA_0_IN(at, buffer)      (buffer[(at) + 3])
#define EXPR_DATA_1_IN(at, buffer)      (buffer[(at) + 4])
#define EXPR_DATA_2_IN(at, buffer)      (buffer[(at) + 5])
#define EXPR_DATA_IN(at, buffer)        ((Unicode*)&buffer[(at) + 3])
#define EXPR_CONST_DATA_IN(at, buffer)  ((const Unicode*)&buffer[(at) + 3])

#define EXPR_TYPE(at)        EXPR_TYPE_IN((at), expr_data)
#define EXPR_PRV(at)         EXPR_PRV_IN((at), expr_data)
#define EXPR_NXT(at)         EXPR_NXT_IN((at), expr_data)
#define EXPR_DATA_0(at)      EXPR_DATA_0_IN((at), expr_data)
#define EXPR_DATA_1(at)      EXPR_DATA_1_IN((at), expr_data)
#define EXPR_DATA_2(at)      EXPR_DATA_2_IN((at), expr_data)
#define EXPR_DATA(at)        EXPR_DATA_IN((at), expr_data)
#define EXPR_CONST_DATA(at)  EXPR_CONST_DATA_IN((at), expr_data)

/******************************************************************************/

/* Both pattern and pattern-output need these, but let them each keep their own
 * local copy.
*/

static char attrs_chars[32] = "0123456789ABCDEFGHIJKLMNOPQRSTUV";

static void set_attrs_chars(const char *cchars)
{
	int len, i;

	if(cchars)
	{
		len = strlen(cchars);
		if(len > 32)
			len = 32;
		for(i = 0; i < len; i++)
			attrs_chars[i] = cchars[i];
	}
}

/******************************************************************************/

#endif /*   PATTERN_PRIVATE_H   */
