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
#include <string.h>

#include "table.h"
#include "conversion.h"
#include "lookup.h"
#include "log.h"

#if defined __WIN32__ || defined __WIN64__
#define FILE_SEPARATOR_STRING  "\\"
#define PATH_SEPARATOR_STRING  ";"
#define FILE_SEPARATOR_CHAR    '\\'
#define PATH_SEPARATOR_CHAR    ';'
#else
#define FILE_SEPARATOR_STRING  "/"
#define PATH_SEPARATOR_STRING  ":"
#define FILE_SEPARATOR_CHAR    '/'
#define PATH_SEPARATOR_CHAR    ':'
#endif

#define PATH_NAME_MAX  0x1000

/* Because there is no lookup_init, these need to be set when library is loaded.
*/
static struct table *table_list = NULL;
static struct conversion *conversion_list = NULL;
static char *table_paths = NULL;
static int table_paths_len = 0;
static int env_checked = 0;
static int (*lookup_hook)(char *path, const int path_max, const char *file_name, const int file_name_len) = NULL;

/******************************************************************************/

/* Because there is no lookup_init, this function must be called via check_env()
 * before table_paths is used anywhere, making sure that table_paths is set to
 * the environmental variable LOUIS_TABLEPATH.
*/
static void lookup_env(void)
{
	char *env;

	env = getenv("LOUIS_TABLEPATH");
	if(!env)
		return;

	if(table_paths)
	{
		log_message(LOG_FATAL, "table_paths already set while checking LOUIS_TABLEPATH");
		return;
	}

	table_paths_len = strlen(env);
	table_paths = MALLOC(table_paths_len + 1);
	if(!table_paths)
	{
		LOG_ALLOCATE_FAIL
		return;
	}
	strncpy(table_paths, env, table_paths_len + 1);
}

static inline void check_env(void)
{
	if(env_checked)
		return;
	env_checked = 1;
	lookup_env();
}

void lookup_fini(void)
{
	table_free(table_list);
	table_list = NULL;
	conversion_free(conversion_list);
	conversion_list = NULL;
	if(table_paths)
	{
		FREE(table_paths);
		table_paths = NULL;
		table_paths_len = 0;
	}
	env_checked = 0;
	lookup_hook = NULL;
}

/******************************************************************************/

int (*lookup_get_hook(void))(char *path, const int path_max, const char *file_name, const int file_name_len)
{
	return lookup_hook;
}

void lookup_set_hook(int (*hook)(char *path, const int path_max, const char *file_name, const int file_name_len))
{
	lookup_hook = hook;
}

/******************************************************************************/

int lookup_get_paths_length(void)
{
	check_env();

	return table_paths_len;
}

int lookup_get_paths(char *paths, const int paths_max)
{
	int len;

	check_env();

	if(!table_paths)
	{
		paths[0] = 0;
		return 0;
	}

	if(table_paths_len > paths_max - 1)
		len = paths_max - 1;
	else
		len = table_paths_len;

	strncpy(paths, table_paths, len);
	paths[len] = 0;

	return len;
}

int lookup_set_paths(const char *paths)
{
	check_env();

	if(table_paths)
		FREE(table_paths);

	if(!paths)
	{
		table_paths = NULL;
		table_paths_len = 0;
		return 1;
	}

	table_paths_len = strlen(paths);
	table_paths = MALLOC(table_paths_len + 1);
	if(!table_paths)
	{
		LOG_ALLOCATE_FAIL
		return 0;
	}
	strncpy(table_paths, paths, table_paths_len + 1);

	return table_paths_len;
}

int lookup_add_paths(const char *paths)
{
	int len;

	check_env();

	if(!paths)
		return table_paths_len;

	if(!table_paths)
	{
		table_paths_len = strlen(paths);
		table_paths = MALLOC(table_paths_len + 1);
		if(!table_paths)
		{
			LOG_ALLOCATE_FAIL
			return 0;
		}
		strncpy(table_paths, paths, table_paths_len + 1);
	}
	else
	{
		len = strlen(paths);
		table_paths_len += len + 1;
		table_paths = REALLOC(table_paths, table_paths_len + 1);
		if(!table_paths)
		{
			LOG_ALLOCATE_FAIL
			return 0;
		}
		strncat(table_paths, PATH_SEPARATOR_STRING, 2);
		strncat(table_paths, paths, len + 1);
	}

	return table_paths_len;
}

/******************************************************************************/

/*   used to iterate through the current paths   */
static int create_path_file_name(
	char *path,
	const int path_max,
	const char *paths,
	const int paths_len,
	const char *file_name,
	const int file_name_len)
{
	int len;

	if(paths_len < 1)
		return 0;

	/*   find path separator   */
	for(len = 0; len < paths_len; len++)
	if(paths[len] == PATH_SEPARATOR_CHAR)
		break;

	/*   check space   */
	if(len >= path_max - (file_name_len + 1))
		return 0;

	/*   create path name   */
	ASSERT(len > 0)
	strncpy(path, paths, len);
	path[len] = FILE_SEPARATOR_CHAR;
	strncpy(&path[len + 1], file_name, file_name_len + 1);

	return len;
}

/******************************************************************************/

static struct table* find_table(const char *file_name)
{
	struct table *table;

	table = table_list;
	while(table)
	{
		if(!strcmp(file_name, table->file_name))
			return table;
		table = table->nxt;
	}
	return NULL;
}

struct table* lookup_table(const char *file_name)
{
	struct table *table;
	char path[PATH_NAME_MAX], *paths;
	int file_name_len, paths_len, len;

	ASSERT(file_name)

	file_name_len = strlen(file_name);

	/*   has table already been loaded   */
	table = find_table(file_name);
	if(table)
		return table;

	/*   try lookup hook   */
	if(lookup_hook)
	if(lookup_hook(path, PATH_NAME_MAX, file_name, file_name_len))
	{
		table = find_table(path);
		if(table)
			return table;
		table = table_compile_from_file(path);
		if(table)
			goto return_table;
	}

	/*   try file_name directly   */
	table = table_compile_from_file(file_name);
	if(table)
		goto return_table;

	/*   assume file_name is a base name   */
	check_env();
	if(table_paths)
	{
		paths = table_paths;
		paths_len = table_paths_len;
		while(len = create_path_file_name(path, PATH_NAME_MAX, paths, paths_len, file_name, file_name_len))
		{
			table = find_table(path);
			if(table)
				return table;
			table = table_compile_from_file(path);
			if(table)
				goto return_table;

			len++;
			paths = &paths[len];
			paths_len -= len;
		}
	}

	log_message(LOG_ERROR, "unable to open table %s", file_name);
	return NULL;

	return_table:
	table->nxt = table_list;
	table_list = table;
	return table;
}

struct table** lookup_tables(int *table_cnt, const char *table_names)
{
	struct table **tables;
	char *names;
	int names_len, len, off, crs, i;

	ASSERT(table_names)

	/*   parse table_names   */
	names_len = strlen(table_names);
	names = MALLOC(names_len + 1);
	LOG_ALLOCATE_FAIL_RETURN_NULL(names)

	*table_cnt = 1;
	strncpy(names, table_names, names_len + 1);
	len = 0;
	for(i = 0; i < names_len; i++)
	if(names[i] == '~')
	{
		/*   ~ at the beginning or ~~ found   */
		if(len < 1)
		{
			log_message(LOG_ERROR, "invalid table list %s\n", table_names);
			FREE(names);
			*table_cnt = 0;
			return NULL;
		}
		(*table_cnt)++;
		len = 0;
	}
	else
		len++;

	/*   just the terminating NULL character,
	     ~ at the end   */
	if(len < 2)
	{
		log_message(LOG_ERROR, "invalid table list %s\n", table_names);
		FREE(names);
		*table_cnt = 0;
		return NULL;
	}

	/*   setup tables array   */
	tables = MALLOC(*table_cnt * sizeof(struct table*));
	if(!tables)
	{
		LOG_ALLOCATE_FAIL
		FREE(names);
		*table_cnt = 0;
		return NULL;
	}
	memset(tables, 0, *table_cnt * sizeof(struct table*));

	i =
	off =
	crs = 0;

	/*   more than one table in list   */
	while(i < *table_cnt - 1)
	{
		crs++;
		while(names[crs] != 0 && names[crs] != '~')
			crs++;
		names[crs] = 0;
		tables[i] = lookup_table(&names[off]);
		if(!tables[i])
			goto return_fail;
		off = crs + 1;
		i++;
	}
	tables[i] = lookup_table(&names[off]);
	if(!tables[i])
		goto return_fail;

	FREE(names);
	return tables;

	return_fail:
	FREE(names);
	FREE(tables);
	*table_cnt = 0;
	return NULL;
}

/******************************************************************************/

static struct conversion* find_conversion(const char *file_name)
{
	struct conversion *conversion;

	conversion = conversion_list;
	while(conversion)
	{
		if(!strcmp(file_name, conversion->file_name))
			return conversion;
		conversion = conversion->nxt;
	}
	return NULL;
}

struct conversion* lookup_conversion(const char *file_name)
{
	struct conversion *conversion;
	char path[PATH_NAME_MAX], *paths;
	int file_name_len, paths_len, len;

	ASSERT(file_name)

	file_name_len = strlen(file_name);

	/*   has conversion already been loaded   */
	conversion = find_conversion(file_name);
	if(conversion)
		return conversion;

	/*   try lookup hook   */
	if(lookup_hook)
	if(lookup_hook(path, PATH_NAME_MAX, file_name, file_name_len))
	{
		conversion = find_conversion(path);
		if(conversion)
			return conversion;
		conversion = conversion_compile_from_file(path);
		if(conversion)
			goto return_conversion;
	}

	/*   try file_name directly   */
	conversion = conversion_compile_from_file(file_name);
	if(conversion)
		goto return_conversion;

	/*   assume file_name is a base name   */
	check_env();
	if(table_paths)
	{
		paths = table_paths;
		paths_len = table_paths_len;
		while(len = create_path_file_name(path, PATH_NAME_MAX - 1, paths, paths_len, file_name, file_name_len))
		{
			conversion = find_conversion(path);
			if(conversion)
				return conversion;
			conversion = conversion_compile_from_file(path);
			if(conversion)
				goto return_conversion;

			len++;
			paths = &paths[len];
			paths_len -= len;
		}
	}

	log_message(LOG_ERROR, "unable to open conversion %s", file_name);
	return NULL;

	return_conversion:
	conversion->nxt = conversion_list;
	conversion_list = conversion;
	return conversion;
}

/******************************************************************************/

FILE* lookup_open_file(char *path_name, const int path_name_max, const char *file_name, const char *adjacent_name)
{
	FILE *file;
	char path[PATH_NAME_MAX], *paths;
	int file_name_len, paths_len, len;

	ASSERT(file_name)

	file_name_len = strlen(file_name);

	/*   try lookup hook   */
	if(lookup_hook)
	if(lookup_hook(path, PATH_NAME_MAX, file_name, file_name_len))
	{
		file = fopen(path, "r");
		if(file)
		{
			strncpy(path_name, path, path_name_max);
			path_name[path_name_max - 1] = 0;
			return file;
		}
	}

	/*   try file_name directly   */
	file = fopen(file_name, "r");
	if(file)
	{
		strncpy(path_name, file_name, path_name_max);
		path_name[path_name_max - 1] = 0;
		return file;
	}

	/*   try directory of adjacent_name   */
	if(adjacent_name)
	{
		strncpy(path, adjacent_name, PATH_NAME_MAX);
		paths = strrchr(path, FILE_SEPARATOR_CHAR);
		if(paths)
		{
			paths++;
			if((paths - path) + file_name_len + 1 <= PATH_NAME_MAX)
			{
				strncpy(paths, file_name, file_name_len + 1);
				file = fopen(path, "r");
				if(file)
				{
					strncpy(path_name, path, path_name_max);
					path_name[path_name_max - 1] = 0;
					return file;
				}
			}
		}
	}

	/*   assume file_name is a base name   */
	check_env();
	if(table_paths)
	{
		paths = table_paths;
		paths_len = table_paths_len;
		while(len = create_path_file_name(path, PATH_NAME_MAX - 1, paths, paths_len, file_name, file_name_len))
		{
			file = fopen(path, "r");
			if(file)
			{
				strncpy(path_name, path, path_name_max);
				path_name[path_name_max - 1] = 0;
				return file;
			}

			len++;
			paths = &paths[len];
			paths_len -= len;
		}
	}

	return NULL;
}

/******************************************************************************/
