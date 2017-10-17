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
#include <string.h>

#include "lookup.h"
#include "utf-output.h"
#include "table-output.h"
#include "log.h"

static int out_ambiguouos_chars, out_ambiguouos_dots, opt_ignore_filters, out_table;

/******************************************************************************/

static void get_ambiguous_rules_chars(
	const struct rule *const*rules_hash,
	const int rules_hash_size)
{
	const struct rule *rule, *nxt;
	int i;

	for(i = 0; i < rules_hash_size; i++)
	{
		rule = rules_hash[i];
		while(rule)
		{
			nxt = rule->chars_nxt;
			while(nxt)
			{
				if(   utf16_are_equal(rule->chars, rule->chars_len, nxt->chars, nxt->chars_len)
				   && !utf16_are_equal(rule->chars, rule->chars_len, nxt->chars, nxt->chars_len)
				   && (opt_ignore_filters || (!rule->filter_backward && !nxt->filter_backward)))
				{
					if(rule->chars_len == 1)
						utf16le_output_char_escape(stdout, rule->chars[0]);
					else
						utf16le_output(stdout, rule->chars, rule->chars_len);
					printf(" ");
					if(rule->chars_len == 1)
						utf16le_output_char_escape(stdout, rule->chars[0]);
					else
						utf16le_output(stdout, rule->chars, rule->chars_len);

					printf("   ");

					if(nxt->chars_len == 1)
						utf16le_output_char_escape(stdout, nxt->chars[0]);
					else
						utf16le_output(stdout, nxt->chars, nxt->chars_len);
					printf(" ");
					if(nxt->chars_len == 1)
						utf16le_output_char_escape(stdout, nxt->chars[0]);
					else
						utf16le_output(stdout, nxt->chars, nxt->chars_len);

					puts("");
				}
				nxt = nxt->chars_nxt;
			}
			rule = rule->chars_nxt;
		}
	}
}

static void table_get_ambiguous_rules_chars(const struct table *table)
{
	puts("chars init:");
	get_ambiguous_rules_chars((const struct rule*const*)table->init_chars_hash, TABLE_TRANS_HASH_SIZE);
	puts("");
	puts("chars pretrans:");
	get_ambiguous_rules_chars((const struct rule*const*)table->pretrans_chars_hash, TABLE_TRANS_HASH_SIZE);
	puts("");
	puts("chars trans:");
	get_ambiguous_rules_chars((const struct rule*const*)table->trans_chars_hash, TABLE_TRANS_HASH_SIZE);
}

static void get_ambiguous_rules_dots(
	const struct rule *const*rules_hash,
	const int rules_hash_size)
{
	const struct rule *rule, *nxt;
	int i, j;

	for(i = 0; i < rules_hash_size; i++)
	{
		rule = rules_hash[i];
		while(rule)
		{
			nxt = rule->dots_nxt;
			while(nxt)
			{
				if(   utf16_are_equal(rule->dots, rule->dots_len, nxt->dots, nxt->dots_len)
				   && !utf16_are_equal(rule->chars, rule->chars_len, nxt->chars, nxt->chars_len)
				   && (opt_ignore_filters || (!rule->filter_backward && !nxt->filter_backward)))
				{
					if(rule->dots_len == 1)
						utf16le_output_char_escape(stdout, rule->dots[0]);
					else
						utf16le_output(stdout, rule->dots, rule->dots_len);

					printf("   \t");

					if(rule->chars_len == 1)
						utf16le_output_char_escape(stdout, rule->chars[0]);
					else
						utf16le_output(stdout, rule->chars, rule->chars_len);
					printf("\t");
					if(nxt->chars_len == 1)
						utf16le_output_char_escape(stdout, nxt->chars[0]);
					else
						utf16le_output(stdout, nxt->chars, nxt->chars_len);

					printf("   \t");

					for(j = 0; j < rule->chars_len; j++)
						printf("\\x%04x", rule->chars[j]);
					printf("   ");
					for(j = 0; j < nxt->chars_len; j++)
						printf("\\x%04x", nxt->chars[j]);

					puts("");
				}
				nxt = nxt->dots_nxt;
			}
			rule = rule->dots_nxt;
		}
	}
}

static void table_get_ambiguous_rules_dots(const struct table *table)
{
	puts("dots init:");
	get_ambiguous_rules_dots((const struct rule*const*)table->init_dots_hash, TABLE_DOTS_HASH_SIZE);
	puts("");
	puts("dots pretrans:");
	get_ambiguous_rules_dots((const struct rule*const*)table->pretrans_dots_hash, TABLE_DOTS_HASH_SIZE);
	puts("");
	puts("dots trans:");
	get_ambiguous_rules_dots((const struct rule*const*)table->trans_dots_hash, TABLE_DOTS_HASH_SIZE);
}

/******************************************************************************/

static void log_callback(const int level, const char *message)
{
	switch(level)
	{
	case LOG_ALL:      fprintf(stderr, "ALL:  ");      break;
	case LOG_TRACE:    fprintf(stderr, "TRACE:  ");    break;
	case LOG_DEBUG:    fprintf(stderr, "DEBUG:  ");    break;
	case LOG_INFO:     fprintf(stderr, "INFO:  ");     break;
	case LOG_WARNING:  fprintf(stderr, "WARNING:  ");  break;
	case LOG_ERROR:    fprintf(stderr, "ERROR:  ");    break;
	case LOG_FATAL:    fprintf(stderr, "FATAL:  ");    break;
	}

	fprintf(stderr, "%s\n", message);
	fflush(stderr);
}

static void print_usage(void)
{
	const char *txt[] =
	{
		"Usage: lou_table [OPTIONS] TABLE_FILE",
		"Options:",
		"   -a         output ambiguous chars and dots",
		"   -ac        output ambiguous chars",
		"   -ad        output ambiguous chars",
		"   -f         ignore filters when outputting ambiguous",
		"   -p PATHS   add PATHS to table paths",
		"   -v         print version",
		"   -h         print this message",
		NULL
	};
	int i;

	for(i = 0; txt[i]; i++)
		puts(txt[i]);
}

static void print_version(void)
{
	const char *txt[] =
	{
		"lou_table (LibLouisAPH) " VERSION,
		"Copyright (C) 2017 American Printing House for the Blind, Inc. <www.aph.org>",
		"Licensed under the Apache License, Version 2.0 <http://www.apache.org/licenses/LICENSE-2.0>.",
		NULL
	};
	int i;

	for(i = 0; txt[i]; i++)
		puts(txt[i]);
}

static char** scan_arguments(char **args, const int argn)
{
	if(   argn == 1
	   || (args[1][0] == '-'
	   && (!strncmp(args[1], "-h", 3) || !strncmp(args[1], "--help", 7))))
	{
		print_usage();
		return NULL;
	}

	if(   argn == 1
	   || (args[1][0] == '-'
	   && (!strncmp(args[1], "-v", 3) || !strncmp(args[1], "--version", 10))))
	{
		print_version();
		exit(0);
	}

	for(args++; *args && **args == '-'; args++)
	switch((*args)[1])
	{
	case 'a':

		if((*args)[2] == 'c')
			out_ambiguouos_chars = 1;
		else if((*args)[2] == 'd')
			out_ambiguouos_dots = 1;
		else
			out_ambiguouos_chars =
			out_ambiguouos_dots = 1;
		break;

	case 'f':  opt_ignore_filters = 1;  break;

	case 'p':  add_paths:

		args++;
		lookup_add_paths(*args);
		break;

	/*   read long arguments   */
	case '-':

		if((*args)[2] == 0)
			return ++args;
		else if(!strncmp(&((*args)[2]), "output-ambiguous-chars-dots", 28))
			out_ambiguouos_chars =
			out_ambiguouos_dots = 1;
		else if(!strncmp(&((*args)[2]), "output-ambiguous-chars", 23))
			out_ambiguouos_chars = 1;
		else if(!strncmp(&((*args)[2]), "output-ambiguous-dots", 22))
			out_ambiguouos_dots = 1;
		else if(!strncmp(&((*args)[2]), "paths", 6))
			goto add_paths;
		else
			goto on_error;
		break;

	default:  on_error:

		fprintf(stderr, "unknown option %s", *args);
		return NULL;
	}

	return args;
}

int main(int argn, char **args)
{
	struct table *table;

	out_table = 1;
	out_ambiguouos_chars =
	out_ambiguouos_dots = 0;
	opt_ignore_filters = 0;

	args = scan_arguments(args, argn);
	if(!args)
		return 1;
	if(!args[0])
	{
		print_usage();
		return 1;
	}

	log_set_callback(log_callback);


	table = lookup_table(args[0]);
	if(!table)
		return 1;

	printf("%s\n", args[0]);

	if(!out_ambiguouos_chars && !out_ambiguouos_dots)
		table_output(stdout, table);

	puts("");

	if(out_ambiguouos_chars)
	{
		puts("ambiguous char rules:");
		table_get_ambiguous_rules_chars(table);
		puts("");
	}

	if(out_ambiguouos_dots)
	{
		puts("ambiguous dot rules:");
		table_get_ambiguous_rules_dots(table);
		puts("");
	}

	return 0;
}

/******************************************************************************/
