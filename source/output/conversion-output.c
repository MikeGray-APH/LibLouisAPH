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

#include <stdlib.h>
#include <stdio.h>

#include "utf-output.h"
#include "conversion.h"
#include "conversion-output.h"

/******************************************************************************/

#if 1
void conversion_output(FILE *output, const struct conversion const*conversion)
{
	Unicode uchar, cell;
	int x, y;

	if(!conversion)
		return;

	fprintf(output, "%s\n", conversion->file_name);

	fputs("unknown:  ", output);
	utf16le_output_char_escape(output, conversion->unknown);
	fputs("\n", output);

	fputs("\n", output);

	cell = 0x2800;
	for(y = 0; y < 16; y++)
	{
		for(x = 0; x < 16; x++)
		{
			uchar = conversion->converts[(y * 16) + x];
			if(uchar != cell)
				utf16le_output_char(output, uchar);
			else
				fputs(" ", output);
			utf16le_output_char(output, cell);
			fputs(" ", output);
			cell++;
		}
		fputs("\n", output);
	}

	fflush(output);
}
#else
void conversion_output(FILE *output, const struct conversion const*conversion)
{
	int x, y;

	if(!conversion)
		return;

	fprintf(output, "%s\n", conversion->file_name);

	utf16le_output_char_escape(output, conversion->unknown);
	fputs("\n", output);

	for(y = 0; y < 16; y++)
	{
		for(x = 0; x < 16; x++)
			utf16le_output_char(output, conversion->converts[(y * 16) + x]);
		fputs("\n", output);
	}

	fflush(output);
}
#endif

/******************************************************************************/
