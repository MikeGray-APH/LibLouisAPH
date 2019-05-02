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

#include "translate.h"
#include "lookup.h"
#include "log.h"

/******************************************************************************/

ATTRIBUTE_DLL_EXPORT
int louis_get_version(char *version, const int version_max)
{
	int version_len;

	version_len = strlen(VERSION);
	if(version_len >= version_max)
		version_len = version_max - 1;
	memcpy(version, VERSION, version_len);
	version[version_len] = 0;
	return version_len;
}

ATTRIBUTE_DLL_EXPORT
void (*louis_get_log_callback(void))(const int level, const char *message)
{
	return log_get_callback();
}

ATTRIBUTE_DLL_EXPORT
void louis_set_log_callback(void (*callback)(const int level, const char *message))
{
	log_set_callback(callback);
}

ATTRIBUTE_DLL_EXPORT
int louis_get_paths(char *paths, const int paths_max)
{
	return lookup_get_paths(paths, paths_max);
}

ATTRIBUTE_DLL_EXPORT
int louis_set_paths(const char *paths)
{
	return lookup_set_paths(paths);
}

ATTRIBUTE_DLL_EXPORT
int louis_add_paths(const char *paths)
{
	return lookup_add_paths(paths);
}

static int lookup_and_translate(
	unichar *dots,
	const int dots_len,
	const unichar *chars,
	const int chars_len,
	const char *table_names,
	const char *conversion_name,
	const enum rule_direction direction,
	int *chars_to_dots_map,
	int *dots_to_chars_map,
	int *cursor)
{
	struct table **tables;
	struct conversion *conversion;
	int status, table_cnt;

	ASSERT(dots)
	ASSERT(dots_len > 0)
	ASSERT(chars)
	ASSERT(chars_len > 0)
	ASSERT(table_names)

	tables = lookup_tables(&table_cnt, table_names);
	if(!tables)
		return 0;

	if(conversion_name)
	{
		conversion = lookup_conversion(conversion_name);
		if(!conversion)
		{
			status = 0;
			goto return_status;
		}
	}
	else
		conversion = NULL;

	status = translate_start(
		dots, dots_len, chars, chars_len,
		(const struct table * const*)tables, table_cnt, conversion, direction,
		chars_to_dots_map, dots_to_chars_map, cursor);

	return_status:
	FREE(tables);
	return status;
}

ATTRIBUTE_DLL_EXPORT
int louis_translate_forward(
	unichar *dots,
	const int dots_len,
	const unichar *chars,
	const int chars_len,
	const char *table_names,
	const char *conversion_name,
	int *chars_to_dots_map,
	int *dots_to_chars_map,
	int *cursor)
{
	return lookup_and_translate(
		dots, dots_len, chars, chars_len,
		table_names, conversion_name, FORWARD,
		chars_to_dots_map, dots_to_chars_map, cursor);
}

ATTRIBUTE_DLL_EXPORT
int louis_translate_backward(
	unichar *chars,
	const int chars_len,
	const unichar *dots,
	const int dots_len,
	const char *table_names,
	const char *conversion_name,
	int *dots_to_chars_map,
	int *chars_to_dots_map,
	int *cursor)
{
	return lookup_and_translate(
		chars, chars_len, dots, dots_len,
		table_names, conversion_name, BACKWARD,
		dots_to_chars_map, chars_to_dots_map, cursor);
}

ATTRIBUTE_DLL_EXPORT
int louis_convert_to(unichar *chars, const int chars_len, const char *conversion_name)
{
	struct conversion *conversion;

	conversion = lookup_conversion(conversion_name);
	if(!conversion)
		return 0;

	conversion_convert_to(chars, chars_len, conversion);
	return 1;
}

ATTRIBUTE_DLL_EXPORT
int louis_convert_from(unichar *dots, const int dots_len, const char *conversion_name)
{
	struct conversion *conversion;

	conversion = lookup_conversion(conversion_name);
	if(!conversion)
		return 0;

	conversion_convert_from(dots, dots_len, conversion);
	return 1;
}

/******************************************************************************/
