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
	unichar *tag, *expr_data, *src_data;
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
	unichar *expr_data,
	const int expr_len,
	const unichar *input,
	const int input_len,
	const char *attrs_chars,
	struct subpattern *subpatterns);


/* Reverses compiled pattern in expr_data.
*/
void pattern_reverse(unichar *expr_data);


/* Returns 1 if input matches the pattern stored in expr_data, 0 otherwise.
*/
int pattern_check(
	const struct translate *translate,
	const unichar *input,
	const int input_start,
	const int input_minmax,
	const int input_dir,
	const unichar *expr_data,
	const char *attrs_chars_,
	struct subpattern *subpatterns);

/******************************************************************************/

#endif /*   PATTERN_H   */
