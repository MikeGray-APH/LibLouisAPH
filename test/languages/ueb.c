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

#include "utf.h"
#include "test.h"

/******************************************************************************/

int test_ueb(FILE *output)
{
	struct table *table;
	struct conversion *conversion;
	int pass_cnt, try_cnt;

	if(!output)
	{
		output = fopen("build/test/output-ueb.txt", "w");
		if(!output)
			output = stdout;
	}

	fputs("testing UEB\n\n", output);
	if(output != stdout)
		puts("testing UEB");

	pass_cnt =
	try_cnt = 0;

	table = table_compile_from_file("tables/english-ueb-grade2.rst");
	if(!table)
	{
		fprintf(output, "ERROR:  unable to open tables/english-ueb-grade2.rst\n\n");
		return 1;
	}
	conversion = conversion_compile_from_file("tables/ascii.cvt");
	if(!conversion)
	{
		fprintf(output, "ERROR:  unable to open tables/ascii.cvt\n\n");
		return 1;
	}

	try_cnt++;  pass_cnt += test_back_from_file(output,   "test/languages/ueb/ueb-back.txt", table, NULL, 0);
	try_cnt++;  pass_cnt += test_expect_from_file(output, "test/languages/ueb/ueb-expect.txt", table, NULL, 0, 1);

	try_cnt++;  pass_cnt += test_expect_from_file(output, "test/languages/ueb/ueb-02-stand_alone.txt", table, conversion, 0, 1);
	try_cnt++;  pass_cnt += test_expect_from_file(output, "test/languages/ueb/ueb-03-symbols.txt", table, conversion, 0, 1);
	try_cnt++;  pass_cnt += test_expect_from_file(output, "test/languages/ueb/ueb-05-grade_1_mode.txt", table, conversion, 0, 1);
	try_cnt++;  pass_cnt += test_expect_from_file(output, "test/languages/ueb/ueb-06-numeric_mode.txt", table, conversion, 0, 1);
	try_cnt++;  pass_cnt += test_expect_from_file(output, "test/languages/ueb/ueb-08-capitalization.txt", table, conversion, 0, 1);
	try_cnt++;  pass_cnt += test_expect_from_file(output, "test/languages/ueb/ueb-09-typeforms.txt", table, conversion, 0, 1);
	try_cnt++;  pass_cnt += test_expect_from_file(output, "test/languages/ueb/ueb-10-07-contractions.txt", table, conversion, 0, 1);
//	try_cnt++;  pass_cnt += test_expect_from_file(output, "test/languages/ueb/ueb-10-13-contractions.txt", table, conversion, 0, 1);

	try_cnt++;  pass_cnt += test_expect_from_file(output, "test/languages/ueb/ueb-dictionary.txt", table, NULL, 0, 1);
	try_cnt++;  pass_cnt += test_back_from_file(output,   "test/data/english-words.txt", table, NULL, 0);

//	try_cnt++;  pass_cnt += test_expect_from_file(output, "test/languages/ueb/ueb-fail-expect.txt", table, conversion, 1, 1);
//	try_cnt++;  pass_cnt += test_back_from_file(output,   "test/languages/ueb/ueb-fail-back.txt", table, NULL, 1);

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
