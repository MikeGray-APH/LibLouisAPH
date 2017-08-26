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
#include <time.h>

#include "translate.h"
#include "utf-convert.h"
#include "utf-output.h"
#include "log.h"
#include "test.h"

/******************************************************************************/

static void log_callback(const int level, const char *message)
{
	switch(level)
	{
	case LOG_ALL:      fprintf(stderr, "ALL:  ");      break;
	case LOG_TRACE:    fprintf(stderr, "TRACE:  ");    break;
	case LOG_DEBUG:    fprintf(stderr, "DEBUG:  ");    break;
	case LOG_INFO:     fprintf(stderr, "INFO:  ");     break;
	case LOG_WARNING:  fprintf(stderr, "WARNING:  ");  break;
	case LOG_ERROR:    fprintf(stderr, "ERROR:  ");    break;
	case LOG_FATAL:    fprintf(stderr, "FATAL:  ");    break;
	}

	fprintf(stderr, "%s\n", message);
	fflush(stderr);
}

/******************************************************************************/

int test_ueb(FILE *output);

int main(void)
{
	clock_t clock_begin, clock_end;
	int fail_cnt;

	MEM_INIT

	log_set_callback(log_callback);

	fail_cnt = 0;

	clock_begin = clock();

	fail_cnt += test_ueb(NULL);

	clock_end = clock();
	printf("clock:  %lu.%lu\n",
		(clock_end - clock_begin) / CLOCKS_PER_SEC,
		(clock_end - clock_begin) % CLOCKS_PER_SEC);
	puts("");

	if(fail_cnt)
		printf("FAILURES:  %d\n", fail_cnt);

	MEM_FINI

	return fail_cnt;
}

/******************************************************************************/
