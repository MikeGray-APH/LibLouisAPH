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
