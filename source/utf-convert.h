/*

LibLouisAPH Braille Translation and Back-Translation Library

Copyright (C) 2017 Mike Gray, American Printing House for the Blind, Inc.

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
