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

#ifndef LIBLOUISAPH_H
#define LIBLOUISAPH_H

/******************************************************************************/

/* Stores at most version_max characters of the version as a string in version.
 * Ensures that the string copied in version is NULL terminated.
*/
int louis_get_version(char *version, const int version_max);


#define LOUIS_LOG_ALL      1
#define LOUIS_LOG_TRACE    2
#define LOUIS_LOG_DEBUG    3
#define LOUIS_LOG_INFO     4
#define LOUIS_LOG_WARNING  5
#define LOUIS_LOG_ERROR    6
#define LOUIS_LOG_FATAL    7


/* Returns the function called whenever a log message is called, or NULL if none
 * is set.
*/
void (*louis_get_log_callback(void))(const int level, const char *message);


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
 * The result is not NULL terminated.
 *
 * Mappings are stored in chars_to_dots_map and dots_to_chars_map if they both
 * are not NULL.  If only one is NULL, mapping is still not done.
 *
 * Returns the length of the resulting forward translation, 0 if no processing
 * was done and no forward translation was performed, and -1 if an error
 * occurred.
*/
int louis_translate_forward(
	unsigned short *dots,
	const int dots_len,
	const unsigned short *chars,
	const int chars_len,
	const char *table_names,
	const char *conversion_name,
	int *chars_to_dots_map,
	int *dots_to_chars_map,
	int *cursor);


/* Performs backward translation, using table_names and conversion_name, of at
 * most dots_len of dots and stores at most chars_len of the result in chars.
 * The result is not NULL terminated.
 *
 * Mappings are stored in dots_to_chars_map and chars_to_dots_map if they both
 * are not NULL.  If only one is NULL, mapping is still not done.
 *
 * Returns the length of the resulting backward translation, 0 if no processing
 * was done and no backward translation was performed, and -1 if an error
 * occurred.
*/
int louis_translate_backward(
	unsigned short *chars,
	const int chars_len,
	const unsigned short *dots,
	const int dots_len,
	const char *table_names,
	const char *conversion_name,
	int *dots_to_chars_map,
	int *chars_to_dots_map,
	int *cursor);


/* Converts at most chars_len of chars from text to braille cells using
 * conversion_name.
 *
 * Returns 1 on successful conversion, 0 otherwise.
*/
int louis_convert_to(unsigned short *chars, const int chars_len, const char *conversion_name);


/* Deconverts at most dots_len of dots from braille cells to text using
 * conversion_name.
 *
 * Returns 1 on successful deconversion, 0 otherwise.
*/
int louis_convert_from(unsigned short *dots, const int dots_len, const char *conversion_name);

/******************************************************************************/

#endif /*   LIBLOUISAPH_H   */
