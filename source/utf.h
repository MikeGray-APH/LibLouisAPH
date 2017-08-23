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

#ifndef UTF_H
#define UTF_H

/******************************************************************************/

typedef unsigned short Unicode;

/******************************************************************************/

/* Returns 1 if uchars0 and uchars1 are equal, 0 otherwise.
*/
static inline int utf16_are_equal(const Unicode *uchars0, const int uchars0_len, const Unicode *uchars1, const int uchars1_len)
{
	int i;

	if(uchars0_len != uchars1_len)
		return 0;
	for(i = 0; i < uchars0_len; i++)
	if(uchars0[i] != uchars1[i])
		return 0;
	return 1;
}


/* Returns 1 if uchars and cchars are equal, 0 otherwise.
 *
 * Checks equality with casting instead of using conversion.
*/
static inline int utf16_is_equal_cchars(const Unicode *uchars, const int uchars_len, const char *cchars, const int cchars_len)
{
	int i;

	if(uchars_len != cchars_len)
		return 0;
	for(i = 0; i < cchars_len; i++)
	if(uchars[i] != (Unicode)cchars[i])
		return 0;
	return 1;
}


/* Copies len characters of src into dst.  Ensures that dst is NULL terminated.
 * Does not stop processing on NULL character.  Assumes that both dst and src
 * have at least len characters.
*/
static inline void utf16_copy(Unicode *dst, const Unicode *src, const int len)
{
	int i;

	for(i = 0; i < len; i++)
		dst[i] = src[i];
	dst[len - 1] = 0;
}


/* Returns 1 is uchar is a Unicode space character, otherwise 0.
*/
static inline int is_space(const Unicode uchar)
{
	switch(uchar)
	{
	case u' ':
	case u'\t':
	case u'\n':
	case u'\r':
	case u'\u00a0':
	case u'\u2000':
	case u'\u2001':
	case u'\u2002':
	case u'\u2003':
	case u'\u2004':
	case u'\u2005':
	case u'\u2006':
	case u'\u2007':
	case u'\u2008':
	case u'\u2009':
	case u'\u200a':
	case u'\u200b':

		return 1;
	}

	return 0;
}

/******************************************************************************/

#endif /*   UTF_H   */
