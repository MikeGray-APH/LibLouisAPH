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

#ifndef TABLE_OUTPUT_H
#define TABLE_OUTPUT_H

#include <stdio.h>

#include "table.h"

/******************************************************************************/

void table_output(FILE *output, const struct table *table);

/******************************************************************************/

static inline void table_convert_markers(const struct table *table, unichar *uchars, const int uchars_len)
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
