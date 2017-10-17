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

#ifndef CONVERSION_H
#define CONVERSION_H

#include "type.h"
#include "utf.h"

/******************************************************************************/

struct conversion
{
	struct conversion *nxt;
	char *file_name;
	Unicode converts[256], unknown;
};

/******************************************************************************/

/* Memory management functions for struct conversion.
*/

void conversion_init(struct conversion *conversion);
void conversion_fini(struct conversion *conversion);
struct conversion* conversion_allocate(void) ATTRIBUTE_FUNCTION_MALLOC;
void conversion_free(struct conversion *conversion);


/* Sets cell to be converted to uchar.
 *
 * Returns 1 if successfully added, 0 if an error occurred.
*/
int conversion_set_cell(struct conversion *conversion, const Unicode cell, const Unicode uchar);


/* Sets any unknown characters to be converted to uchar.
 *
 * Returns 1 if successfully added, 0 if an error occurred.
*/
int conversion_set_unknown(struct conversion *conversion, const Unicode uchar);


/* Converts uchars from text to braille cells.
*/
void conversion_convert_to(Unicode *dots, const int dots_len, const struct conversion *conversion);


/* Converts cells from braille cells to text.
*/
void conversion_convert_from(Unicode *uchars, const int uchars_len, const struct conversion *conversion);


/* Returns conversion that was loaded and compiled from file file_name, or NULL
 * if an error occurred.  Defined in compile.c.
*/
struct conversion* conversion_compile_from_file(const char *file_name);

/******************************************************************************/

#endif /*   CONVERSION_H   */
