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
#define VAR(v,t) { printf( "--> " #v " = %" #t "\n", (v)); fflush(stdout); }
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
