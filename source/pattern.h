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

#ifndef PATTERN_H
#define PATTERN_H

/* When defined, all pattern matching operations will be outputted to stdout.
*/
//#define PATTERN_OUTPUT_TRACE

struct translate;

#include "type.h"
#include "utf.h"

/******************************************************************************/

struct subpattern
{
	struct subpattern *nxt;
	Unicode *tag, *expr_data, *src_data;
	int tag_len, expr_len, src_len, processing;
};

/******************************************************************************/

/* Memory management functions for struct subpattern.
*/

struct subpattern* subpattern_allocate(void) ATTRIBUTE_FUNCTION_MALLOC;
void subpattern_free(struct subpattern *subpattern);


/* Compiles pattern from input and stores the result in expr_data.
 *
 * Returns length of compiled pattern.
*/
int pattern_compile(
	Unicode *expr_data,
	const int expr_len,
	const Unicode *input,
	const int input_len,
	const char *attrs_chars,
	struct subpattern *subpatterns);


/* Reverses compiled pattern in expr_data.
*/
void pattern_reverse(Unicode *expr_data);


/* Returns 1 if input matches the pattern stored in expr_data, 0 otherwise.
*/
int pattern_check(
	const struct translate *translate,
	const Unicode *input,
	const int input_start,
	const int input_minmax,
	const int input_dir,
	const Unicode *expr_data,
	const char *attrs_chars_,
	struct subpattern *subpatterns);

/******************************************************************************/

#endif /*   PATTERN_H   */
