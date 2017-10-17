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
