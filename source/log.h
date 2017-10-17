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

#ifndef LOG_H
#define LOG_H

/******************************************************************************/

/*   must be kept in sync with LibLouisAPH.h   */
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

/* Returns the callback function for log messages, or NULL is not set.
*/
void (*log_get_callback(void))(const int level, const char *message);


/* Sets the callback function for log messages.  Unsets if callback is NULL.
*/
void log_set_callback(void (*callback)(const int level, const char *message));


/* Log message at log_level level.  Formatting with v*printf is used.
*/
void log_message(const enum log_level level, const char *format, ...);


/* Log message at log_level level with token.  Formatting with v*printf is used.
 * Before formatting is done, the string %TOKEN is replaced with the conversion
 * of token to UTF-8.
*/
void log_message_with_token(const enum log_level level, const Unicode *token, const int token_len, const char *format, ...);

/******************************************************************************/

#endif /*   LOG_H   */
