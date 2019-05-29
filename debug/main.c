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

/*   needed for setenv and unsetenv   */
#define _XOPEN_SOURCE 600

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "utf-convert.h"
#include "translate.h"
#include "lookup.h"
#include "utf-output.h"
#include "table-output.h"
#include "conversion-output.h"
#include "log.h"

void debug_output_chomp(const unichar *uchars, const int uchars_len);

/******************************************************************************/

static int input_get_length(const unichar *uchars, const int uchars_max)
{
	int len;

	for(len = 0; len < uchars_max; len++)
	if(!uchars[len])
		break;

	return len;
}

static void test_input(const struct table *const*tables, const int table_cnt, const struct conversion *conversion, const char *input)
{
	unichar *uchars, *trans;
	int input_len, uchars_len, trans_len, len;

	input_len = strlen(input);
	uchars_len = input_len;
	trans_len = uchars_len * 5;
	if(trans_len < 0x100)
		trans_len = 0x100;
	uchars = MALLOC((uchars_len + 1) * sizeof(unichar));
	trans  = MALLOC((trans_len + 1) * sizeof(unichar));

	memset(uchars, 0, (uchars_len + 1) * sizeof(unichar));
	memset(trans, 0, (trans_len + 1) * sizeof(unichar));

	uchars_len = utf8_convert_to_utf16(uchars, (uchars_len + 1), input, input_len, NULL);
	uchars_len = table_convert_escape_markers(tables[table_cnt - 1], uchars, uchars_len);
	uchars_len = utf16_convert_escapes(uchars, uchars_len);

	len = translate_start(trans, trans_len, uchars, uchars_len, tables, table_cnt, conversion, FORWARD, NULL, NULL, NULL);
	if(len == -1)
	{
		fprintf(stderr, "FAIL\n");
		return;
	}

	table_convert_markers(tables[table_cnt - 1], uchars, uchars_len);
	debug_output_chomp(uchars, uchars_len);
	puts("");
	table_convert_markers(tables[table_cnt - 1], trans, trans_len);
	debug_output_chomp(trans, len);
	puts("");

	FREE(uchars);
	FREE(trans);
}

static void test_input_line(const struct table *const*tables, const int table_cnt, const struct conversion *conversion, const char *input)
{
	test_input(tables, table_cnt, conversion, input);
	puts("");
}

static void test_input_both(const struct table *const*tables, const int table_cnt, const struct conversion *conversion, const char *input)
{
	unichar *uchars, *trans, *reverse;
	int input_len, uchars_len, trans_len, reverse_len;

	input_len = strlen(input);
	uchars_len = input_len;
	trans_len = uchars_len * 5;
	if(trans_len < 0x100)
		trans_len = 0x100;
	reverse_len = uchars_len * 5;
	uchars   = MALLOC((uchars_len + 1) * sizeof(unichar));
	trans    = MALLOC((trans_len + 1) * sizeof(unichar));
	reverse  = MALLOC((reverse_len + 1) * sizeof(unichar));

	memset(uchars, 0, (uchars_len + 1) * sizeof(unichar));
	memset(trans, 0, (trans_len + 1) * sizeof(unichar));
	memset(reverse, 0, (reverse_len + 1) * sizeof(unichar));

	uchars_len = utf8_convert_to_utf16(uchars, (uchars_len + 1), input, input_len, NULL);
	uchars_len = table_convert_escape_markers(tables[table_cnt - 1], uchars, uchars_len);
	uchars_len = utf16_convert_escapes(uchars, uchars_len);

	trans_len = translate_start(trans, trans_len, uchars, uchars_len, tables, table_cnt, conversion, FORWARD, NULL, NULL, NULL);
	if(trans_len == -1)
	{
		fprintf(stderr, "FAIL\n");
		return;
	}
	reverse_len = translate_start(reverse, reverse_len, trans, trans_len, tables, table_cnt, conversion, BACKWARD, NULL, NULL, NULL);
	if(reverse_len == -1)
	{
		fprintf(stderr, "FAIL\n");
		return;
	}

	table_convert_markers(tables[table_cnt - 1], uchars, uchars_len);
	debug_output_chomp(uchars, uchars_len);
	puts("");
	table_convert_markers(tables[table_cnt - 1], trans, trans_len);
	debug_output_chomp(trans, trans_len);
	puts("");
	debug_output_chomp(reverse, reverse_len);
	puts("");

	FREE(uchars);
	FREE(trans);
	FREE(reverse);
}

static void test_input_both_line(const struct table *const*tables, const int table_cnt, const struct conversion *conversion, const char *input)
{
	test_input_both(tables, table_cnt, conversion, input);
	puts("");
}

static int test_input_both_pass(const struct table *const*tables, const int table_cnt, const struct conversion *conversion, const char *input)
{
	unichar *uchars, *trans, *reverse;
	int input_len, uchars_len, trans_len, reverse_len;
	int pass;

	input_len = strlen(input);
	uchars_len = input_len;
	trans_len = uchars_len * 5;
	if(trans_len < 0x100)
		trans_len = 0x100;
	reverse_len = uchars_len * 5;
	uchars   = MALLOC((uchars_len + 1) * sizeof(unichar));
	trans    = MALLOC((trans_len + 1) * sizeof(unichar));
	reverse  = MALLOC((reverse_len + 1) * sizeof(unichar));

	memset(uchars, 0, (uchars_len + 1) * sizeof(unichar));
	memset(trans, 0, (trans_len + 1) * sizeof(unichar));
	memset(reverse, 0, (reverse_len + 1) * sizeof(unichar));

	uchars_len = utf8_convert_to_utf16(uchars, (uchars_len + 1), input, input_len, NULL);
	uchars_len = table_convert_escape_markers(tables[table_cnt - 1], uchars, uchars_len);
	uchars_len = utf16_convert_escapes(uchars, uchars_len);

	trans_len = translate_start(trans, trans_len, uchars, uchars_len, tables, table_cnt, conversion, FORWARD, NULL, NULL, NULL);
	if(trans_len == -1)
	{
		fprintf(stderr, "FAIL\n");
		return 0;
	}
	reverse_len = translate_start(reverse, reverse_len, trans, trans_len, tables, table_cnt, conversion, BACKWARD, NULL, NULL, NULL);
	if(reverse_len == -1)
	{
		fprintf(stderr, "FAIL\n");
		return 0;
	}

	pass = 1;
	if(!utf16_are_equal(uchars, uchars_len, reverse, reverse_len))
	{
		pass = 0;
		table_convert_markers(tables[table_cnt - 1], uchars, uchars_len);
		debug_output_chomp(uchars, uchars_len);
		printf("   ");
		debug_output_chomp(trans, trans_len);
		printf("   ");
		debug_output_chomp(reverse, reverse_len);
		puts("");
	}

	FREE(uchars);
	FREE(trans);
	FREE(reverse);

	return pass;
}

static void test_input_uchars(const struct table *const*tables, const int table_cnt, const struct conversion *conversion, const unichar *uchars, const int uchars_len)
{
	unichar *trans;
	int trans_len, len;

	trans_len = uchars_len * 5;
	if(trans_len < 0x100)
		trans_len = 0x100;
	trans  = MALLOC((trans_len + 1) * sizeof(unichar));

	memset(trans, 0, (trans_len + 1) * sizeof(unichar));

	len = translate_start(trans, trans_len, uchars, uchars_len, tables, table_cnt, conversion, FORWARD, NULL, NULL, NULL);
	if(len == -1)
	{
		fprintf(stderr, "FAIL\n");
		return;
	}

	debug_output_chomp(uchars, uchars_len);
	puts("");
	debug_output_chomp(trans, len);
	puts("");

	puts("");

	FREE(trans);
}

static void test_input_mapping(const struct table *const*tables, const int table_cnt, const struct conversion *conversion, const char *input)
{
	unichar *uchars, *trans;
	int *chars_to_dots_map, *dots_to_chars_map;
	int input_len, uchars_len, trans_len, len, i;

	input_len = strlen(input);
	uchars_len = input_len;
	trans_len = uchars_len * 5;
	if(trans_len < 0x100)
		trans_len = 0x100;
	uchars = MALLOC((uchars_len + 1) * sizeof(unichar));
	trans  = MALLOC((trans_len + 1) * sizeof(unichar));
	chars_to_dots_map = MALLOC((uchars_len + 1) * sizeof(int));
	dots_to_chars_map = MALLOC((trans_len + 1) * sizeof(int));

	memset(uchars, 0, (uchars_len + 1) * sizeof(unichar));
	memset(trans, 0, (trans_len + 1) * sizeof(unichar));
	memset(chars_to_dots_map, 0, (uchars_len + 1) * sizeof(int));
	memset(dots_to_chars_map, 0, (trans_len + 1) * sizeof(int));

	uchars_len = utf8_convert_to_utf16(uchars, (uchars_len + 1), input, input_len, NULL);
	len = translate_start(trans, trans_len, uchars, uchars_len, tables, table_cnt, conversion, FORWARD, chars_to_dots_map, dots_to_chars_map, NULL);
	if(len == -1)
	{
		fprintf(stderr, "FAIL\n");
		return;
	}

	for(i = 0; i < uchars_len; i++)
		printf("%x", (i % 16));
	puts("");
	table_convert_markers(tables[table_cnt - 1], uchars, uchars_len);
	debug_output_chomp(uchars, uchars_len);
	puts("");
	for(i = 0; i < uchars_len; i++)
	if(uchars[i])
	if(chars_to_dots_map[i] == -1)
		printf("_");
	else
		printf("%x", (chars_to_dots_map[i] % 16));
	else
		break;
	puts("\n");

	for(i = 0; i < len; i++)
		printf("%x", (i % 16));
	puts("");
	table_convert_markers(tables[table_cnt - 1], trans, len);
	debug_output_chomp(trans, len);
	puts("");
	for(i = 0; i < len; i++)
	if(dots_to_chars_map[i] == -1)
		printf("_");
	else
		printf("%x", (dots_to_chars_map[i] % 16));
	puts("");

	puts("");

	FREE(uchars);
	FREE(trans);
	FREE(chars_to_dots_map);
	FREE(dots_to_chars_map);
}

static void test_input_both_mapping(const struct table *const*tables, const int table_cnt, const struct conversion *conversion, const char *input)
{
	unichar *uchars, *trans, *reverse;
	int *chars_to_dots_fmap, *dots_to_chars_fmap, *chars_to_dots_bmap, *dots_to_chars_bmap;
	int input_len, uchars_len, trans_len, reverse_len, i;

	input_len = strlen(input);
	uchars_len = input_len;
	trans_len = uchars_len * 5;
	if(trans_len < 0x100)
		trans_len = 0x100;
	reverse_len = uchars_len * 5;
	uchars   = MALLOC((uchars_len + 1) * sizeof(unichar));
	trans    = MALLOC((trans_len + 1) * sizeof(unichar));
	reverse  = MALLOC((reverse_len + 1) * sizeof(unichar));
	chars_to_dots_fmap = MALLOC((uchars_len + 1) * sizeof(int));
	dots_to_chars_fmap = MALLOC((trans_len + 1) * sizeof(int));
	chars_to_dots_bmap = MALLOC((trans_len + 1) * sizeof(int));
	dots_to_chars_bmap = MALLOC((reverse_len + 1) * sizeof(int));

	memset(uchars, 0, (uchars_len + 1) * sizeof(unichar));
	memset(trans, 0, (trans_len + 1) * sizeof(unichar));
	memset(reverse, 0, (reverse_len + 1) * sizeof(unichar));
	memset(chars_to_dots_fmap, 0, (uchars_len + 1) * sizeof(int));
	memset(dots_to_chars_fmap, 0, (trans_len + 1) * sizeof(int));
	memset(chars_to_dots_bmap, 0, (trans_len + 1) * sizeof(int));
	memset(dots_to_chars_bmap, 0, (reverse_len + 1) * sizeof(int));

	uchars_len = utf8_convert_to_utf16(uchars, (uchars_len + 1), input, input_len, NULL);
	uchars_len = table_convert_escape_markers(tables[table_cnt - 1], uchars, uchars_len);
	uchars_len = utf16_convert_escapes(uchars, uchars_len);

	trans_len = translate_start(trans, trans_len, uchars, uchars_len, tables, table_cnt, conversion, FORWARD, chars_to_dots_fmap, dots_to_chars_fmap, NULL);
	if(trans_len == -1)
	{
		fprintf(stderr, "FAIL\n");
		return;
	}
	reverse_len = translate_start(reverse, reverse_len, trans, trans_len, tables, table_cnt, conversion, BACKWARD, chars_to_dots_bmap, dots_to_chars_bmap, NULL);
	if(reverse_len == -1)
	{
		fprintf(stderr, "FAIL\n");
		return;
	}

	/*   forward   */

	for(i = 0; i < uchars_len; i++)
		printf("%x", (i % 16));
	puts("");
	table_convert_markers(tables[table_cnt - 1], uchars, uchars_len);
	debug_output_chomp(uchars, uchars_len);
	puts("");
	for(i = 0; i < uchars_len; i++)
	if(chars_to_dots_fmap[i] == -1)
		printf("_");
	else
		printf("%x", (chars_to_dots_fmap[i] % 16));
	puts("\n");

	for(i = 0; i < trans_len; i++)
		printf("%x", (i % 16));
	puts("");
	debug_output_chomp(trans, trans_len);
	puts("");
	for(i = 0; i < trans_len; i++)
	if(dots_to_chars_fmap[i] == -1)
		printf("_");
	else
		printf("%x", (dots_to_chars_fmap[i] % 16));
	puts("\n");

	/*   backward   */

	for(i = 0; i < trans_len; i++)
		printf("%x", (i % 16));
	puts("");
	debug_output_chomp(trans, trans_len);
	puts("");
	for(i = 0; i < trans_len; i++)
	if(chars_to_dots_bmap[i] == -1)
		printf("_");
	else
		printf("%x", (chars_to_dots_bmap[i] % 16));
	puts("\n");

	for(i = 0; i < reverse_len; i++)
		printf("%x", (i % 16));
	puts("");
	debug_output_chomp(reverse, reverse_len);
	puts("");
	for(i = 0; i < reverse_len; i++)
	if(dots_to_chars_bmap[i] == -1)
		printf("_");
	else
		printf("%x", (dots_to_chars_bmap[i] % 16));
	puts("\n");

	puts("\n");

	FREE(uchars);
	FREE(trans);
	FREE(reverse);
	FREE(chars_to_dots_fmap);
	FREE(dots_to_chars_fmap);
	FREE(chars_to_dots_bmap);
	FREE(dots_to_chars_bmap);
}

static void test_input_mapping_vert(const struct table *const*tables, const int table_cnt, const struct conversion *conversion, const char *input)
{
	unichar *uchars, *trans;
	int *chars_to_dots_map, *dots_to_chars_map;
	int input_len, uchars_len, trans_len, len, i;

	test_input(tables, table_cnt, conversion, input);

	input_len = strlen(input);
	uchars_len = input_len;
	trans_len = uchars_len * 5;
	if(trans_len < 0x100)
		trans_len = 0x100;
	uchars = MALLOC((uchars_len + 1) * sizeof(unichar));
	trans  = MALLOC((trans_len + 1) * sizeof(unichar));
	chars_to_dots_map = MALLOC((uchars_len + 1) * sizeof(int));
	dots_to_chars_map = MALLOC((trans_len + 1) * sizeof(int));

	memset(uchars, 0, (uchars_len + 1) * sizeof(unichar));
	memset(trans, 0, (trans_len + 1) * sizeof(unichar));
	memset(chars_to_dots_map, 0, (uchars_len + 1) * sizeof(int));
	memset(dots_to_chars_map, 0, (trans_len + 1) * sizeof(int));

	uchars_len = utf8_convert_to_utf16(uchars, (uchars_len + 1), input, input_len, NULL);
	uchars_len = table_convert_escape_markers(tables[table_cnt - 1], uchars, uchars_len);
	uchars_len = utf16_convert_escapes(uchars, uchars_len);

	len = translate_start(trans, trans_len, uchars, uchars_len, tables, table_cnt, conversion, FORWARD, chars_to_dots_map, dots_to_chars_map, NULL);
	if(len == -1)
	{
		fprintf(stderr, "FAIL\n");
		return;
	}

	for(i = 0; i < MAX(uchars_len, len); i++)
	{
		if(i < uchars_len)
		{
			printf("%02x", (i % 0xff));

			printf("  ");

			utf16_output_char(stdout, uchars[i]);

			if(chars_to_dots_map[i] == -1)
				printf("\t _");
			else
				printf("\t%02x", (chars_to_dots_map[i] % 0xff));
		}

		if(i < len)
		{
			printf("  \t");

			printf("%02x", (i % 0xff));

			printf("  ");

			utf16_output_char(stdout, trans[i]);

			if(dots_to_chars_map[i] == -1)
				printf("\t _");
			else
				printf("\t%02x", (dots_to_chars_map[i] % 0xff));
		}

		puts("");
	}

	puts("");

	FREE(uchars);
	FREE(trans);
	FREE(chars_to_dots_map);
	FREE(dots_to_chars_map);
}

static void test_input_cursor(const struct table *const*tables, const int table_cnt, const struct conversion *conversion, const char *input, const int cursor)
{
	unichar *uchars, *trans;
	int input_len, uchars_len, trans_len, len, crs, i;

	input_len = strlen(input);
	uchars_len = input_len;
	trans_len = uchars_len * 5;
	if(trans_len < 0x100)
		trans_len = 0x100;
	uchars = MALLOC((uchars_len + 1) * sizeof(unichar));
	trans  = MALLOC((trans_len + 1) * sizeof(unichar));

	memset(uchars, 0, (uchars_len + 1) * sizeof(unichar));
	memset(trans, 0, (trans_len + 1) * sizeof(unichar));
	crs = cursor;

	uchars_len = utf8_convert_to_utf16(uchars, (uchars_len + 1), input, input_len, NULL);
	uchars_len = utf16_convert_escapes(uchars, uchars_len);
	len = translate_start(trans, trans_len, uchars, uchars_len, tables, table_cnt, conversion, BACKWARD, NULL, NULL, &crs);
	if(len == -1)
	{
		fprintf(stderr, "FAIL\n");
		return;
	}

	for(i = 0; i < cursor; i++)
		printf(" ");
	puts("#");
	table_convert_markers(tables[table_cnt - 1], uchars, uchars_len);
	debug_output_chomp(uchars, uchars_len);
	puts("");
	table_convert_markers(tables[table_cnt - 1], trans, trans_len);
	debug_output_chomp(trans, len);
	puts("");
	for(i = 0; i < crs; i++)
		printf(" ");
	puts("#");
	printf("%d : %d\n", cursor, crs);

	puts("");

	FREE(uchars);
	FREE(trans);
}

/******************************************************************************/

static void log_callback(const int level, const char *message)
{
	switch(level)
	{
	case LOG_ALL:      printf("ALL:  ");      break;
	case LOG_TRACE:    printf("TRACE:  ");    break;
	case LOG_DEBUG:    printf("DEBUG:  ");    break;
	case LOG_INFO:     printf("INFO:  ");     break;
	case LOG_WARNING:  printf("WARNING:  ");  break;
	case LOG_ERROR:    printf("ERROR:  ");    break;
	case LOG_FATAL:    printf("FATAL:  ");    break;
	}

	printf("%s\n", message);
	fflush(stdout);
}

#define USER(tag)      "\uf001" #tag "\uf001"
#define BEGIN(tag)     "\uf002" #tag "\uf002"
#define END(tag)       "\uf003" #tag "\uf003"
#define MODIFIER(tag)  "\uf004" #tag "\uf004"
#define HARD(tag)      "\uf005" #tag "\uf005"
#define SOFT(tag)      "\uf006" #tag "\uf006"
#define INTERNAL(tag)  "\uf007" #tag "\uf007"

#define TEST_INPUT_TABLE(input)  test_input_line((const struct table * const*)&table, 1, conversion, input)

static int test_input_compiled(void)
{
	struct table *table;
	struct conversion *conversion;

	table = NULL;
	conversion = NULL;

	MEM_INIT

	log_set_callback(log_callback);

	//unsetenv("LOUIS_TABLEPATH");
	//setenv("LOUIS_TABLEPATH", "tables", 0);
	//lookup_add_paths("test/tables:tables");

	table = table_compile_from_file("debug/table.rst");
	//table = table_compile_from_file("tables/english-ueb-grade2.rst");
	if(!table)
		return 1;
	//table_output(stdout, table);  puts("");

	//conversion = conversion_compile_from_file("tables/ascii.cvt");  if(!conversion) return 1;
	//conversion_output(stdout, conversion);  puts("");

	TEST_INPUT_TABLE("liblouisaph");
	//TEST_INPUT_TABLE("LibLouisAPH");

	table_free(table);
	if(conversion)
		conversion_free(conversion);
	lookup_fini();
	MEM_FINI

	return 0;
}

static int test_input_table(void)
{
	struct table *table;
	struct conversion *conversion;

	table = NULL;
	conversion = NULL;

	MEM_INIT

	log_set_callback(log_callback);

	//unsetenv("LOUIS_TABLEPATH");
	//setenv("LOUIS_TABLEPATH", "tables", 0);
	//lookup_add_paths("test/tables:tables");

	table = lookup_table("debug/table.rst");
	//table = lookup_table("tables/english-ueb-grade2.rst");
	if(!table)
		return 1;
	//table_output(stdout, table_compiled);  puts("");

	//conversion = lookup_conversion("tables/ascii.cvt");  if(!conversion) return 1;
	//conversion_output(stdout, conversion);  puts("");

	TEST_INPUT_TABLE("liblouisaph");
	//TEST_INPUT_TABLE("LibLouisAPH");

	lookup_fini();
	MEM_FINI

	return 0;
}

//#define TEST_INPUT(input)  test_input((const struct table * const*)tables, table_cnt, conversion, input)
#define TEST_INPUT(input)  test_input_line((const struct table * const*)tables, table_cnt, conversion, input)
//#define TEST_INPUT(input)  test_input_both_line((const struct table * const*)tables, table_cnt, conversion, input)
//#define TEST_INPUT(input)  test_input_both_pass((const struct table * const*)tables, table_cnt, conversion, input)
//#define TEST_INPUT(input)  test_input_mapping((const struct table * const*)tables, table_cnt, conversion, input)
//#define TEST_INPUT(input)  test_input_both_mapping((const struct table * const*)tables, table_cnt, conversion, input)
//#define TEST_INPUT(input)  test_input_mapping_vert((const struct table * const*)tables, table_cnt, conversion, input)

static int test_input_tables(void)
{
	struct table **tables;
	struct conversion *conversion;
	int table_cnt, i;

	tables = NULL;
	conversion = NULL;

	MEM_INIT

	log_set_callback(log_callback);

	//unsetenv("LOUIS_TABLEPATH");
	//setenv("LOUIS_TABLEPATH", "tables", 0);
	//lookup_add_paths("test/tables:tables");

	//tables = lookup_tables(&table_cnt, "debug/table.rst");
	tables = lookup_tables(&table_cnt, "tables/english-ueb-grade2.rst");
	//tables = lookup_tables(&table_cnt, "tables/nemeth-ueb.rst");
	//tables = lookup_tables(&table_cnt, "debug/table.rst~tables/english-ueb-grade2.rst");
	//tables = lookup_tables(&table_cnt, "tables/english-ueb-grade2.rst~debug/table.rst");
	if(!tables)
		return 1;
	//for(i = 0; i < table_cnt; i++){  table_output(stdout, tables[i]);  puts("");  }

	//conversion = lookup_conversion("tables/ascii.cvt");  if(!conversion) return 1;
	//conversion_output(stdout, conversion);  puts("");

	//TEST_INPUT("unicode_braille_chars");
	//TEST_INPUT("liblouisaph");
	TEST_INPUT("LibLouisAPH");

	FREE(tables);
	lookup_fini();
	MEM_FINI

	return 0;
}

int main(void)
{
	//return test_input_compiled();
	//return test_input_table();
	return test_input_tables();
	//return 0;
}

/******************************************************************************/
