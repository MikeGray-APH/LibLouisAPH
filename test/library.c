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

#include "translate.h"
#include "lookup.h"
#include "utf-convert.h"
#include "utf-output.h"
#include "log.h"
#include "test.h"

/******************************************************************************/

int test_rule_sort(FILE *output)
{
	struct table *table;
	int status;

	status = 0;

	if(output != stdout)
		printf("test_rule_sort:  ");

	fputs("test_rule_sort\n\n", output);

	table = table_compile_from_file("test/tables/rule-sort_0.rst");
	if(!table)
	{
		fputs("unable to open test/tables/rule-sort_0.rst\n", output);
		goto free_and_return;
	}

	if(!test_expect(output, (const struct table * const*)&table, 1, NULL, BOTH, u"chars", 5, u"⠒⠒", 2))
		goto free_and_return;

	table_free(table);
	table = table_compile_from_file("test/tables/rule-sort_1.rst");
	if(!table)
	{
		fputs("unable to open test/tables/rule-sort_1.rst\n", output);
		goto free_and_return;
	}

	if(!test_expect(output, (const struct table * const*)&table, 1, NULL, BOTH, u"chars", 5, u"⠗⠺", 2))
		goto free_and_return;

	table_free(table);
	table = table_compile_from_file("test/tables/rule-sort_2.rst");
	if(!table)
	{
		fputs("unable to open test/tables/rule-sort_2.rst\n", output);
		goto free_and_return;
	}

	if(!test_expect(output, (const struct table * const*)&table, 1, NULL, BOTH, u"chars", 5, u"⠒⠒", 2))
		goto free_and_return;

	status = 1;

	free_and_return:
	if(table)
		table_free(table);

	fputs("\n", output);
	fflush(output);

	if(output != stdout)
	if(status)
		puts("PASS");
	else
		puts("FAIL");

	return status;
}

int test_table_include(FILE *output)
{
	struct table *table;
	int status;

	status = 0;

	if(output != stdout)
		printf("test_table_include:  ");

	fputs("test_table_include\n\n", output);

	table = table_compile_from_file("test/tables/table-include_0.rst");
	if(!table)
	{
		fputs("unable to open test/tables/table-include_0.rst\n", output);
		goto free_and_return;
	}

	if(!test_expect(output, (const struct table * const*)&table, 1, NULL, BOTH, u"<=#=>", 5, u"⠪=#=⠕", 5))
		goto free_and_return;

	table_free(table);
	table = table_compile_from_file("test/tables/table-include_1.rst");
	if(!table)
	{
		fputs("unable to open test/tables/table-include_1.rst\n", output);
		goto free_and_return;
	}

	if(!test_expect(output, (const struct table * const*)&table, 1, NULL, BOTH, u"<=#=>", 5, u"⠪⠭#⠭⠕", 5))
		goto free_and_return;

	table_free(table);
	table = table_compile_from_file("test/tables/table-include_2.rst");
	if(!table)
	{
		fputs("unable to open test/tables/table-include_2.rst\n", output);
		goto free_and_return;
	}

	if(!test_expect(output, (const struct table * const*)&table, 1, NULL, BOTH, u"<=#=>", 5, u"⠪⠭⠿⠭⠕", 5))
		goto free_and_return;

	status = 1;

	free_and_return:
	if(table)
		table_free(table);

	fputs("\n", output);
	fflush(output);

	if(output != stdout)
	if(status)
		puts("PASS");
	else
		puts("FAIL");

	return status;
}

int test_table_override(FILE *output)
{
	struct table *tables[2];
	int status;

	status = 0;
	tables[0] =
	tables[1] = NULL;

	if(output != stdout)
		printf("test_table_override:  ");

	fputs("test_table_override\n\n", output);

	tables[0] = table_compile_from_file("test/tables/table-override_1.rst");
	if(!tables[0])
	{
		fputs("unable to open test/tables/table-override_1.rst\n", output);
		goto free_and_return;
	}

	if(!test_expect(output, (const struct table * const*)tables, 1, NULL, BOTH, u"a", 1, u"⠁", 1))
		goto free_and_return;
	if(!test_expect(output, (const struct table * const*)tables, 1, NULL, BOTH, u"abc", 3, u"⠇", 1))
		goto free_and_return;

	tables[1] = tables[0];
	tables[0] = table_compile_from_file("test/tables/table-override_0.rst");
	if(!tables[0])
	{
		fputs("unable to open test/tables/table-override_0.rst\n", output);
		goto free_and_return;
	}

	if(!test_expect(output, (const struct table * const*)tables, 2, NULL, BOTH, u"a", 1, u"⠾", 1))
		goto free_and_return;
	if(!test_expect(output, (const struct table * const*)tables, 2, NULL, BOTH, u"abc", 3, u"⠸", 1))
		goto free_and_return;

	status = 1;

	free_and_return:
	if(tables[0])
		table_free(tables[0]);
	if(tables[1])
		table_free(tables[1]);

	fputs("\n", output);
	fflush(output);

	if(output != stdout)
	if(status)
		puts("PASS");
	else
		puts("FAIL");

	return status;
}

int test_table_override_with_lookup(FILE *output)
{
	struct table **tables;
	int table_cnt, status;

	status = 0;
	tables = NULL;

	if(output != stdout)
		printf("test_table_override_with_lookup:  ");

	fputs("test_table_override_with_lookup\n\n", output);

	if(!lookup_add_paths("test/tables/"))
		goto free_and_return;

	tables = lookup_tables(&table_cnt, "table-override_1.rst");
	if(!tables)
		goto free_and_return;

	if(!test_expect(output, (const struct table * const*)tables, 1, NULL, BOTH, u"a", 1, u"⠁", 1))
		goto free_and_return;
	if(!test_expect(output, (const struct table * const*)tables, 1, NULL, BOTH, u"abc", 3, u"⠇", 1))
		goto free_and_return;

	FREE(tables);
	tables = lookup_tables(&table_cnt, "table-override_0.rst~table-override_1.rst");
	if(!tables)
		goto free_and_return;

	if(!test_expect(output, (const struct table * const*)tables, 2, NULL, BOTH, u"a", 1, u"⠾", 1))
		goto free_and_return;
	if(!test_expect(output, (const struct table * const*)tables, 2, NULL, BOTH, u"abc", 3, u"⠸", 1))
		goto free_and_return;

	status = 1;

	free_and_return:
	if(tables)
		FREE(tables);
	lookup_fini();

	fputs("\n", output);
	fflush(output);

	if(output != stdout)
	if(status)
		puts("PASS");
	else
		puts("FAIL");

	return status;
}

int test_cursor(FILE *output)
{
	struct table *table;
	int cursors_forward[]  = {0,0,0,1,2,6,7,7,8,8,8,9,9,10,11,11,12,12,13,13,14,15,16,17};
	int cursors_backward[] = {0,3,4,4,4,4,5,6,8,11,13,14,16,18,20,21,22,23};
	int status, i;

	status = 0;

	if(output != stdout)
		printf("test_cursor:  ");

	fputs("test_cursor\n\n", output);

	table = table_compile_from_file("test/tables/translate-cursor.rst");
	if(!table)
	{
		fputs("unable to open test/tables/translate-cursor.rst\n", output);
		goto free_and_return;
	}

	for(i = 0; i < 22; i++)
		if(!test_expect_cursor(
			output, (const struct table * const*)&table, 1, NULL, FORWARD,
			u"abc x acabcac abacbc cba", 24,
			u"⠿ ⠭⠗⠺⠭ ⠭⠿⠭ ⠛⠭⠶ ⠤⠒⠉", 18,
			i, cursors_forward[i]))
			goto free_and_return;

	for(i = 0; i < 18; i++)
		if(!test_expect_cursor(
			output, (const struct table * const*)&table, 1, NULL, BACKWARD,
			u"⠿ ⠭⠗⠺⠭ ⠭⠿⠭ ⠛⠭⠶ ⠤⠒⠉", 18,
			u"abc x acabcac abacbc cba", 24,
			i, cursors_backward[i]))
			goto free_and_return;

	status = 1;

	free_and_return:
	if(table)
		table_free(table);

	fputs("\n", output);
	fflush(output);

	if(output != stdout)
	if(status)
		puts("PASS");
	else
		puts("FAIL");

	return status;
}

int test_mapping_with_capital(FILE *output)
{
	struct table *table;
	int status;

	status = 0;

	if(output != stdout)
		printf("test_mapping_with_capital:  ");

	fputs("test_mapping_with_capital\n\n", output);

	table = table_compile_from_file("test/tables/translate-mapping.rst");
	if(!table)
	{
		fputs("unable to open test/tables/translate-mapping.rst\n", output);
		goto free_and_return;
	}

	if(!test_expect_mapping(
		output, (const struct table * const*)&table, 1, NULL, BOTH,
		u"ABC Abc abc abC ABC", 19,
		u"⠯⠭⠿⠀⠯⠿⠀⠿⠀⠉⠒⠯⠤⠀⠯⠭⠿", 17,
		(const int[]){2,2,2,3,5,5,5,6,7,7,7,8,9,10,12,13,16,16,16},
		(const int[]){-1,-1,0,3,-1,4,7,8,11,12,13,-1,14,15,-1,-1,16}))
		goto free_and_return;

	if(!test_expect_mapping(
		output, (const struct table * const*)&table, 1, NULL, BOTH,
		u"ABC ABC ABC Abc abc abC ABC ABc abc", 35,
		u"⠯⠭⠭⠿⠀⠿⠀⠿⠭⠭⠽⠀⠯⠿⠀⠿⠀⠉⠒⠯⠤⠀⠯⠭⠿⠀⠯⠭⠉⠒⠭⠽⠤⠀⠿", 35,
		(const int[]){3,3,3,4,5,5,5,6,7,7,7,11,13,13,13,14,15,15,15,16,17,18,20,21,24,24,24,25,28,29,32,33,34,34,34},
		(const int[]){-1,-1,-1,0,3,4,7,8,-1,-1,-1,11,-1,12,15,16,19,20,21,-1,22,23,-1,-1,24,27,-1,-1,28,29,-1,-1,30,31,32}))
		goto free_and_return;

	status = 1;

	free_and_return:
	if(table)
		table_free(table);

	fflush(output);

	if(output != stdout)
	if(status)
		puts("PASS");
	else
		puts("FAIL");

	return status;
}

/******************************************************************************/

int test_library(FILE *output)
{
	int pass_cnt;

	if(!output)
	{
		output = fopen("build/test/output-library.txt", "w");
		if(!output)
			output = stdout;
	}

	if(output != stdout)
		puts("testing library");

	fputs("testing library\n\n", output);

	pass_cnt = 0;

	pass_cnt += test_rule_sort(output);
	pass_cnt += test_table_include(output);
	pass_cnt += test_table_override(output);
	pass_cnt += test_table_override_with_lookup(output);
	pass_cnt += test_cursor(output);
	pass_cnt += test_mapping_with_capital(output);

	if(output != stdout)
	{
		puts("");
		fclose(output);
	}

	return 6 - pass_cnt;
}

/******************************************************************************/
