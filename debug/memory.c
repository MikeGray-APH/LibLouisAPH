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

/******************************************************************************/

#ifdef DEBUG_MEMORY

static FILE *mem_file;

int mem_init(void)
{
	mem_file = fopen("mem-output.txt", "w");
	return mem_file != NULL;
}

int mem_fini(void)
{
	return fclose(mem_file);
}

void mem_check(void *addr, const size_t size, const char *file, const char *function, const int line)
{
	fprintf(mem_file, "check    %016lx   %8lx   %s:%s:%d\n", (unsigned long)addr, size, file, function, line);
	fflush(mem_file);
}

void* mem_alloc(const size_t size, const char *file, const char *function, const int line)
{
	void *addr;

	addr = malloc(size);
	fprintf(mem_file, "alloc    %016lx   %8lx   %s:%s:%d\n", (unsigned long)addr, size, file, function, line);
	fflush(mem_file);
	return addr;
}

void* mem_realloc(void *addr, const size_t size, const char *file, const char *function, const int line)
{
	fprintf(mem_file, "realloc  %016lx   %8lx   %s:%s:%d\n", (unsigned long)addr, size, file, function, line);
	fflush(mem_file);
	return realloc(addr, size);
}

void mem_free(void *addr, const char *file, const char *function, const int line)
{
	fprintf(mem_file, "free     %016lx              %s:%s:%d\n", (unsigned long)addr, file, function, line);
	fflush(mem_file);
	free(addr);
}

#endif /*   DEBUG_MEMORY   */

/******************************************************************************/
