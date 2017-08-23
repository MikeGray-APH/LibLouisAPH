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

#ifndef LIBLOUISAPH_H
#define LIBLOUISAPH_H

/******************************************************************************/

/* Stores at most version_max characters of the version as a string in version.
 * Ensures that the string copied in version is NULL terminated.
*/
int louis_get_version(char *version, const int version_max);


/* Sets the function called whenever a log message is called, or NULL to clear
 * the function.
*/
void louis_set_log_callback(void (*callback)(const int level, const char *message));


/* Copies at most paths_max - 1 of the current paths into paths.  The copied
 * paths will be zero terminated.
 *
 * Returns the number of characters copied.
*/
int louis_get_paths(char *paths, const int paths_max);


/* Sets the current paths to paths.
 *
 * Returns the number of characters copied or 0 if an error occurred.
*/
int louis_set_paths(const char *paths);


/* Appends paths to the current paths using the appropriate path separator
 * for the system.
 *
 * Returns the length of the current paths.
*/
int louis_add_paths(const char *paths);


/* Performs forward translation, using table_names and conversion_name, of at
 * most chars_len of chars and stores at most dots_len of the result in dots.
 *
 * Mappings are stored in chars_to_dots_map and dots_to_chars_map if they both
 * are not NULL.  If only one is NULL, mapping is still not done.
 *
 * Returns the length of the resulting translation, 0 if no processing was done
 * and no translation was performed, and -1 if an error occurred.
*/
int louis_translate_forward(
	unsigned short *dots,
	const int dots_len,
	const unsigned short *chars,
	const int chars_len,
	const char *table_names,
	const char *conversion_name,
	int *chars_to_dots_map,
	int *dots_to_chars_map);


/* Performs backward translation, using table_names and conversion_name, of at
 * most chars_len of chars and stores at most dots_len of the result in dots.
 *
 * Mappings are stored in chars_to_dots_map and dots_to_chars_map if they both
 * are not NULL.  If only one is NULL, mapping is still not done.
 *
 * Returns the length of the resulting translation, 0 if no processing was done
 * and no translation was performed, and -1 if an error occurred.
*/
int louis_translate_backward(
	unsigned short *chars,
	const int chars_len,
	const unsigned short *dots,
	const int dots_len,
	const char *table_names,
	const char *conversion_name,
	int *dots_to_chars_map,
	int *chars_to_dots_map);


/* Converts at most chars_len of chars from text to braille cells using
 * conversion_name.
*/
int louis_convert_to(unsigned short *chars, const int chars_len, const char *conversion_name);


/* Deconverts at most dots_len of dots from braille cells to text using
 * conversion_name.
*/
int louis_convert_from(unsigned short *dots, const int dots_len, const char *conversion_name);

/******************************************************************************/

#endif /*   LIBLOUISAPH_H   */
