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

#ifndef LOG_H
#define LOG_H

/******************************************************************************/

enum log_level
{
	LOG_ALL = 1,
	LOG_TRACE,
	LOG_DEBUG,
	LOG_INFO,
	LOG_WARNING,
	LOG_ERROR,
	LOG_FATAL,
};

#define LOG_ALLOCATE_FAIL    { log_message(LOG_FATAL, "%s:%d  memory allocation failed", __FILE__, __LINE__); }

#define LOG_ALLOCATE_FAIL_RETURN_NULL(obj) \
{ \
	if((obj) == NULL) \
	{ \
		LOG_ALLOCATE_FAIL \
		return NULL; \
	} \
} \

/******************************************************************************/

/* Log message at log_level level.  Formatting with v*printf is used.
*/
void log_message(const enum log_level level, const char *format, ...);


/* Log message at log_level level with token.  Formatting with v*printf is used.
 * Before formatting is done, the string %TOKEN is replaced with the conversion
 * of token to UTF-8.
*/
void log_message_with_token(const enum log_level level, const Unicode *token, const int token_len, const char *format, ...);


/* Sets the callback function for log messages.  Unsets if callback is NULL.
*/
void log_set_callback(void (*callback)(const int level, const char *message));

/******************************************************************************/

#endif /*   LOG_H   */
