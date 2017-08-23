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

#ifndef UTF_OUTPUT_H
#define UTF_OUTPUT_H

#include <stdio.h>

#include "utf.h"

/******************************************************************************/

void utf16le_output(FILE *output, const Unicode *uchars, const int uchars_len);
void utf16le_output_char(FILE *output, const Unicode uchar);
void utf16le_output_char_escape(FILE *output, const Unicode uchar);

/******************************************************************************/

#endif /*   UTF_OUTPUT_H   */
