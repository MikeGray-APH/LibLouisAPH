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

#include "type.h"
#include "utf-convert.h"
#include "utf-output.h"

/******************************************************************************/

void utf16_output(FILE *output, const unichar *uchars, const int uchars_len)
{
	char *cchars;
	int cchars_len;

	if(uchars_len <= 0 || !uchars)
		return;

	cchars_len = uchars_len * 8;
	cchars = MALLOC(cchars_len + 1);

	utf16_convert_to_utf8(cchars, (cchars_len + 1), uchars, uchars_len, NULL);
	fprintf(output, "%s", cchars);
	fflush(output);

	FREE(cchars);
}

void utf16_output_char(FILE *output, const unichar uchar)
{
	char cchars[16];
	unichar uchars[2];

	switch(uchar)
	{
	case 0xa0:
	case u' ':
	case u'\n':
	case u'\r':
	case u'\t':  fputs(" ", output);  break;
	default:

		uchars[0] = uchar;
		uchars[1] = 0;
		utf16_convert_to_utf8(cchars, 16, uchars, 2, NULL);
		fprintf(output, "%s", cchars);
	}

	fflush(output);
}

void utf16_output_char_escape(FILE *output, const unichar uchar)
{
	char cchars[16];
	unichar uchars[2];

	switch(uchar)
	{
	case 0xa0:   fputs("\\S", output);  break;
	case u' ':   fputs("\\s", output);  break;
	case u'\n':  fputs("\\n", output);  break;
	case u'\r':  fputs("\\r", output);  break;
	case u'\t':  fputs("\\t", output);  break;
	default:

		uchars[0] = uchar;
		uchars[1] = 0;
		utf16_convert_to_utf8(cchars, 16, uchars, 2, NULL);
		fprintf(output, "%s", cchars);
	}

	fflush(output);
}

/******************************************************************************/
