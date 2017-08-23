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
#include <string.h>

#include "conversion.h"
#include "log.h"

/******************************************************************************/

void conversion_init(struct conversion *conversion)
{
	int i;

	memset(conversion, 0, sizeof(struct conversion));

	/*   fill with default cells   */
	for(i = 0; i < 256; i++)
		conversion->converts[i] = 0x2800 + i;
}

void conversion_fini(struct conversion *conversion)
{
	if(!conversion)
		return;

	if(conversion->file_name)
		FREE(conversion->file_name);
}

ATTRIBUTE_FUNCTION_MALLOC
struct conversion* conversion_allocate(void)
{
	struct conversion *conversion;

	conversion = MALLOC(sizeof(struct conversion));
	LOG_ALLOCATE_FAIL_RETURN_NULL(conversion)
	conversion_init(conversion);

	return conversion;
}

void conversion_free(struct conversion *conversion)
{
	if(!conversion)
		return;

	conversion_free(conversion->nxt);
	conversion_fini(conversion);
	FREE(conversion);
}

int conversion_set_cell(struct conversion *conversion, const Unicode cell, const Unicode uchar)
{
	if(cell >= 0x2800 && cell <= 0x28ff)
		conversion->converts[cell & 0xff] = uchar;
	else
		return 0;

	return 1;
}

int conversion_set_unknown(struct conversion *conversion, const Unicode uchar)
{
	conversion->unknown = uchar;
	return 1;
}

void conversion_convert_to(Unicode *dots, const int dots_len, const struct conversion *conversion)
{
	int i;

	if(!conversion)
		return;

	for(i = 0; i < dots_len; i++)
	if(dots[i] >= 0x2800 && dots[i] <= 0x28ff)
		dots[i] = conversion->converts[dots[i] & 0xff];
	else
		dots[i] = conversion->unknown;
}

static Unicode convert_uchar_from(const struct conversion *conversion, const Unicode uchar)
{
	int i;

	for(i = 0; i < 0x100; i++)
	if(uchar == conversion->converts[i])
		return i + 0x2800;

	return conversion->unknown;
}

void conversion_convert_from(Unicode *uchars, const int uchars_len, const struct conversion *conversion)
{
	int i;

	if(!conversion)
		return;

	for(i = 0; i < uchars_len; i++)
		uchars[i] = convert_uchar_from(conversion, uchars[i]);
}

/******************************************************************************/
