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

#ifndef UTF_CONVERT_H
#define UTF_CONVERT_H

#include "utf.h"

/******************************************************************************/

/* Returns the conversion of at most uchars_len digits to an int.
 *
 * The strtol function is used, with base 0, after a simple conversion is done.
 * The max number of digits allowed is 0xff, greater lengths are truncated.
*/
int utf16_convert_to_int(unichar *uchars, const int uchars_len);


/* Converts escape characters designated with \ in uchars.  Any unspecified
 * character is simply copied.  Stops processing on NULL character or when
 * uchars_len is reached.
 *
 *   \\   back slash (the back slash is not specifically specified)
 *   \n   newline
 *   \r   carriage return
 *   \t   tab
 *   \s   space
 *
 *   \u#### \U#### \x#### \X####   unichar character with hex value ####
 *      #### may contain upper or lower cases abcdef.  The number of digits
 *      must be four.
 *
 * Returns the number of characters stored in uchars.
*/
int utf16_convert_escapes(unichar *uchars, const int uchars_len);


/* Converts cchars_len characters of cchars from UTF8 to UTF16.  Stores at
 * most uchars_max - 1 unichar characters in uchars.  Ensures that uchars is
 * NULL terminated.  Stops processing on NULL character.
 *
 * If cchars_crs is NULL, returns the number of characters stored in uchars, not
 * including the NULL terminator.
 *
 * If cchars_crs is not NULL, returns the total number of characters that
 * would result from the conversion, not including the NULL terminator.  Stores
 * the number of characters read from cchars in cchars_crs.  Note that converted
 * characters are still stored in uchars.
*/
int utf8_convert_to_utf16(unichar *uchars, const int uchars_max, const char *cchars, const int cchars_max, int *cchars_crs);


/* Converts uchars_len characters of uchars from UTF16 to UTF8.  Stores at
 * most cchars_max - 1 characters in cchars.  Ensures that cchars is NULL
 * terminated.  Stops processing on NULL character.
 *
 * If uchars_crs is NULL, returns the number of characters stored in cchars, not
 * including the NULL terminator.
 *
 * If uchars_crs is not NULL, returns the total number of characters that
 * would result from the conversion, not including the NULL terminator.  Stores
 * the number of characters read from uchars in uchars_crs.  Note that converted
 * characters are still stored in cchars.
*/
int utf16_convert_to_utf8(char *cchars, const int cchars_max, const unichar *uchars, const int uchars_max, int *uchars_crs);

/******************************************************************************/

#endif /*   UTF_CONVERT_H   */
