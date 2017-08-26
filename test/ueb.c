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

	try_cnt++;  pass_cnt += test_back_from_file(output,   "test/ueb/ueb-back.txt", table, NULL, 0);
	try_cnt++;  pass_cnt += test_expect_from_file(output, "test/ueb/ueb-expect.txt", table, NULL, 0, 1);

	try_cnt++;  pass_cnt += test_expect_from_file(output, "test/ueb/ueb-02-stand_alone.txt", table, conversion, 0, 1);
	try_cnt++;  pass_cnt += test_expect_from_file(output, "test/ueb/ueb-03-symbols.txt", table, conversion, 0, 1);
	try_cnt++;  pass_cnt += test_expect_from_file(output, "test/ueb/ueb-05-grade_1_mode.txt", table, conversion, 0, 1);
	try_cnt++;  pass_cnt += test_expect_from_file(output, "test/ueb/ueb-06-numeric_mode.txt", table, conversion, 0, 1);
	try_cnt++;  pass_cnt += test_expect_from_file(output, "test/ueb/ueb-08-capitalization.txt", table, conversion, 0, 1);
	try_cnt++;  pass_cnt += test_expect_from_file(output, "test/ueb/ueb-09-typeforms.txt", table, conversion, 0, 1);
	try_cnt++;  pass_cnt += test_expect_from_file(output, "test/ueb/ueb-10-07-contractions.txt", table, conversion, 0, 1);
//	try_cnt++;  pass_cnt += test_expect_from_file(output, "test/ueb/ueb-10-13-contractions.txt", table, conversion, 0, 1);

	try_cnt++;  pass_cnt += test_expect_from_file(output, "test/ueb/ueb-dictionary.txt", table, NULL, 0, 1);
	try_cnt++;  pass_cnt += test_back_from_file(output,   "test/data/english-words.txt", table, NULL, 0);

//	try_cnt++;  pass_cnt += test_expect_from_file(output, "test/ueb/ueb-fail-expect.txt", table, conversion, 1, 1);
//	try_cnt++;  pass_cnt += test_back_from_file(output,   "test/ueb/ueb-fail-back.txt", table, NULL, 1);

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
