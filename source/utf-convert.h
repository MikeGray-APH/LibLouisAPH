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
int utf16le_convert_to_int(Unicode *uchars, const int uchars_len);


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
 *   \u#### \U#### \x#### \X####   Unicode character with hex value ####
 *      #### may contain upper or lower cases abcdef.  The number of digits
 *      must be four.
 *
 * Returns the number of characters stored in uchars.
*/
int utf16le_convert_escapes(Unicode *uchars, const int uchars_len);


/* Converts cchars_len characters of cchars from UTF8 to UTF16LE.  Stores at
 * most uchars_max - 1 Unicode characters in uchars.  Ensures that uchars is
 * NULL terminated.  Stops processing on NULL character.
 *
 * Returns the number of characters stored in uchars, or -1 for UTF8 sequences
 * that refer to Unicode characters greater than 0xffff.
*/
int utf8_convert_to_utf16le(Unicode *uchars, const int uchars_max, const char *cchars, const int cchars_max);


/* Converts uchars_len characters of uchars from UTF16LE to UTF8.  Stores at
 * most cchars_max - 1 characters in cchars.  Ensures that cchars is NULL
 * terminated.  Stops processing on NULL character.
 *
 * Returns the number of characters stored in cchars.
*/
int utf16le_convert_to_utf8(char *cchars, const int cchars_max, const Unicode *uchars, const int uchars_max);

/******************************************************************************/

#endif /*   UTF_CONVERT_H   */
