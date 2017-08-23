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
