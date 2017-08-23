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
#include <string.h>

#include "translate.h"
#include "lookup.h"
#include "log.h"

/******************************************************************************/

ATTRIBUTE_DLL_EXPORT
int louis_get_version(char *version, const int version_max)
{
	strncpy(version, VERSION, version_max);
	version[version_max - 1] = 0;
	return 5;
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
	Unicode *dots,
	const int dots_len,
	const Unicode *chars,
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
			log_message(LOG_ERROR, "unable to open conversion %s\n", conversion_name);
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
	Unicode *dots,
	const int dots_len,
	const Unicode *chars,
	const int chars_len,
	const char *table_names,
	const char *conversion_name,
	int *chars_to_dots_map,
	int *dots_to_chars_map,
	int *cursor)
{
	return lookup_and_translate(dots, dots_len, chars, chars_len,
                                    table_names, conversion_name, FORWARD,
                                    chars_to_dots_map, dots_to_chars_map, cursor);
}

ATTRIBUTE_DLL_EXPORT
int louis_translate_backward(
	Unicode *chars,
	const int chars_len,
	const Unicode *dots,
	const int dots_len,
	const char *table_names,
	const char *conversion_name,
	int *dots_to_chars_map,
	int *chars_to_dots_map,
	int *cursor)
{
	return lookup_and_translate(chars, chars_len, dots, dots_len,
                                    table_names, conversion_name, BACKWARD,
                                    dots_to_chars_map, chars_to_dots_map, cursor);
}

ATTRIBUTE_DLL_EXPORT
int louis_convert_to(Unicode *chars, const int chars_len, const char *conversion_name)
{
	struct conversion *conversion;

	conversion = lookup_conversion(conversion_name);
	if(!conversion)
	{
		log_message(LOG_ERROR, "unable to open conversion %s\n", conversion_name);
		return 0;
	}

	conversion_convert_to(chars, chars_len, conversion);
	return 1;
}

ATTRIBUTE_DLL_EXPORT
int louis_convert_from(Unicode *dots, const int dots_len, const char *conversion_name)
{
	struct conversion *conversion;

	conversion = lookup_conversion(conversion_name);
	if(!conversion)
	{
		log_message(LOG_ERROR, "unable to open conversion %s\n", conversion_name);
		return 0;
	}

	conversion_convert_from(dots, dots_len, conversion);
	return 1;
}

/******************************************************************************/
