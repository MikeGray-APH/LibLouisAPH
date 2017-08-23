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

#include <stdlib.h>
#include <stdio.h>

#include "type.h"
#include "utf-convert.h"
#include "utf-output.h"

/******************************************************************************/

void utf16le_output(FILE *output, const Unicode *uchars, const int uchars_len)
{
	char *cchars;
	int cchars_len;

	if(uchars_len <= 0 || !uchars)
		return;

	cchars_len = uchars_len * 8;
	cchars = MALLOC(cchars_len);

	utf16le_convert_to_utf8(cchars, cchars_len, uchars, uchars_len);
	fprintf(output, "%s", cchars);
	fflush(output);

	FREE(cchars);
}

void utf16le_output_char(FILE *output, const Unicode uchar)
{
	char cchars[16];
	Unicode uchars[2];

	switch(uchar)
	{
	case 0xa0:
	case u' ':
	case u'\n':
	case u'\r':
	case u'\t':  fputs(" ", output);   break;
	default:

		uchars[0] = uchar;
		uchars[1] = 0;
		utf16le_convert_to_utf8(cchars, 16, uchars, 2);
		fprintf(output, "%s", cchars);
	}

	fflush(output);
}

void utf16le_output_char_escape(FILE *output, const Unicode uchar)
{
	char cchars[16];
	Unicode uchars[2];

	switch(uchar)
	{
	case 0xa0:   fputs("\\S", output);   break;
	case u' ':   fputs("\\s", output);   break;
	case u'\n':  fputs("\\n", output);   break;
	case u'\r':  fputs("\\r", output);   break;
	case u'\t':  fputs("\\t", output);   break;
	default:

		uchars[0] = uchar;
		uchars[1] = 0;
		utf16le_convert_to_utf8(cchars, 16, uchars, 2);
		fprintf(output, "%s", cchars);
	}

	fflush(output);
}

/******************************************************************************/
