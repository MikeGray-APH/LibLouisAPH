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

#ifndef UTF_H
#define UTF_H

/******************************************************************************/

typedef unsigned short unichar;

/******************************************************************************/

/* Returns 1 if uchars0 and uchars1 are equal, 0 otherwise.
*/
static inline int utf16_are_equal(const unichar *uchars0, const int uchars0_len, const unichar *uchars1, const int uchars1_len)
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
static inline int utf16_is_equal_cchars(const unichar *uchars, const int uchars_len, const char *cchars, const int cchars_len)
{
	int i;

	if(uchars_len != cchars_len)
		return 0;
	for(i = 0; i < cchars_len; i++)
	if(uchars[i] != (unichar)cchars[i])
		return 0;
	return 1;
}


/* Copies len characters of src into dst.  Ensures that dst is NULL terminated.
 * Does not stop processing on NULL character.  Assumes that both dst and src
 * have at least len characters.
*/
static inline void utf16_copy(unichar *dst, const unichar *src, const int len)
{
	int i;

	for(i = 0; i < len; i++)
		dst[i] = src[i];
	dst[len - 1] = 0;
}


/* Returns 1 is uchar is a unichar space character, otherwise 0.
*/
static inline int is_space(const unichar uchar)
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
