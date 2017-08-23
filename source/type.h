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

#ifndef TYPE_H
#define TYPE_H

#include <stdlib.h>

/******************************************************************************/

#ifndef VERSION
#define VERSION "development"
#endif

/******************************************************************************/

#define BIT(b)   (1ul << (b))
#define MAX(x, y) (((x) > (y)) ? (x) : (y))

/******************************************************************************/

/*   specific gnu macros   */
#ifdef __GNUC__

#define ATTRIBUTE_FUNCTION_MALLOC         __attribute__((malloc))
#define ATTRIBUTE_UNUSED                  __attribute__((unused))

#if defined __MINGW32__ || defined __MINGW64__
#define ATTRIBUTE_DLL_EXPORT              __attribute__((dllexport))
#else
#define ATTRIBUTE_DLL_EXPORT              __attribute__((visibility("default")))
#endif

#else

#define ATTRIBUTE_FUNCTION_MALLOC
#define ATTRIBUTE_DLL_EXPORT
#define ATTRIBUTE_UNUSED
#define ATTRIBUTE_DLL_EXPORT

#endif

/******************************************************************************/

/*   macros used for debuging   */
#ifdef DEBUG

#ifndef OUTPUT
#define OUTPUT
#endif

#define ASSERT(b)  { if(!(b)) abort(); }
#define DB_MEMSET(dst, src, sz)   { memset((dst), (src), (sz)); }

#else /*   DEBUG   */

#define ASSERT(b)   {}
#define DB_MEMSET(dst, src, sz)   {}

#endif /*   DEBUG   */

#if 0
#include <stdio.h>
#define PUTS(s)  { puts( #s );   fflush(stdout); }
#define PRINT(s) { printf( #s ); fflush(stdout); }
#define VAR(v,t) { printf( #v " = %" #t "\n", (v)); fflush(stdout); }
#define HERE \
{ \
        printf("--> %s:%i\t%s\n", __FILE__, __LINE__, __func__); \
        fflush(stdout); \
}
#endif

/******************************************************************************/

/*   macros and functions used for debugging memory allocation   */
#ifdef DEBUG_MEMORY

int   mem_init(void);
int   mem_fini(void);
void  mem_check(void *addr, const size_t size, const char *file, const char *function, const int line);
void* mem_alloc(const size_t size, const char *file, const char *function, const int line) ATTRIBUTE_FUNCTION_MALLOC;
void* mem_realloc(void *addr, const size_t size, const char *file, const char *function, const int line) ATTRIBUTE_FUNCTION_MALLOC;
void  mem_free(void *addr, const char *file, const char *function, const int line);

#define MEM_INIT               mem_init();
#define MEM_FINI               mem_fini();
#define MEM_CHECK(addr, size)  mem_check((addr), (size), __FILE__, __func__, __LINE__)
#define MALLOC(size)           mem_alloc((size), __FILE__, __func__, __LINE__)
#define REALLOC(addr, size)    mem_realloc((addr), (size), __FILE__, __func__, __LINE__)
#define FREE(addr)             mem_free((addr), __FILE__, __func__, __LINE__)

#else /*   DEBUG_MEMORY   */

#define MEM_INIT
#define MEM_FINI
#define MEM_CHECK(addr, size)
#define MALLOC(size)           malloc((size))
#define REALLOC(addr, size)    realloc((addr), (size))
#define FREE(addr)             free((addr))

#endif /*   DEBUG_MEMORY   */

/******************************************************************************/

#endif /*   TYPE_H   */
