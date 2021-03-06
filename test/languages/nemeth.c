/*

   Copyright 2018 American Printing House for the Blind Inc.

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

#include "utf.h"
#include "test.h"

/******************************************************************************/

int test_nemeth(FILE *output)
{
	struct table *table;
	struct conversion *conversion;
	int pass_cnt, try_cnt;

	if(!output)
	{
		output = fopen("build/test/output-nemeth.txt", "w");
		if(!output)
			output = stdout;
	}

	fputs("testing nemeth\n\n", output);
	if(output != stdout)
		puts("testing nemeth");

	pass_cnt =
	try_cnt = 0;

	table = table_compile_from_file("tables/nemeth-ueb.rst");
	if(!table)
	{
		fprintf(output, "ERROR:  unable to open tables/nemeth-ueb.rst\n\n");
		return 1;
	}
	conversion = conversion_compile_from_file("tables/ascii.cvt");
	if(!conversion)
	{
		fprintf(output, "ERROR:  unable to open tables/ascii.cvt\n\n");
		return 1;
	}

	try_cnt++;  pass_cnt += test_expect_from_file(output, "test/languages/nemeth/nemeth-expect.txt", table, NULL, 0, 0);
	try_cnt++;  pass_cnt += test_expect_from_file(output, "test/languages/nemeth/nemeth-lesson02.txt", table, NULL, 0, 0);
	try_cnt++;  pass_cnt += test_expect_from_file(output, "test/languages/nemeth/nemeth-lesson06.txt", table, NULL, 0, 0);
	try_cnt++;  pass_cnt += test_expect_from_file(output, "test/languages/nemeth/nemeth-lesson07.txt", table, NULL, 0, 0);

	if(table)
		table_free(table);
	if(conversion)
		conversion_free(conversion);

	if(output != stdout)
	{
		puts("");
		fclose(output);
	}

	return try_cnt - pass_cnt;
}

/******************************************************************************/
