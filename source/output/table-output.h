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

#ifndef TABLE_OUTPUT_H
#define TABLE_OUTPUT_H

#include <stdio.h>

#include "table.h"

/******************************************************************************/

void table_output(FILE *output, const struct table *table);

/******************************************************************************/

static inline void table_convert_markers(const struct table *table, Unicode *uchars, const int uchars_len)
{
	int i;

	if(table)
	{
		for(i = 0; i < uchars_len; i++)
		     if(uchars[i] == table->marker_user)
			uchars[i] = u'⟘';
		else if(uchars[i] == table->marker_begin)
			uchars[i] = u'⟪';
		else if(uchars[i] == table->marker_end)
			uchars[i] = u'⟫';
		else if(uchars[i] == table->marker_modifier)
			uchars[i] = u'★';
		else if(uchars[i] == table->marker_hard)
			uchars[i] = u'⟠';
		else if(uchars[i] == table->marker_soft)
			uchars[i] = u'⟊';
		else if(uchars[i] == table->marker_internal)
			uchars[i] = u'☣';
	}
	else for(i = 0; i < uchars_len; i++)
	switch(uchars[i])
	{
	case TABLE_MARKER_USER:      uchars[i] = u'⟘';  break;
	case TABLE_MARKER_BEGIN:     uchars[i] = u'⟪';  break;
	case TABLE_MARKER_END:       uchars[i] = u'⟫';  break;
	case TABLE_MARKER_MODIFIER:  uchars[i] = u'★';  break;
	case TABLE_MARKER_HARD:      uchars[i] = u'⟠';  break;
	case TABLE_MARKER_SOFT:      uchars[i] = u'⟊';  break;
	case TABLE_MARKER_INTERNAL:  uchars[i] = u'☣';  break;
	//case :                     uchars[i] = u'⟨';  break;
	//case :                     uchars[i] = u'⟩';  break;
	//case :                     uchars[i] = u'☓';  break;
	}
}

/******************************************************************************/

#endif /*   TABLE_OUTPUT_H   */
