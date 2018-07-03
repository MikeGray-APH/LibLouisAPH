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
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include "utf-convert.h"
#include "log.h"

/* When defined, log messages will also be outputed to a file with the name of
 * whatever is set to LOG_OUTPUT_TO_FILE.
*/
//#define LOG_OUTPUT_TO_FILE  "llaph.log"

#define LOG_MESSAGE_MAX 0x200

/* Because there is no log_init, this need to be set when library is loaded.
*/
static void (*log_callback)(const int level, const char *message) = NULL;

/******************************************************************************/

void (*log_get_callback(void))(const int level, const char *message)
{
	return log_callback;
}

void log_set_callback(void (*callback)(const int level, const char *message))
{
	log_callback = callback;
}

/******************************************************************************/

void log_message(const enum log_level level, const char *format, ...)
{
	va_list args;
	char message[LOG_MESSAGE_MAX];

#ifdef LOG_OUTPUT_TO_FILE

	FILE *log_file;

	log_file = fopen(LOG_OUTPUT_TO_FILE, "a");
	if(log_file)
	{
		va_start(args, format);
		vfprintf(log_file, format, args);
		fputs("\n", log_file);
		fclose(log_file);
	}

#endif

	if(!log_callback)
		return;

	message[0] = 0;
	va_start(args, format);
	vsnprintf(message, LOG_MESSAGE_MAX, format, args);
	va_end(args);

	log_callback(level, message);
}

void log_message_with_token(const enum log_level level, const Unicode *token, const int token_len, const char *format, ...)
{
	va_list args;
	char message[LOG_MESSAGE_MAX], reformat[LOG_MESSAGE_MAX], *at;
	int format_len, len, crs;

	format_len = strlen(format);
	if(format_len >= LOG_MESSAGE_MAX)
		format_len = LOG_MESSAGE_MAX - 1;

	at = strstr(format, "%TOKEN");
	if(at)
	{
		crs = at - format;
		memcpy(reformat, format, crs);
		len = utf16le_convert_to_utf8(&reformat[crs], LOG_MESSAGE_MAX - crs, token, token_len);
		memcpy(&reformat[crs + len], &format[crs + 6], format_len - crs - 6);
		reformat[(format_len - 6) + len] = 0;
	}
	else
	{
		memcpy(reformat, format, format_len);
		reformat[format_len] = 0;
	}

#ifdef LOG_OUTPUT_TO_FILE

	FILE *log_file;

	log_file = fopen(LOG_OUTPUT_TO_FILE, "a");
	if(log_file)
	{
		va_start(args, format);
		vfprintf(log_file, reformat, args);
		fputs("\n", log_file);
		fclose(log_file);
	}

#endif

	if(!log_callback)
		return;

	message[0] = 0;
	va_start(args, format);
	vsnprintf(message, LOG_MESSAGE_MAX, reformat, args);
	va_end(args);

	log_callback(level, message);
}

/******************************************************************************/
