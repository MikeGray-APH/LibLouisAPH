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

int test_nemeth(FILE *output);
int test_ueb(FILE *output);

int main(void)
{
	clock_t clock_begin, clock_end;
	int fail_cnt;

	MEM_INIT

	log_set_callback(log_callback);

	fail_cnt = 0;

	clock_begin = clock();

	fail_cnt += test_nemeth(NULL);
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
