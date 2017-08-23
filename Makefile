# LibLouisAPH Braille Translation and Back-Translation Library
#
# Copyright (C) 2017 American Printing House for the Blind, Inc. <www.aph.org>
#
# This file is part of LibLouisAPH.
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

################################################################################

VERSION := 0.1.0-dev

CC = gcc

CC_WIN64 := x86_64-w64-mingw32-gcc
CC_WIN32 := i686-w64-mingw32-gcc
CC_MAC64 := x86_64-apple-darwin15-cc
CC_MAC32 := i386-apple-darwin15-cc

CPPFLAGS = -D VERSION=\"$(VERSION)\" -I source -I source/language
CFLAGS = -std="c11"
LDFLAGS =

OBJS_LIB := \
	source/utf-convert.o \
	source/table.o \
	source/conversion.o \
	source/compile.o \
	source/translate.o \
	source/pattern.o \
	source/lookup.o \
	source/log.o \

OBJ_LIB_IFACE := source/interface.o

OBJS_LANG := \
	source/language/generic-common.o \
	source/language/generic-forward.o \
	source/language/generic-backward.o \

OBJS_OUTPUT := \
	source/output/utf-output.o \
	source/output/pattern-output.o \
	source/output/conversion-output.o \
	source/output/table-output.o \

OBJS_DEBUG := \
	debug/debug.o \
	debug/memory.o \

OBJ_DEBUG_MAIN := debug/main.o

OBJS_TEST := \
	test/test.o \
	test/library.o \
	test/ueb.o \

OBJ_TEST_MAIN := test/main.o

OBJ_TEST_LINK := test/link.o

OBJS_CONVERT := \
	source/utf-convert.o \
	source/table.o \
	source/compile.o \
	source/pattern.o \
	source/conversion.o \
	source/lookup.o \
	source/log.o \
	source/output/utf-output.o \
	source/output/conversion-output.o \
	tools/lou_convert.o \

OBJS_TABLE := \
	source/utf-convert.o \
	source/table.o \
	source/compile.o \
	source/pattern.o \
	source/conversion.o \
	source/lookup.o \
	source/log.o \
	source/output/utf-output.o \
	source/output/pattern-output.o \
	source/output/table-output.o \
	source/output/conversion-output.o \
	tools/lou_table.o \

OBJS_TRANSLATE := \
	$(OBJS_LIB) \
	$(OBJS_LANG) \
	source/output/utf-output.o \
	tools/lou_translate.o \

################################################################################

CWARNS_DEBUG := \
	-Wall \
	-Wextra \
	-Wbad-function-cast \
	-Wcast-align \
	-Wcast-qual \
	-Wfloat-equal \
	-Wlogical-op \
	-Wredundant-decls \
	-Wshadow \
	-Wstrict-prototypes \
	-Wundef \
	-Wwrite-strings \
	-Wunused \
	-Wno-parentheses \
	-Wno-unknown-warning-option \
	-Wno-unused-function \
	-Wno-unused-variable \
	-Wno-unused-but-set-variable \

CWARNS_OPT := \
	-Werror \
	-Wall \
	-Wextra \
	-Wbad-function-cast \
	-Wcast-align \
	-Wcast-qual \
	-Wfloat-equal \
	-Wlogical-op \
	-Wredundant-decls \
	-Wshadow \
	-Wstrict-prototypes \
	-Wundef \
	-Wwrite-strings \
	-Wunused \
	-Wno-inline \
	-Wno-parentheses \
	-Wno-unknown-warning-option \

################################################################################

OBJS_DB_BUILD := $(foreach OBJ, $(OBJS_LIB) $(OBJS_LANG) $(OBJS_OUTPUT) $(OBJS_DEBUG) $(OBJ_LIB_IFACE), build/objects/$(OBJ))

build/exe-db: CPPFLAGS += -I source/output -D DEBUG #-D DEBUG_MEMORY
build/exe-db: CFLAGS += -ggdb $(CWARNS_DEBUG) -fstack-protector
build/exe-db: $(OBJS_DB_BUILD) build/objects/$(OBJ_DEBUG_MAIN) | build
	$(CC) -o $@ $(LDFLAGS) $(OBJS_DB_BUILD) build/objects/$(OBJ_DEBUG_MAIN)

db: build/exe-db
	gdb --command=debug/gdb/main.gdb build/exe-db


dll: CFLAGS += -fpic -ggdb $(CWARNS_DEBUG) -fstack-protector
dll: build/liblouisAPH.so

OBJS_DLL_BUILD := $(foreach OBJ, $(OBJS_LIB) $(OBJS_LANG) $(OBJ_LIB_IFACE), build/objects/dll/$(OBJ))

build/liblouisAPH.so: $(OBJS_DLL_BUILD) | build
	$(CC) -o $@ -shared $(OBJS_DLL_BUILD)


lib: CFLAGS += -ggdb $(CWARNS_DEBUG) -fstack-protector
lib: build/liblouisAPH.a

OBJS_LIB_BUILD := $(foreach OBJ, $(OBJS_LIB) $(OBJS_LANG) $(OBJ_LIB_IFACE), build/objects/$(OBJ))

build/liblouisAPH.a: $(OBJS_LIB_BUILD) | build
	ar -rcv $@ $(OBJS_LIB_BUILD)

.PHONY: db dll lib

################################################################################

tools: CPPFLAGS += -D DEBUG # -D DEBUG_MEMORY
tools: CFLAGS += -ggdb $(CWARNS_DEBUG)
tools: translate table convert

convert: CPPFLAGS += -I source/output -D OUTPUT
convert: build/tools/lou_convert

OBJS_CONVERT_BUILD := $(foreach OBJ, $(OBJS_CONVERT), build/objects/$(OBJ))

build/tools/lou_convert: $(OBJS_CONVERT_BUILD) | build/tools
	$(CC) -o $@ $(LDFLAGS) $(OBJS_CONVERT_BUILD)

table: CPPFLAGS += -I source/output -D OUTPUT
table: build/tools/lou_table

OBJS_TABLE_BUILD := $(foreach OBJ, $(OBJS_TABLE), build/objects/$(OBJ))

build/tools/lou_table: $(OBJS_TABLE_BUILD) | build/tools
	$(CC) -o $@ $(LDFLAGS) $(OBJS_TABLE_BUILD)

translate: CPPFLAGS += -I source/output -D OUTPUT
translate: build/tools/lou_translate

OBJS_TRANSLATE_BUILD := $(foreach OBJ, $(OBJS_TRANSLATE), build/objects/$(OBJ))

build/tools/lou_translate: $(OBJS_TRANSLATE_BUILD) | build/tools
	$(CC) -o $@ $(LDFLAGS) $(OBJS_TRANSLATE_BUILD)

build/tools:
	mkdir -p build/tools

.PHONY: tools convert table translate

################################################################################

test: test-lib test-link test-tools

test-lib: CPPFLAGS += -I source/output -D DEBUG #-D DEBUG_MEMORY
test-lib: CFLAGS += -ggdb $(CWARNS_DEBUG) -fstack-protector
test-lib: build/exe-test-db | build/test
	@build/exe-test-db

test-db: CPPFLAGS += -I source/output -D DEBUG #-D DEBUG_MEMORY
test-db: CFLAGS += -ggdb $(CWARNS_DEBUG) -fstack-protector
test-db: build/exe-test-db | build/test
	gdb --command=debug/gdb/test.gdb build/exe-test-db

OBJS_TEST_DB_BUILD := $(foreach OBJ, $(OBJS_LIB) $(OBJS_LANG) $(OBJS_OUTPUT) $(OBJS_DEBUG) $(OBJS_TEST) $(OBJ_TEST_MAIN), build/objects/$(OBJ))

build/exe-test-db: $(OBJS_TEST_DB_BUILD)
	$(CC) -o $@ $(LDFLAGS) $(OBJS_TEST_DB_BUILD)

test-link: CPPFLAGS += -I . -I source/output -D DEBUG #-D DEBUG_MEMORY
test-link: CFLAGS += -ggdb $(CWARNS_DEBUG) -fstack-protector
test-link: LDFLAGS += -L build -llouisAPH
test-link: dll build/exe-test-link | build/test
	@env LD_LIBRARY_PATH=build build/exe-test-link

build/exe-test-link: build/objects/$(OBJ_TEST_LINK)
	$(CC) -o $@ build/objects/$(OBJ_TEST_LINK) $(LDFLAGS)

test-tools: tools | build/test
	@./test/tools.sh

test-opt: CPPFLAGS += -I source/output -D OUTPUT
test-opt: CFLAGS += -O3 $(CWARNS_OPT)
test-opt: build/exe-test-opt | build/test
	@build/exe-test-opt

OBJS_TEST_OPT_BUILD := $(foreach OBJ, $(OBJS_LIB) $(OBJS_LANG) $(OBJS_OUTPUT) $(OBJS_DEBUG) $(OBJS_TEST) $(OBJ_TEST_MAIN), build/objects/opt/$(OBJ))

build/exe-test-opt: $(OBJS_TEST_OPT_BUILD)
	$(CC) -o $@ $(LDFLAGS) $(OBJS_TEST_OPT_BUILD)

build/test:
	mkdir -p build/test

.PHONY: test test-lib test-db test-link test-tools test-opt

################################################################################

dist:  dist-linux64

dist-linux64: dll-linux64 lib-linux64 translate-linux64 table-linux64 convert-linux64

dll-linux64: CFLAGS += -O3 -fPIC $(CWARNS_OPT) -fvisibility=hidden
dll-linux64: dists/x86_64-linux/liblouisAPH-linux64-$(VERSION).so

OBJ_DLL_LINUX64 := $(foreach OBJ, $(OBJS_LIB) $(OBJS_LANG) $(OBJ_LIB_IFACE), dists/objects/x86_64-linux/dll/$(OBJ))

dists/x86_64-linux/liblouisAPH-linux64-$(VERSION).so: $(OBJ_DLL_LINUX64) | dists/x86_64-linux
	$(CC) -o $@ -shared -s -fvisibility=hidden $(OBJ_DLL_LINUX64)

lib-linux64: CFLAGS += -O3 $(CWARNS_OPT)
lib-linux64: dists/x86_64-linux/liblouisAPH-linux64-$(VERSION).a

OBJ_LIB_LINUX64 := $(foreach OBJ, $(OBJS_LIB) $(OBJS_LANG) $(OBJ_LIB_IFACE), dists/objects/x86_64-linux/$(OBJ))

dists/x86_64-linux/liblouisAPH-linux64-$(VERSION).a: $(OBJ_LIB_LINUX64) | dists/x86_64-linux
	ar -rcv $@ $(OBJ_LIB_LINUX64)

convert-linux64: CPPFLAGS += -I source/output -D OUTPUT
convert-linux64: CFLAGS += -O3 $(CWARNS_OPT)
convert-linux64: dists/x86_64-linux/lou_convert

OBJS_CONVERT_LINUX64 := $(foreach OBJ, $(OBJS_CONVERT), dists/objects/x86_64-linux/$(OBJ))

dists/x86_64-linux/lou_convert: $(OBJS_CONVERT_LINUX64) | dists/x86_64-linux
	$(CC) -o $@ $(LDFLAGS) $(OBJS_CONVERT_LINUX64)

table-linux64: CPPFLAGS += -I source/output -D OUTPUT
table-linux64: CFLAGS += -O3 $(CWARNS_OPT)
table-linux64: dists/x86_64-linux/lou_table

OBJS_TABLE_LINUX64 := $(foreach OBJ, $(OBJS_TABLE), dists/objects/x86_64-linux/$(OBJ))

dists/x86_64-linux/lou_table: $(OBJS_TABLE_LINUX64) | dists/x86_64-linux
	$(CC) -o $@ $(LDFLAGS) $(OBJS_TABLE_LINUX64)

translate-linux64: CPPFLAGS += -I source/output -D OUTPUT
translate-linux64: CFLAGS += -O3 $(CWARNS_OPT)
translate-linux64: dists/x86_64-linux/lou_translate

OBJS_TRANSLATE_LINUX64 := $(foreach OBJ, $(OBJS_TRANSLATE), dists/objects/x86_64-linux/$(OBJ))

dists/x86_64-linux/lou_translate: $(OBJS_TRANSLATE_LINUX64) | dists/x86_64-linux
	$(CC) -o $@ $(LDFLAGS) $(OBJS_TRANSLATE_LINUX64)

dists/x86_64-linux:
	mkdir -p dists/x86_64-linux

.PHONY: dist dist-linux64 dll-linux64 lib-linux64 convert-linux64 table-linux64 translate-linux64

################################################################################

dist-linux32: dll-linux32 lib-linux32 translate-linux32 table-linux32 convert-linux32

dll-linux32: CFLAGS += -m32 -O3 $(CWARNS_OPT)
dll-linux32: dists/i686-linux/liblouisAPH-linux32-$(VERSION).so

OBJS_DLL_LINUX32 := $(foreach OBJ, $(OBJS_LIB) $(OBJS_LANG) $(OBJ_LIB_IFACE), dists/objects/i686-linux/$(OBJ))

dists/i686-linux/liblouisAPH-linux32-$(VERSION).so: $(OBJS_DLL_LINUX32) | dists/i686-linux
	$(CC) -m32 -o $@ -shared $(OBJS_DLL_LINUX32)

lib-linux32: CFLAGS += -m32 -O3 $(CWARNS_OPT)
lib-linux32: dists/i686-linux/liblouisAPH-linux32-$(VERSION).a

OBJS_LIB_LINUX32 := $(foreach OBJ, $(OBJS_LIB) $(OBJS_LANG) $(OBJ_LIB_IFACE), dists/objects/i686-linux/$(OBJ))

dists/i686-linux/liblouisAPH-linux32-$(VERSION).a: $(OBJS_LIB_LINUX32) | dists/i686-linux
	ar -rcv $@ $(OBJS_LIB_LINUX32)

convert-linux32: CPPFLAGS += -I source/output -D OUTPUT
convert-linux32: CFLAGS += -m32 -O3 $(CWARNS_OPT)
convert-linux32: dists/i686-linux/lou_convert

OBJS_CONVERT_LINUX32 := $(foreach OBJ, $(OBJS_CONVERT), dists/objects/i686-linux/$(OBJ))

dists/i686-linux/lou_convert: $(OBJS_CONVERT_LINUX32) | dists/i686-linux
	$(CC) -m32 -o $@ $(LDFLAGS) $(OBJS_CONVERT_LINUX32)

table-linux32: CPPFLAGS += -I source/output -D OUTPUT
table-linux32: CFLAGS += -m32 -O3 $(CWARNS_OPT)
table-linux32: dists/i686-linux/lou_table

OBJS_TABLE_LINUX32 := $(foreach OBJ, $(OBJS_TABLE), dists/objects/i686-linux/$(OBJ))

dists/i686-linux/lou_table: $(OBJS_TABLE_LINUX32) | dists/i686-linux
	$(CC) -m32 -o $@ $(LDFLAGS) $(OBJS_TABLE_LINUX32)

translate-linux32: CPPFLAGS += -I source/output -D OUTPUT
translate-linux32: CFLAGS += -m32 -O3 $(CWARNS_OPT)
translate-linux32: dists/i686-linux/lou_translate

OBJS_TRANSLATE_LINUX32 := $(foreach OBJ, $(OBJS_TRANSLATE), dists/objects/i686-linux/$(OBJ))

dists/i686-linux/lou_translate: $(OBJS_TRANSLATE_LINUX32) | dists/i686-linux
	$(CC) -m32 -o $@ $(LDFLAGS) $(OBJS_TRANSLATE_LINUX32)

dists/i686-linux:
	mkdir -p dists/i686-linux

.PHONY: dist-linux32 dll-linux32 lib-linux32 convert-linux32 table-linux32 translate-linux32

################################################################################

dist-win64: dll-win64 translate-win64 table-win64 convert-win64

dll-win64: CC = $(CC_WIN64)
dll-win64: CFLAGS += -O3 $(CWARNS_OPT)
dll-win64: dists/x86_64-win/liblouisAPH-win64-$(VERSION).dll

OBJS_DLL_WIN64 := $(foreach OBJ, $(OBJS_LIB) $(OBJS_LANG) $(OBJ_LIB_IFACE), dists/objects/x86_64-win/$(OBJ))

dists/x86_64-win/liblouisAPH-win64-$(VERSION).dll: $(OBJS_DLL_WIN64) | dists/x86_64-win
	$(CC) -o $@ -shared $(OBJS_DLL_WIN64)

convert-win64: CC = $(CC_WIN64)
convert-win64: CPPFLAGS += -I source/output -D OUTPUT
convert-win64: CFLAGS += -O3 $(CWARNS_OPT)
convert-win64: dists/x86_64-win/lou_convert.exe

OBJS_CONVERT_WIN64 := $(foreach OBJ, $(OBJS_CONVERT), dists/objects/x86_64-win/$(OBJ))

dists/x86_64-win/lou_convert.exe: $(OBJS_CONVERT_WIN64) | dists/x86_64-win
	$(CC) -o $@ $(LDFLAGS) $(OBJS_CONVERT_WIN64)

table-win64: CC = $(CC_WIN64)
table-win64: CPPFLAGS += -I source/output -D OUTPUT
table-win64: CFLAGS += -O3 $(CWARNS_OPT)
table-win64: dists/x86_64-win/lou_table.exe

OBJS_TABLE_WIN64 := $(foreach OBJ, $(OBJS_TABLE), dists/objects/x86_64-win/$(OBJ))

dists/x86_64-win/lou_table.exe: $(OBJS_TABLE_WIN64) | dists/x86_64-win
	$(CC) -o $@ $(LDFLAGS) $(OBJS_TABLE_WIN64)

translate-win64: CC = $(CC_WIN64)
translate-win64: CPPFLAGS += -I source/output -D OUTPUT
translate-win64: CFLAGS += -O3 $(CWARNS_OPT)
translate-win64: dists/x86_64-win/lou_translate.exe

OBJS_TRANSLATE_WIN64 := $(foreach OBJ, $(OBJS_TRANSLATE), dists/objects/x86_64-win/$(OBJ))

dists/x86_64-win/lou_translate.exe: $(OBJS_TRANSLATE_WIN64) | dists/x86_64-win
	$(CC) -o $@ $(LDFLAGS) $(OBJS_TRANSLATE_WIN64)

dists/x86_64-win:
	mkdir -p dists/x86_64-win

.PHONY: dist-win64 dll-win64 convert-win64 table-win64 translate-win64

################################################################################

dist-win32: dll-win32 convert-win32 table-win32 translate-win32

dll-win32: CC = $(CC_WIN32)
dll-win32: CFLAGS += -O3 $(CWARNS_OPT)
dll-win32: dists/i686-win/liblouisAPH-win32-$(VERSION).dll

OBJS_DLL_WIN32 := $(foreach OBJ, $(OBJS_LIB) $(OBJS_LANG) $(OBJ_LIB_IFACE), dists/objects/i686-win/$(OBJ))

dists/i686-win/liblouisAPH-win32-$(VERSION).dll: $(OBJS_DLL_WIN32) | dists/i686-win
	$(CC) -o $@ -shared $(OBJS_DLL_WIN32)

convert-win32: CC = $(CC_WIN32)
convert-win32: CPPFLAGS += -I source/output -D OUTPUT
convert-win32: CFLAGS = -O3 $(CWARNS_OPT)
convert-win32: dists/i686-win/lou_convert.exe

OBJS_CONVERT_WIN32 := $(foreach OBJ, $(OBJS_CONVERT), dists/objects/i686-win/$(OBJ))

dists/i686-win/lou_convert.exe: $(OBJS_CONVERT_WIN32) | dists/i686-win
	$(CC) -o $@ $(LDFLAGS) $(OBJS_CONVERT_WIN32)

table-win32: CC = $(CC_WIN32)
table-win32: CPPFLAGS += -I source/output -D OUTPUT
table-win32: CFLAGS += -O3 $(CWARNS_OPT)
table-win32: dists/i686-win/lou_table.exe

OBJS_TABLE_WIN32 := $(foreach OBJ, $(OBJS_TABLE), dists/objects/i686-win/$(OBJ))

dists/i686-win/lou_table.exe: $(OBJS_TABLE_WIN32) | dists/i686-win
	$(CC) -o $@ $(LDFLAGS) $(OBJS_TABLE_WIN32)

translate-win32: CC = $(CC_WIN32)
translate-win32: CPPFLAGS += -I source/output -D OUTPUT
translate-win32: CFLAGS += -O3 $(CWARNS_OPT)
translate-win32: dists/i686-win/lou_translate.exe

OBJS_TRANSLATE_WIN32 := $(foreach OBJ, $(OBJS_TRANSLATE), dists/objects/i686-win/$(OBJ))

dists/i686-win/lou_translate.exe: $(OBJS_TRANSLATE_WIN32) | dists/i686-win
	$(CC) -o $@ $(LDFLAGS) $(OBJS_TRANSLATE_WIN32)

dists/i686-win:
	mkdir -p dists/i686-win

.PHONY: dist-win32 dll-win32 convert-win32 table-win32 translate-win32

################################################################################

dist-mac64: dll-mac64 translate-mac64 table-mac64 convert-mac64

dll-mac64: CC = $(CC_MAC64)
dll-mac64: CFLAGS += -O3 $(CWARNS_OPT)
dll-mac64: dists/x86_64-mac/liblouisAPH-mac64-$(VERSION).dylib

OBJS_DLL_MAC64 := $(foreach OBJ, $(OBJS_LIB) $(OBJS_LANG) $(OBJ_LIB_IFACE), dists/objects/x86_64-mac/$(OBJ))

dists/x86_64-mac/liblouisAPH-mac64-$(VERSION).dylib: $(OBJS_DLL_MAC64) | dists/x86_64-mac
	$(CC) -o $@ -shared $(OBJS_DLL_MAC64)

convert-mac64: CC = $(CC_MAC64)
convert-mac64: CPPFLAGS += -I source/output -D OUTPUT
convert-mac64: CFLAGS += -O3 $(CWARNS_OPT)
convert-mac64: dists/x86_64-mac/lou_convert

OBJS_CONVERT_MAC64 := $(foreach OBJ, $(OBJS_CONVERT), dists/objects/x86_64-mac/$(OBJ))

dists/x86_64-mac/lou_convert: $(OBJS_CONVERT_MAC64) | dists/x86_64-mac
	$(CC) -o $@ $(LDFLAGS) $(OBJS_CONVERT_MAC64)

table-mac64: CC = $(CC_MAC64)
table-mac64: CPPFLAGS += -I source/output -D OUTPUT
table-mac64: CFLAGS += -O3 $(CWARNS_OPT)
table-mac64: dists/x86_64-mac/lou_table

OBJS_TABLE_MAC64 := $(foreach OBJ, $(OBJS_TABLE), dists/objects/x86_64-mac/$(OBJ))

dists/x86_64-mac/lou_table: $(OBJS_TABLE_MAC64) | dists/x86_64-mac
	$(CC) -o $@ $(LDFLAGS) $(OBJS_TABLE_MAC64)

translate-mac64: CC = $(CC_MAC64)
translate-mac64: CPPFLAGS += -I source/output -D OUTPUT
translate-mac64: CFLAGS += -O3 $(CWARNS_OPT)
translate-mac64: dists/x86_64-mac/lou_translate

OBJS_TRANSLATE_MAC64 := $(foreach OBJ, $(OBJS_TRANSLATE), dists/objects/x86_64-mac/$(OBJ))

dists/x86_64-mac/lou_translate: $(OBJS_TRANSLATE_MAC64) | dists/x86_64-mac
	$(CC) -o $@ $(LDFLAGS) $(OBJS_TRANSLATE_MAC64)

dists/x86_64-mac:
	mkdir -p dists/x86_64-mac

.PHONY: dist-mac64 dll-mac64 convert-mac64 table-mac64 translate-mac64

################################################################################

dist-mac32: dll-mac32 translate-mac32 table-mac32 convert-mac32

dll-mac32: CC = $(CC_MAC32)
dll-mac32: CFLAGS += -O3 $(CWARNS_OPT)
dll-mac32: dists/i386-mac/liblouisAPH-mac32-$(VERSION).dylib

OBJS_DLL_MAC32 := $(foreach OBJ, $(OBJS_LIB) $(OBJS_LANG) $(OBJ_LIB_IFACE), dists/objects/i386-mac/$(OBJ))

dists/i386-mac/liblouisAPH-mac32-$(VERSION).dylib: $(OBJS_DLL_MAC32) | dists/i386-mac
	$(CC) -o $@ -shared $(OBJS_DLL_MAC32)

convert-mac32: CC = $(CC_MAC32)
convert-mac32: CPPFLAGS += -I source/output -D OUTPUT
convert-mac32: CFLAGS += -O3 $(CWARNS_OPT)
convert-mac32: dists/i386-mac/lou_convert

OBJS_CONVERT_MAC32 := $(foreach OBJ, $(OBJS_CONVERT), dists/objects/i386-mac/$(OBJ))

dists/i386-mac/lou_convert: $(OBJS_CONVERT_MAC32) | dists/i386-mac
	$(CC) -o $@ $(LDFLAGS) $(OBJS_CONVERT_MAC32)

table-mac32: CC = $(CC_MAC32)
table-mac32: CPPFLAGS += -I source/output -D OUTPUT
table-mac32: CFLAGS += -O3 $(CWARNS_OPT)
table-mac32: dists/i386-mac/lou_table

OBJS_TABLE_MAC32 := $(foreach OBJ, $(OBJS_TABLE), dists/objects/i386-mac/$(OBJ))

dists/i386-mac/lou_table: $(OBJS_TABLE_MAC32) | dists/i386-mac
	$(CC) -o $@ $(LDFLAGS) $(OBJS_TABLE_MAC32)

translate-mac32: CC = $(CC_MAC32)
translate-mac32: CPPFLAGS += -I source/output -D OUTPUT
translate-mac32: CFLAGS += -O3 $(CWARNS_OPT)
translate-mac32: dists/i386-mac/lou_translate

OBJS_TRANSLATE_MAC32 := $(foreach OBJ, $(OBJS_TRANSLATE), dists/objects/i386-mac/$(OBJ))

dists/i386-mac/lou_translate: $(OBJS_TRANSLATE_MAC32) | dists/i386-mac
	$(CC) -o $@ $(LDFLAGS) $(OBJS_TRANSLATE_MAC32)

dists/i386-mac:
	mkdir -p dists/i386-mac

.PHONY: dist-mac32 dll-mac32 convert-mac32 table-mac32 translate-mac32

################################################################################

MINGW64     := $(shell if (which $(CC_WIN64) &> /dev/null ); then echo 1; else echo 0; fi )
MINGW32     := $(shell if (which $(CC_WIN32) &> /dev/null ); then echo 1; else echo 0; fi )
OSXCROSS64  := $(shell if (which $(CC_MAC64) &> /dev/null ); then echo 1; else echo 0; fi )
OSXCROSS32  := $(shell if (which $(CC_MAC32) &> /dev/null ); then echo 1; else echo 0; fi )

ifeq ($(MINGW64),1)
DISTS_MINGW64     := dist-win64
RELEASES_MINGW64  := dists/LibLouisAPH-win64-$(VERSION).zip
endif

ifeq ($(MINGW32),1)
DISTS_MINGW32     := dist-win32
RELEASES_MINGW32  := dists/LibLouisAPH-win32-$(VERSION).zip
endif

ifeq ($(OSXCROSS64),1)
DISTS_OSXCROSS64     := dist-mac64
RELEASES_OSXCROSS64  := dists/LibLouisAPH-mac64-$(VERSION).zip
endif

ifeq ($(OSXCROSS32),1)
DISTS_OSXCROSS32     := dist-mac32
RELEASES_OSXCROSS32  := dists/LibLouisAPH-mac32-$(VERSION).zip
endif

DISTS     := dist-linux64 dist-linux32 $(DISTS_MINGW64) $(DISTS_MINGW32) $(DISTS_OSXCROSS64) $(DISTS_OSXCROSS32)
RELEASES  := dists/LibLouisAPH-source-$(VERSION).zip dists/LibLouisAPH-linux64-$(VERSION).tar.bz2 dists/LibLouisAPH-linux32-$(VERSION).tar.bz2 $(RELEASES_MINGW64) $(RELEASES_MINGW32) $(RELEASES_OSXCROSS64) $(RELEASES_OSXCROSS32)

dists: $(DISTS)

dists/LibLouisAPH-source-$(VERSION).zip:
	mkdir -p dists/LibLouisAPH-source-$(VERSION)/
	cp -R debug/ docs/ source/ tables/ test/ tools/ Makefile COPYING COPYING.LESSER README.md LibLouisAPH.h dists/LibLouisAPH-source-$(VERSION)/
	cd dists && zip -r -9 LibLouisAPH-source-$(VERSION).zip LibLouisAPH-source-$(VERSION)/

dists/LibLouisAPH-linux64-$(VERSION).tar.bz2:
	mkdir -p dists/LibLouisAPH-linux64-$(VERSION)/
	cp -R dists/x86_64-linux/* dists/LibLouisAPH-linux64-$(VERSION)/
	cp -R tables/ dists/LibLouisAPH-linux64-$(VERSION)/
	cp LibLouisAPH.h COPYING COPYING.LESSER dists/LibLouisAPH-linux64-$(VERSION)/
	cd dists && tar jvfc LibLouisAPH-linux64-$(VERSION).tar.bz2 LibLouisAPH-linux64-$(VERSION)/

dists/LibLouisAPH-linux32-$(VERSION).tar.bz2:
	mkdir -p dists/LibLouisAPH-linux32-$(VERSION)/
	cp -R dists/i686-linux/* dists/LibLouisAPH-linux32-$(VERSION)/
	cp -R tables/ dists/LibLouisAPH-linux32-$(VERSION)/
	cp LibLouisAPH.h COPYING COPYING.LESSER dists/LibLouisAPH-linux32-$(VERSION)/
	cd dists && tar jvfc LibLouisAPH-linux32-$(VERSION).tar.bz2 LibLouisAPH-linux32-$(VERSION)/

dists/LibLouisAPH-win64-$(VERSION).zip:
	mkdir -p dists/LibLouisAPH-win64-$(VERSION)/
	cp -R dists/x86_64-win/* dists/LibLouisAPH-win64-$(VERSION)/
	cp -R tables/ dists/LibLouisAPH-win64-$(VERSION)/
	cp LibLouisAPH.h COPYING COPYING.LESSER dists/LibLouisAPH-win64-$(VERSION)/
	cd dists && zip -r -9 LibLouisAPH-win64-$(VERSION).zip LibLouisAPH-win64-$(VERSION)/

dists/LibLouisAPH-win32-$(VERSION).zip:
	mkdir -p dists/LibLouisAPH-win32-$(VERSION)/
	cp -R dists/i686-win/* dists/LibLouisAPH-win32-$(VERSION)/
	cp -R tables/ dists/LibLouisAPH-win32-$(VERSION)/
	cp LibLouisAPH.h COPYING COPYING.LESSER dists/LibLouisAPH-win32-$(VERSION)/
	cd dists && zip -r -9 LibLouisAPH-win32-$(VERSION).zip LibLouisAPH-win32-$(VERSION)/

dists/LibLouisAPH-mac64-$(VERSION).zip:
	mkdir -p dists/LibLouisAPH-mac64-$(VERSION)/
	cp -R dists/x86_64-mac/* dists/LibLouisAPH-mac64-$(VERSION)/
	cp -R tables/ dists/LibLouisAPH-mac64-$(VERSION)/
	cp LibLouisAPH.h COPYING COPYING.LESSER dists/LibLouisAPH-mac64-$(VERSION)/
	cd dists && zip -r -9 LibLouisAPH-mac64-$(VERSION).zip LibLouisAPH-mac64-$(VERSION)/

dists/LibLouisAPH-mac32-$(VERSION).zip:
	mkdir -p dists/LibLouisAPH-mac32-$(VERSION)/
	cp -R dists/i386-mac/* dists/LibLouisAPH-mac32-$(VERSION)/
	cp -R tables/ dists/LibLouisAPH-mac32-$(VERSION)/
	cp LibLouisAPH.h COPYING COPYING.LESSER dists/LibLouisAPH-mac32-$(VERSION)/
	cd dists && zip -r -9 LibLouisAPH-mac32-$(VERSION).zip LibLouisAPH-mac32-$(VERSION)/


releases: dists $(RELEASES)

.PHONY: dists releases

################################################################################

deps: build/Makedeps
	@cat build/Makedeps

build/Makedeps: CPPFLAGS += -I . -I source/output -D OUTPUT
build/Makedeps: | build
	@for BUILD_DIR in build/objects dists/objects/x86_64-linux dists/objects/i686-linux dists/objects/x86_64-win dists/objects/i686-win dists/objects/x86_64-mac dists/objects/i386-mac ; \
	do \
		echo "#####  $$BUILD_DIR" >> build/Makedeps ; \
		echo >> build/Makedeps ; \
		for DIR in source tools test debug ; \
		do \
			for SRC in `find $$DIR -name '*.c'` ; \
			do \
				$(CC) $(CPPFLAGS) -MM $$SRC -MT $$BUILD_DIR/$${SRC%.c}.o >> build/Makedeps ; \
			done ; \
			for SOURCE_DIR in `find $$DIR -type d` ; \
			do \
				if ( ls $$SOURCE_DIR/*.c &> /dev/null ) ; \
				then \
					printf '\n' >> build/Makedeps ; \
					echo "$$BUILD_DIR/$$SOURCE_DIR/%.o: $$SOURCE_DIR/%.c | $$BUILD_DIR/$$SOURCE_DIR" >> build/Makedeps ; \
					printf '\t@echo $$(CC) $$<\n' >> build/Makedeps ; \
					printf '\t@$$(CC) -c -o $$@ $$(CPPFLAGS) $$(CFLAGS) $$<\n' >> build/Makedeps ; \
					printf '\n' >> build/Makedeps ; \
					echo "$$BUILD_DIR/$$SOURCE_DIR:" >> build/Makedeps ; \
					printf "\tmkdir -p $$BUILD_DIR/$$SOURCE_DIR\n" >> build/Makedeps ; \
					printf '\n' >> build/Makedeps ; \
				fi ; \
			done ; \
		done ; \
	done ; \
	echo "#####  DLL" >> build/Makedeps ; \
	echo >> build/Makedeps ; \
	for BUILD_DIR in build/objects dists/objects/x86_64-linux ; \
	do \
		for SOURCE_DIR in source source/language ; \
		do \
			echo "$$BUILD_DIR/dll/$$SOURCE_DIR/%.o: $$SOURCE_DIR/%.c | $$BUILD_DIR/dll/$$SOURCE_DIR" >> build/Makedeps ; \
			printf '\t@echo $$(CC) $$<\n' >> build/Makedeps ; \
			printf '\t@$$(CC) -c -o $$@ $$(CPPFLAGS) $$(CFLAGS) $$<\n' >> build/Makedeps ; \
			printf '\n' >> build/Makedeps ; \
			echo "$$BUILD_DIR/dll/$$SOURCE_DIR:" >> build/Makedeps ; \
			printf "\tmkdir -p $$BUILD_DIR/dll/$$SOURCE_DIR\n" >> build/Makedeps ; \
			printf '\n' >> build/Makedeps ; \
		done ; \
	done ; \
	echo "#####  OPT" >> build/Makedeps ; \
	echo >> build/Makedeps ; \
	for BUILD_DIR in build/objects ; \
	do \
		for SOURCE_DIR in source source/language source/output debug test ; \
		do \
			echo "$$BUILD_DIR/opt/$$SOURCE_DIR/%.o: $$SOURCE_DIR/%.c | $$BUILD_DIR/opt/$$SOURCE_DIR" >> build/Makedeps ; \
			printf '\t@echo $$(CC) $$<\n' >> build/Makedeps ; \
			printf '\t@$$(CC) -c -o $$@ $$(CPPFLAGS) $$(CFLAGS) $$<\n' >> build/Makedeps ; \
			printf '\n' >> build/Makedeps ; \
			echo "$$BUILD_DIR/opt/$$SOURCE_DIR:" >> build/Makedeps ; \
			printf "\tmkdir -p $$BUILD_DIR/opt/$$SOURCE_DIR\n" >> build/Makedeps ; \
			printf '\n' >> build/Makedeps ; \
		done ; \
	done \


ifneq ($(MAKECMDGOALS),clean)
ifneq ($(MAKECMDGOALS),cleanse)
ifneq ($(MAKECMDGOALS),distclean)
-include build/Makedeps
endif
endif
endif

build:
	mkdir -p build


clean: FORCE
	rm -rf build/

cleanse: clean
	rm -rf dists/

distclean: cleanse

.PHONY: deps clean cleanse distclean

FORCE:

################################################################################
