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

/*   needed for setenv and unsetenv   */
#define _XOPEN_SOURCE 600

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "translate.h"
#include "lookup.h"
#include "utf-convert.h"
#include "utf-output.h"
#include "log.h"
#include "test.h"

static FILE *output;

/******************************************************************************/

static void log_callback(const int level, const char *message)
{
	switch(level)
	{
	case LOG_ALL:      fprintf(output, "ALL:  ");      break;
	case LOG_TRACE:    fprintf(output, "TRACE:  ");    break;
	case LOG_DEBUG:    fprintf(output, "DEBUG:  ");    break;
	case LOG_INFO:     fprintf(output, "INFO:  ");     break;
	case LOG_WARNING:  fprintf(output, "WARNING:  ");  break;
	case LOG_ERROR:    fprintf(output, "ERROR:  ");    break;
	case LOG_FATAL:    fprintf(output, "FATAL:  ");    break;
	}

	fprintf(output, "%s\n", message);
	fflush(output);
}

/******************************************************************************/

static int test_lookup_path(void)
{
	char paths[0x100];
	int paths_len, status;

	memset(paths, 0, 0x100);
	status = 0;

	if(output != stdout)
		printf("test_lookup_path:  ");

	fputs("test_lookup_path\n\n", output);

	lookup_fini();
	unsetenv("LOUIS_TABLEPATH");

	paths_len = lookup_get_paths(paths, 0x100);
	fprintf(output, "get:  [%d]\t%s\n", paths_len, paths);
	if(paths_len != 0)
	{
		fprintf(output, "ERROR:  %d != 0\n", paths_len);
		goto return_fail;
	}

	lookup_fini();
	setenv("LOUIS_TABLEPATH", "test/tables", 0);
	fprintf(output, "env:  [%d]\ttest/tables\n", (int)strlen("test/tables"));
	paths_len = lookup_get_paths(paths, 12);
	fprintf(output, "get:  [%d]\t%s   max = 12\n", paths_len, paths);
	if(paths_len != 11)
	{
		fprintf(output, "ERROR:  %d != 0\n", paths_len);
		goto return_fail;
	}
	if(strncmp(paths, "test/tables", 12))
	{
		fprintf(output, "ERROR:  %s != test/tables\n", paths);
		goto return_fail;
	}
	paths[0] = 0;
	paths_len = lookup_get_paths(paths, 11);
	fprintf(output, "get:  [%d]\t%s   max = 11\n", paths_len, paths);
	if(paths_len != 10)
	{
		fprintf(output, "ERROR:  %d != 0\n", paths_len);
		goto return_fail;
	}
	if(strncmp(paths, "test/table", 11))
	{
		fprintf(output, "ERROR:  %s != test/tables\n", paths);
		goto return_fail;
	}

	paths_len = lookup_set_paths("tables");
	fprintf(output, "set:  [%d]\ttables\n", paths_len);
	paths[0] = 0;
	paths_len = lookup_get_paths(paths, 0x100);
	fprintf(output, "get:  [%d]\t%s\n", paths_len, paths);
	if(paths_len != 6)
	{
		fprintf(output, "ERROR:  %d != 6\n", paths_len);
		goto return_fail;
	}
	if(strncmp(paths, "tables", 7))
	{
		fprintf(output, "ERROR:  %s != tables\n", paths);
		goto return_fail;
	}

	paths_len = lookup_add_paths("test/tables");
	fprintf(output, "add:  [%d]\ttest/tables\n", paths_len);
	paths[0] = 0;
	paths_len = lookup_get_paths(paths, 0x100);
	fprintf(output, "get:  [%d]\t%s\n", paths_len, paths);
	if(paths_len != 18)
	{
		fprintf(output, "ERROR:  %d != 18\n", paths_len);
		goto return_fail;
	}
	if(strncmp(paths, "tables:test/tables", 19))
	{
		fprintf(output, "ERROR:  %s != tables:test/tables\n", paths);
		goto return_fail;
	}

	status = 1;

	return_fail:
	lookup_fini();
	unsetenv("LOUIS_TABLEPATH");

	fputs("\n", output);
	fflush(output);

	if(output != stdout)
	if(status)
		puts("PASS");
	else
		puts("FAIL");

	return status;
}

/******************************************************************************/

static int test_rule_sort(void)
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
		fputs("ERROR:  unable to open test/tables/rule-sort_0.rst\n", output);
		goto free_and_return;
	}

	if(!test_expect(output, (const struct table * const*)&table, 1, NULL, BOTH, u"chars", 5, u"⠒⠒", 2))
		goto free_and_return;

	table_free(table);
	table = table_compile_from_file("test/tables/rule-sort_1.rst");
	if(!table)
	{
		fputs("ERROR:  unable to open test/tables/rule-sort_1.rst\n", output);
		goto free_and_return;
	}

	if(!test_expect(output, (const struct table * const*)&table, 1, NULL, BOTH, u"chars", 5, u"⠗⠺", 2))
		goto free_and_return;

	table_free(table);
	table = table_compile_from_file("test/tables/rule-sort_2.rst");
	if(!table)
	{
		fputs("ERROR:  unable to open test/tables/rule-sort_2.rst\n", output);
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

/******************************************************************************/

static int test_table_include(void)
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
		fputs("ERROR:  unable to open test/tables/table-include_0.rst\n", output);
		goto free_and_return;
	}

	if(!test_expect(output, (const struct table * const*)&table, 1, NULL, BOTH, u"<=#=>", 5, u"⠪=#=⠕", 5))
		goto free_and_return;

	table_free(table);
	table = table_compile_from_file("test/tables/table-include_1.rst");
	if(!table)
	{
		fputs("ERROR:  unable to open test/tables/table-include_1.rst\n", output);
		goto free_and_return;
	}

	if(!test_expect(output, (const struct table * const*)&table, 1, NULL, BOTH, u"<=#=>", 5, u"⠪⠭#⠭⠕", 5))
		goto free_and_return;

	table_free(table);
	table = table_compile_from_file("test/tables/table-include_2.rst");
	if(!table)
	{
		fputs("ERROR:  unable to open test/tables/table-include_2.rst\n", output);
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

/******************************************************************************/

static int test_table_include_with_environment(void)
{
	struct table **tables;
	int table_cnt, status;

	status = 0;

	if(output != stdout)
		printf("test_table_include_with_environment:  ");

	fputs("test_table_include_with_environment\n\n", output);

	lookup_fini();
	unsetenv("LOUIS_TABLEPATH");
	setenv("LOUIS_TABLEPATH", "test/tables", 0);

	tables = lookup_tables(&table_cnt, "table-include_0.rst");
	if(!tables)
		goto free_and_return;

	if(!test_expect(output, (const struct table * const*)tables, table_cnt, NULL, BOTH, u"<=#=>", 5, u"⠪=#=⠕", 5))
		goto free_and_return;

	FREE(tables);
	tables = lookup_tables(&table_cnt, "test/tables/table-include_1.rst");
	if(!tables)
		goto free_and_return;

	if(!test_expect(output, (const struct table * const*)tables, table_cnt, NULL, BOTH, u"<=#=>", 5, u"⠪⠭#⠭⠕", 5))
		goto free_and_return;

	FREE(tables);
	tables = lookup_tables(&table_cnt, "test/tables/table-include_2.rst");
	if(!tables)
		goto free_and_return;

	if(!test_expect(output, (const struct table * const*)tables, table_cnt, NULL, BOTH, u"<=#=>", 5, u"⠪⠭⠿⠭⠕", 5))
		goto free_and_return;

	status = 1;

	free_and_return:
	if(tables)
		FREE(tables);
	lookup_fini();
	unsetenv("LOUIS_TABLEPATH");

	fputs("\n", output);
	fflush(output);

	if(output != stdout)
	if(status)
		puts("PASS");
	else
		puts("FAIL");

	return status;
}

/******************************************************************************/

static int test_table_override(void)
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
		fputs("ERROR:  unable to open test/tables/table-override_1.rst\n", output);
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
		fputs("ERROR:  unable to open test/tables/table-override_0.rst\n", output);
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

/******************************************************************************/

static int test_table_override_with_lookup(void)
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

/******************************************************************************/

static int test_cursor(void)
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
		fputs("ERROR:  unable to open test/tables/translate-cursor.rst\n", output);
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

/******************************************************************************/

static int test_mapping_with_capital(void)
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
		fputs("ERROR:  unable to open test/tables/translate-mapping.rst\n", output);
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

#define MESSAGES_LEN  63
#define MESSAGES_MAX  100
#define MESSAGE_MAX   0x100

static char  messages[MESSAGES_MAX][MESSAGE_MAX];
static int   message_crs;

static void log_callback_store(const int level, const char *message)
{
	if(message_crs >= MESSAGES_MAX)
	{
		message_crs++;
		return;
	}

	switch(level)
	{
	case LOG_ALL:      snprintf(messages[message_crs++], MESSAGE_MAX, "ALL:  %s", message);      break;
	case LOG_TRACE:    snprintf(messages[message_crs++], MESSAGE_MAX, "TRACE:  %s", message);    break;
	case LOG_DEBUG:    snprintf(messages[message_crs++], MESSAGE_MAX, "DEBUG:  %s", message);    break;
	case LOG_INFO:     snprintf(messages[message_crs++], MESSAGE_MAX, "INFO:  %s", message);     break;
	case LOG_WARNING:  snprintf(messages[message_crs++], MESSAGE_MAX, "WARNING:  %s", message);  break;
	case LOG_ERROR:    snprintf(messages[message_crs++], MESSAGE_MAX, "ERROR:  %s", message);    break;
	case LOG_FATAL:    snprintf(messages[message_crs++], MESSAGE_MAX, "FATAL:  %s", message);    break;
	}
}

static int test_table_errors(void)
{
	const char *errors[MESSAGES_MAX] =
	{
		"ERROR:  test/tables/errors.rst:2  unknown opcode UNKNOWN_OPCODE",
		"ERROR:  test/tables/errors.rst:4  include missing file name",
		"ERROR:  test/tables/errors.rst:5  unable to open include file UNKNOWN_FILE",
		"ERROR:  test/tables/errors.rst:8  invalid value INVALID_VALUE",
		"ERROR:  test/tables/errors.rst:10  missing indicator name",
		"ERROR:  test/tables/errors.rst:11  missing indicators",
		"ERROR:  test/tables/errors.rst:12  invalid dot character",
		"ERROR:  test/tables/errors.rst:13  indicator too long",
		"ERROR:  test/tables/errors.rst:14  invalid value INVALID_VALUE",
		"ERROR:  test/tables/errors.rst:16  invalid characters",
		"ERROR:  test/tables/errors.rst:17  invalid value INVALID_VALUE",
		"ERROR:  test/tables/errors.rst:19  missing join index",
		"ERROR:  test/tables/errors.rst:20  missing character",
		"ERROR:  test/tables/errors.rst:21  missing character",
		"ERROR:  test/tables/errors.rst:22  invalid value INVALID_VALUE",
		"ERROR:  test/tables/errors.rst:23  invalid value INVALID_VALUE",
		"ERROR:  test/tables/errors.rst:24  invalid value INVALID_VALUE",
		"ERROR:  test/tables/errors.rst:25  join index out of range",
		"ERROR:  test/tables/errors.rst:27  invalid attribute",
		"ERROR:  test/tables/errors.rst:28  invalid value INVALID_VALUE",
		"ERROR:  test/tables/errors.rst:30  invalid pattern",
		"ERROR:  test/tables/errors.rst:31  invalid pattern name",
		"ERROR:  test/tables/errors.rst:32  invalid pattern",
		"ERROR:  test/tables/errors.rst:34  invalid filter",
		"ERROR:  test/tables/errors.rst:35  invalid filter",
		"ERROR:  test/tables/errors.rst:36  invalid filter",
		"ERROR:  test/tables/errors.rst:37  invalid filter name",
		"ERROR:  test/tables/errors.rst:38  invalid filter",
		"ERROR:  test/tables/errors.rst:39  invalid filter",
		"ERROR:  test/tables/errors.rst:41  filter INVALID_FILTER not found",
		"ERROR:  test/tables/errors.rst:42  filter INVALID_FILTER not found",
		"ERROR:  test/tables/errors.rst:44  invalid uses",
		"ERROR:  test/tables/errors.rst:45  invalid uses",
		"ERROR:  test/tables/errors.rst:46  filter INVALID_FILTER not found",
		"ERROR:  test/tables/errors.rst:46  invalid uses",
		"ERROR:  test/tables/errors.rst:47  filter INVALID_FILTER not found",
		"ERROR:  test/tables/errors.rst:47  invalid uses",
		"ERROR:  test/tables/errors.rst:49  invalid rule",
		"ERROR:  test/tables/errors.rst:50  invalid rule",
		"ERROR:  test/tables/errors.rst:51  invalid rule",
		"ERROR:  test/tables/errors.rst:52  invalid rule",
		"ERROR:  test/tables/errors.rst:53  invalid rule type UNKNOWN_TYPE",
		"ERROR:  test/tables/errors.rst:54  invalid rule",
		"ERROR:  test/tables/errors.rst:55  invalid rule",
		"ERROR:  test/tables/errors.rst:57  invalid match",
		"ERROR:  test/tables/errors.rst:58  invalid match",
		"ERROR:  test/tables/errors.rst:59  invalid match",
		"ERROR:  test/tables/errors.rst:60  invalid match",
		"ERROR:  test/tables/errors.rst:61  invalid match",
		"ERROR:  test/tables/errors.rst:62  invalid match",
		"ERROR:  test/tables/errors.rst:63  invalid match",
		"ERROR:  test/tables/errors.rst:64  invalid match type UNKNOWN_TYPE",
		"ERROR:  test/tables/errors.rst:65  invalid match",
		"ERROR:  test/tables/errors.rst:66  invalid match",
		"ERROR:  test/tables/errors.rst:67  invalid match",
		"ERROR:  test/tables/errors.rst:68  invalid match",
		"ERROR:  test/tables/errors.rst:69  invalid match",
		"ERROR:  test/tables/errors.rst:70  invalid match",
		"ERROR:  test/tables/errors.rst:72  missing macro tag",
		"ERROR:  test/tables/errors.rst:77  recursive macro @macro, defined at test/tables/errors.rst:74",
		"ERROR:  test/tables/errors.rst:82  too many args for macro @args, defined at test/tables/errors.rst:79",
		"ERROR:  test/tables/errors.rst:83  $1 over argument count 0 for macro @args, defined at test/tables/errors.rst:79",
		"ERROR:  test/tables/errors.rst:84  $2 over argument count 1 for macro @args, defined at test/tables/errors.rst:79",
	};
	void (*log_callback_prv)(const int level, const char *message);
	struct table *table;
	int status, i;

	status = 0;

	if(output != stdout)
		printf("test_table_errors:  ");

	fputs("test_table_errors\n\n", output);

	log_callback_prv = log_get_callback();
	log_set_callback(log_callback_store);

	memset(messages, 0, sizeof(messages));
	message_crs = 0;

	table = table_compile_from_file("test/tables/errors.rst");

	for(i = 0; i < MESSAGES_LEN; i++)
	{
		if(i >= message_crs)
		{
			fputs("]ERROR:  too few errors logged\n", output);
			goto free_and_return;
		}
		if(strncmp(errors[i], messages[i], MESSAGE_MAX))
		{
			fprintf(output, "-%s\n]%s\n", messages[i], errors[i]);
			goto free_and_return;
		}
		fprintf(output, " %s\n", messages[i]);
	}
	if(i < message_crs)
	{
		fputs("]ERROR:  too many errors logged\n", output);
		for( ; i < message_crs; i++)
			fprintf(output, "-%s\n", messages[i]);
		goto free_and_return;
	}

	status = 1;

	free_and_return:
	log_set_callback(log_callback_prv);
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

int main(void)
{
	int pass_cnt, try_cnt;

	MEM_INIT

	log_set_callback(log_callback);

	output = fopen("build/test/output-library.txt", "w");
	if(!output)
		output = stdout;

	fputs("testing library\n\n", output);
	if(output != stdout)
		puts("testing library");

	pass_cnt =
	try_cnt = 0;

	try_cnt++;  pass_cnt += test_lookup_path();
	try_cnt++;  pass_cnt += test_rule_sort();
	try_cnt++;  pass_cnt += test_table_include();
	try_cnt++;  pass_cnt += test_table_include_with_environment();
	try_cnt++;  pass_cnt += test_table_override();
	try_cnt++;  pass_cnt += test_table_override_with_lookup();
	try_cnt++;  pass_cnt += test_cursor();
	try_cnt++;  pass_cnt += test_mapping_with_capital();
	try_cnt++;  pass_cnt += test_table_errors();

	puts("");
	fclose(output);

	MEM_FINI

	return try_cnt - pass_cnt;
}

/******************************************************************************/
