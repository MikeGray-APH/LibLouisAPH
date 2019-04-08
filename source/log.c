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

#define LOG_MESSAGE_MAX 0x1000

/* When defined, log messages will also be outputed to a file with the name of
 * whatever is set to LOG_OUTPUT_TO_FILE.
*/
//#define LOG_OUTPUT_TO_FILE  "llaph.log"

/* Because there is no log_init, this need to be set when library is loaded.
*/
static void (*log_callback)(const int level, const char *message) = NULL;

/******************************************************************************/

#ifdef LOG_OUTPUT_TO_FILE

#define OUTPUT_TO_FILE(level, message)   log_output_to_file(level, message);

static void log_output_to_file(const enum log_level level, const char *message)
{
	FILE *log_file;

	log_file = fopen(LOG_OUTPUT_TO_FILE, "a");
	if(log_file)
	{
		switch(level)
		{
		case LOG_ALL:      fprintf(log_file, "ALL:  ");      break;
		case LOG_TRACE:    fprintf(log_file, "TRACE:  ");    break;
		case LOG_DEBUG:    fprintf(log_file, "DEBUG:  ");    break;
		case LOG_INFO:     fprintf(log_file, "INFO:  ");     break;
		case LOG_WARNING:  fprintf(log_file, "WARNING:  ");  break;
		case LOG_ERROR:    fprintf(log_file, "ERROR:  ");    break;
		case LOG_FATAL:    fprintf(log_file, "FATAL:  ");    break;
		}

		fprintf(log_file, "%s\n", message);
		fclose(log_file);
	}
}

#else

#define OUTPUT_TO_FILE(level, message)

#endif

void (*log_get_callback(void))(const int level, const char *message)
{
	return log_callback;
}

void log_set_callback(void (*callback)(const int level, const char *message))
{
	log_callback = callback;
}

/******************************************************************************/

static int convert_number(char *buffer, const int buffer_max, const unsigned int number, const int base)
{
	unsigned int digit;
	char *crs, remain;
	char buf[71];
	int buf_len, cnt;

	crs = buf;
	digit = number;
	buf_len = 0;
	do
	{
		remain = (char)(digit % base);
		*crs++ = (remain < 10) ? remain + '0' : (remain - 10) + 'a';
		buf_len++;
		if(buf_len >= 71)
			break;
 	}
 	while(digit /= base);

 	crs--;
 	for(cnt = 0; cnt < buffer_max - 1; cnt++)
 	{
		buffer[cnt] = *crs;
		crs--;
		if(crs < buf)
			break;
	}
	cnt++;
	buffer[cnt] = 0;

	/*   return buf_len instead of cnt to behave like snprintf   */
	return buf_len;
}

void log_message(const enum log_level level, const char *format, ...)
{
	va_list args;
	char message[LOG_MESSAGE_MAX], *arg_string;
	size_t fcrs, mcrs, len;
	Unicode *arg_uchars, arg_uchar;
	unsigned int arg_unt;
	int arg_int;

	if(!log_callback)
		return;

	memset(message, 0, LOG_MESSAGE_MAX);
	va_start(args, format);
	for(fcrs = mcrs = 0; fcrs < strlen(format) - 1; fcrs++)
	{
		if(format[fcrs] != '%')
			message[mcrs++] = format[fcrs];
		else switch(format[++fcrs])
		{
		case 'd':

			arg_int = va_arg(args, int);
			len = snprintf(&message[mcrs], LOG_MESSAGE_MAX - mcrs, "%d", arg_int);
			mcrs += len;
			break;

		case 'u':

			arg_unt = va_arg(args, int);
			len = snprintf(&message[mcrs], LOG_MESSAGE_MAX - mcrs, "%u", arg_unt);
			mcrs += len;
			break;

		case 'x':

			arg_unt = va_arg(args, int);
			len = snprintf(&message[mcrs], LOG_MESSAGE_MAX - mcrs, "%x", arg_unt);
			mcrs += len;
			break;

		case 'o':

			arg_unt = va_arg(args, int);
			len = snprintf(&message[mcrs], LOG_MESSAGE_MAX - mcrs, "%o", arg_unt);
			mcrs += len;
			break;

		case 'b':

			arg_unt = va_arg(args, int);
			len = convert_number(&message[mcrs], LOG_MESSAGE_MAX - mcrs, arg_unt, 2);
			mcrs += len;
			break;

		case 'c':

			arg_int = va_arg(args, int);
			len = snprintf(&message[mcrs], LOG_MESSAGE_MAX - mcrs, "%c", arg_int);
			mcrs += len;
			break;

		case 's':

			arg_string = va_arg(args, char*);
			len = snprintf(&message[mcrs], LOG_MESSAGE_MAX - mcrs, "%s", arg_string);
			mcrs += len;
			break;

		case 'C':

			arg_uchar = (Unicode)va_arg(args, int);
			len = utf16le_convert_to_utf8(&message[mcrs], LOG_MESSAGE_MAX - mcrs, &arg_uchar, 1);
			mcrs += len;
			break;

		case 'S':

			arg_uchars = (Unicode*)va_arg(args, Unicode*);
			len = 0;
			while(arg_uchars[len])
				len++;
			len = utf16le_convert_to_utf8(&message[mcrs], LOG_MESSAGE_MAX - mcrs, arg_uchars, len);
			mcrs += len;
			break;

		case '#':

			fcrs++;
			if(fcrs >= strlen(format))
			{
				/*   copy last chars to message   */
				message[mcrs++] = format[fcrs - 2];
				message[mcrs++] = format[fcrs - 1];
				break;
			}
			if(format[fcrs] == 'S')
			{
				arg_uchars = (Unicode*)va_arg(args, Unicode*);
				arg_int = va_arg(args, int);
				len = utf16le_convert_to_utf8(&message[mcrs], LOG_MESSAGE_MAX - mcrs, arg_uchars, arg_int);
				mcrs += len;
			}
			else
			{
				snprintf(&message[mcrs], LOG_MESSAGE_MAX - mcrs, ":  ERROR:  unknown specifier %%#%c", format[fcrs]);
				message[LOG_MESSAGE_MAX - 1] = 0;
				goto return_message;
			}
			break;

		default:

			snprintf(&message[mcrs], LOG_MESSAGE_MAX - mcrs, ":  ERROR:  unknown specifier %%%c", format[fcrs]);
			message[LOG_MESSAGE_MAX - 1] = 0;
			goto return_message;
		}

		if(mcrs >= LOG_MESSAGE_MAX - 1)
		{
			mcrs = LOG_MESSAGE_MAX - 1;
			message[mcrs] = 0;
			goto return_message;
		}
	}
	va_end(args);

	/*   copy last char to message   */
	if(fcrs < strlen(format))
	if(mcrs < LOG_MESSAGE_MAX - 1)
		message[mcrs++] = format[fcrs];
	else
		mcrs = LOG_MESSAGE_MAX - 1;
	message[mcrs] = 0;

	return_message:
	OUTPUT_TO_FILE(level, message)
	log_callback(level, message);
}

/******************************************************************************/
