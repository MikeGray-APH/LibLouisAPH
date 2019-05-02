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

#include <stdlib.h>
#include <stdio.h>

#include "utf-output.h"
#include "conversion.h"
#include "conversion-output.h"

/******************************************************************************/

#if 1
void conversion_output(FILE *output, const struct conversion *conversion)
{
	unichar uchar, cell;
	int x, y;

	if(!conversion)
		return;

	fprintf(output, "%s\n", conversion->file_name);

	fputs("unknown:  ", output);
	utf16_output_char_escape(output, conversion->unknown);
	fputs("\n", output);

	fputs("\n", output);

	cell = 0x2800;
	for(y = 0; y < 16; y++)
	{
		for(x = 0; x < 16; x++)
		{
			uchar = conversion->converts[(y * 16) + x];
			if(uchar != cell)
				utf16_output_char(output, uchar);
			else
				fputs(" ", output);
			utf16_output_char(output, cell);
			fputs(" ", output);
			cell++;
		}
		fputs("\n", output);
	}

	fflush(output);
}
#else
void conversion_output(FILE *output, const struct conversion *conversion)
{
	int x, y;

	if(!conversion)
		return;

	fprintf(output, "%s\n", conversion->file_name);

	utf16_output_char_escape(output, conversion->unknown);
	fputs("\n", output);

	for(y = 0; y < 16; y++)
	{
		for(x = 0; x < 16; x++)
			utf16_output_char(output, conversion->converts[(y * 16) + x]);
		fputs("\n", output);
	}

	fflush(output);
}
#endif

/******************************************************************************/
