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

#ifndef LOOKUP_H
#define LOOKUP_H

#include <stdio.h>

#include "table.h"
#include "conversion.h"

/******************************************************************************/

/* Frees all resources.  Also resets lookup state to the same as when the
 * library was first loaded to allow continued use.
*/
void lookup_fini(void);


/* Returns the hook function for file lookups, or NULL is not set.
*/
int (*lookup_get_hook(void))(char *path, const int path_max, const char *file_name, const int file_name_len);


/* Sets the hook function for file lookups.  Unsets if hook is NULL.
*/
void lookup_set_hook(int (*hook)(char *path, const int path_max, const char *file_name, const int file_name_len));


/* Returns the number of characters in current paths.
*/
int lookup_get_paths_length(void);


/* Copies at most paths_max - 1 of the current paths into path.  The copied
 * paths will be NULL terminated.
 *
 * Returns the number of characters copied.
*/
int lookup_get_paths(char *paths, const int paths_max);


/* Sets the current paths to paths, clearing the previous current paths.
 *
 * Returns the number of characters copied or 0 if an error occurred.
*/
int lookup_set_paths(const char *paths);


/* Appends paths to the current paths using the appropriate path separator fir
 * the system.
 *
 * Returns the length of the current paths.
*/
int lookup_add_paths(const char *paths);


/* Returns an array of tables listed in table_names that are separated with the
 * override character.  The tables in the array wil be in the same order as they
 * are listed.  The number of tables in the array is stored in table_cnt.  Each
 * table name is loaded via the lookup_table function.
 *
 * Returns NULL and stores 0 in table_cnt if an error occurred.
 *
 * IMPORTANT:  While the tables in the array should not be freed, the array
 * itself should be freed when finished using it.
*/
struct table** lookup_tables(int *table_cnt, const char *table_names);


/* Returns a table that was loaded and compiled from the file file_name.
 * Returns NULL if an error occurred.
 *
 * The file_name is first checked to see if the table has already been loaded
 * and compiled.  If not, the file_name alone is tried.  If that fails, then
 * the file_name is checked in each directory listed in the current paths in the
 * order they are listed.
*/
struct table* lookup_table(const char *file_name);


/* Returns a conversion that was loaded and compiled from the file file_name.
 * Returns NULL if an error occurred.
 *
 * The file_name is checked in the same manner as lookup_table.
*/
struct conversion* lookup_conversion(const char *file_name);


/* Returns a FILE* of the file file_name opened for reading, or NULL if the file
 * could not be opened.  At most path_name_max - 1 characters of the full file
 * name that was successfully opened is stored in path_name.
 *
 * First the file_name alone is tried.  If that fails, then if adjacent_name is
 * not NULL, file_name with the dirname of adjacent_name is tried,  If that
 * fails, then the file_name is checked in each directory listed in the current
 * paths in the order they are listed.
*/
FILE* lookup_open_file(char *path_name, const int path_name_max, const char *file_name, const char *adjacent_name);

/******************************************************************************/

#endif /*   LOOKUP_H   */
