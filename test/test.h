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

#ifndef TEST_H
#define TEST_H

#include <stdio.h>

#include "table.h"
#include "conversion.h"

/******************************************************************************/

/* If direction is FORWARD or BACKWARD, translates chars using tables and
 * conversion (which may be NULL), then compares the translation to dots.
 * If direction is BOTH, chars is forward translated, then compare it to dots,
 * then the translation is back translated and that result is compared to chars.
 * If cursor_chars is greater than zero and direction is BOTH, then the cursor
 * at cursor_chars is checked with the cursor after the translation, and vice
 * versa.
 *
 * Returns 1 if everything matched, 0 otherwise.
*/
int test_expect_cursor(
	FILE *output,
	const struct table *const*tables,
	const int table_cnt,
	const struct conversion *conversion,
	const enum rule_direction direction,
	const Unicode *chars,
	const int chars_len,
	const Unicode *dots,
	const int dots_len,
	const int cursor_chars,
	const int cursor_dots);


/* If direction is FORWARD or BACKWARD, translates chars using tables and
 * conversion (which may be NULL), then compares the translation to dots.  Also
 * compares the resulting mappings with chars_to_dots and dots_to_chars.
 * If direction is BOTH, first forward translation is checked, then backward
 * translation is checked with the chars and dots swapped.
 *
 * Returns 1 if everything matched, 0 otherwise.
*/
int test_expect_mapping(
	FILE *output,
	const struct table *const*tables,
	const int table_cnt,
	const struct conversion *conversion,
	const enum rule_direction direction,
	const Unicode *chars,
	const int chars_len,
	const Unicode *dots,
	const int dots_len,
	const int *chars_to_dots,
	const int *dots_to_chars);


/* Reads lines from file file_name, forward translates them using tables and
 * conversion (which may be NULL) and then back translates that result.
 * Compares the final result to the original line.
 *
 * Returns 1 if all lines matched their final results, 0 otherwise.
*/
int test_back_from_file(
	FILE *output,
	const char *file_name,
	const struct table *table,
	const struct conversion *conversion,
	const int output_pass_fail);


/* Reads input and result from the lines from file file_name.  Translates input
 * and compares that to result.  If do_back is set, backward translates the
 * result and compares it to the input, with some ambiguity.
 *
 * Returns 1 if all input's translations matched their results, and if do_back
 * was set, the result's backward translations matched back to their original
 * input, 0 otherwise.
*/
int test_expect_from_file(
	FILE *output,
	const char *file_name,
	const struct table *table,
	const struct conversion *conversion,
	const int output_pass_fail,
	const int do_back);

/******************************************************************************/

/* Convenience function for test_expect_cursor
*/
static inline int test_expect(
	FILE *output,
	const struct table *const*tables,
	const int table_cnt,
	const struct conversion *conversion,
	const enum rule_direction direction,
	const Unicode *chars,
	const int chars_len,
	const Unicode *dots,
	const int dots_len)
{
	return test_expect_cursor(output, tables, table_cnt, conversion, direction, chars, chars_len, dots, dots_len, -1, -1);
}

/******************************************************************************/

#endif /*   TEST_H  */
