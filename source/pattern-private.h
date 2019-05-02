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
#define EXPR_DATA_IN(at, buffer)        ((unichar*)&buffer[(at) + 3])
#define EXPR_CONST_DATA_IN(at, buffer)  ((const unichar*)&buffer[(at) + 3])

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
