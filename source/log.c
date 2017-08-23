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
	int len;

	at = strstr(format, "%TOKEN");
	if(at)
	{
		len = at - format;
		strncpy(reformat, format, len);
		utf16le_convert_to_utf8(&reformat[len], LOG_MESSAGE_MAX - len, token, token_len);
		strncpy(&reformat[len + token_len], &format[len + 6], LOG_MESSAGE_MAX - len - 6);
	}
	else
		strncpy(reformat, format, LOG_MESSAGE_MAX);

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
