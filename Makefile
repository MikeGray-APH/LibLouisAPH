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

CPPFLAGS = -D VERSION=\"$(VERSION)\" -I source -I source/languages # -D DEBUG_MEMORY
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
	source/languages/generic-common.o \
	source/languages/generic-forward.o \
	source/languages/generic-backward.o \

OBJS_OUTPUT := \
	source/outputs/utf-output.o \
	source/outputs/pattern-output.o \
	source/outputs/conversion-output.o \
	source/outputs/table-output.o \

OBJS_DEBUG := \
	debug/debug.o \
	debug/memory.o \

OBJ_DEBUG_MAIN := debug/main.o

OBJS_TEST_LIBRARY := \
	test/test.o \
	test/library.o \

OBJS_TEST_LANGUAGES := \
	test/test.o \
	test/languages.o \
	test/languages/ueb.o \

OBJ_TEST_LINK := test/link.o

OBJS_CONVERT := \
	source/utf-convert.o \
	source/table.o \
	source/compile.o \
	source/pattern.o \
	source/conversion.o \
	source/lookup.o \
	source/log.o \
	source/outputs/utf-output.o \
	source/outputs/conversion-output.o \
	tools/lou_convert.o \

OBJS_TABLE := \
	source/utf-convert.o \
	source/table.o \
	source/compile.o \
	source/pattern.o \
	source/conversion.o \
	source/lookup.o \
	source/log.o \
	source/outputs/utf-output.o \
	source/outputs/pattern-output.o \
	source/outputs/table-output.o \
	source/outputs/conversion-output.o \
	tools/lou_table.o \

OBJS_TRANSLATE := \
	$(OBJS_LIB) \
	$(OBJS_LANG) \
	source/outputs/utf-output.o \
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

.PHONY: db dll lib

OBJS_DB_BUILD := $(foreach OBJ, $(OBJS_LIB) $(OBJS_LANG) $(OBJS_OUTPUT) $(OBJS_DEBUG) $(OBJ_DEBUG_MAIN), build/objects/$(OBJ))

build/exe-db: CPPFLAGS += -I source/outputs -D DEBUG
build/exe-db: CFLAGS += -ggdb -fstack-protector $(CWARNS_DEBUG)
build/exe-db: $(OBJS_DB_BUILD) | build
	$(CC) -o $@ $(CFLAGS) $(OBJS_DB_BUILD) $(LDFLAGS)

db: build/exe-db
	gdb --command=debug/gdb/main.gdb build/exe-db

dll: CFLAGS += -ggdb -fstack-protector -fPIC $(CWARNS_DEBUG)
dll: build/liblouisAPH.so

OBJS_DLL_BUILD := $(foreach OBJ, $(OBJS_LIB) $(OBJS_LANG) $(OBJ_LIB_IFACE), build/objects/dll/$(OBJ))

build/liblouisAPH.so: $(OBJS_DLL_BUILD) | build
	$(CC) -o $@ -shared $(CFLAGS) $(OBJS_DLL_BUILD)

lib: CFLAGS += -ggdb -fstack-protector $(CWARNS_DEBUG)
lib: build/liblouisAPH.a

OBJS_LIB_BUILD := $(foreach OBJ, $(OBJS_LIB) $(OBJS_LANG) $(OBJ_LIB_IFACE), build/objects/$(OBJ))

build/liblouisAPH.a: $(OBJS_LIB_BUILD) | build
	ar -rcv $@ $(OBJS_LIB_BUILD)

########################################

.PHONY: tools convert table translate

tools: translate table convert

convert: CPPFLAGS += -I source/outputs -D OUTPUT -D DEBUG
convert: CFLAGS += -ggdb -fstack-protector $(CWARNS_DEBUG)
convert: build/tools/lou_convert

OBJS_CONVERT_BUILD := $(foreach OBJ, $(OBJS_CONVERT), build/objects/$(OBJ))

build/tools/lou_convert: $(OBJS_CONVERT_BUILD) | build/tools
	$(CC) -o $@ $(CFLAGS) $(OBJS_CONVERT_BUILD) $(LDFLAGS)

table: CPPFLAGS += -I source/outputs -D OUTPUT -D DEBUG
table: CFLAGS += -ggdb -fstack-protector $(CWARNS_DEBUG)
table: build/tools/lou_table

OBJS_TABLE_BUILD := $(foreach OBJ, $(OBJS_TABLE), build/objects/$(OBJ))

build/tools/lou_table: $(OBJS_TABLE_BUILD) | build/tools
	$(CC) -o $@ $(CFLAGS) $(OBJS_TABLE_BUILD) $(LDFLAGS)

translate: CPPFLAGS += -I source/outputs -D OUTPUT -D DEBUG
translate: CFLAGS += -ggdb -fstack-protector $(CWARNS_DEBUG)
translate: build/tools/lou_translate

OBJS_TRANSLATE_BUILD := $(foreach OBJ, $(OBJS_TRANSLATE), build/objects/$(OBJ))

build/tools/lou_translate: $(OBJS_TRANSLATE_BUILD) | build/tools
	$(CC) -o $@ $(CFLAGS) $(OBJS_TRANSLATE_BUILD) $(LDFLAGS)

build/tools:
	mkdir -p build/tools/

################################################################################

.PHONY: test test-all test-lib test-db test-langs test-link test-tools test-opt

test: test-lib test-link test-tools

test-all: test test-langs

test-lib: CPPFLAGS += -I source/outputs -D DEBUG
test-lib: CFLAGS += -ggdb -fstack-protector $(CWARNS_DEBUG)
test-lib: build/exe-test-lib
	@build/exe-test-lib

test-db: CPPFLAGS += -I source/outputs -D DEBUG
test-db: CFLAGS += -ggdb -fstack-protector $(CWARNS_DEBUG)
test-db: build/exe-test-lib
	gdb --command=debug/gdb/test.gdb build/exe-test-lib

OBJS_TEST_LIB_BUILD := $(foreach OBJ, $(OBJS_LIB) $(OBJS_LANG) $(OBJS_OUTPUT) $(OBJS_DEBUG) $(OBJS_TEST_LIBRARY), build/objects/$(OBJ))

build/exe-test-lib: $(OBJS_TEST_LIB_BUILD) | build/test
	$(CC) -o $@ $(CFLAGS) $(OBJS_TEST_LIB_BUILD) $(LDFLAGS)

test-link: CPPFLAGS += -I . -I source/outputs -D DEBUG
test-link: CFLAGS += -ggdb -fstack-protector -fPIC $(CWARNS_DEBUG)
test-link: LDFLAGS += -L build -llouisAPH
test-link: build/liblouisAPH.so build/exe-test-link
	@env LD_LIBRARY_PATH=build build/exe-test-link

build/exe-test-link: build/objects/$(OBJ_TEST_LINK)
	$(CC) -o $@ $(CFLAGS) build/objects/$(OBJ_TEST_LINK) $(LDFLAGS)

test-tools: tools | build/test
	@./test/tools.sh

test-langs: CPPFLAGS += -I source/outputs -I test -D DEBUG
test-langs: CFLAGS += -ggdb -fstack-protector $(CWARNS_DEBUG)
test-langs: build/exe-test-langs
	@build/exe-test-langs

OBJS_TEST_LANG_BUILD := $(foreach OBJ, $(OBJS_LIB) $(OBJS_LANG) $(OBJS_OUTPUT) $(OBJS_DEBUG) $(OBJS_TEST_LANGUAGES), build/objects/$(OBJ))

build/exe-test-langs: $(OBJS_TEST_LANG_BUILD) | build/test
	$(CC) -o $@ $(CFLAGS) $(OBJS_TEST_LANG_BUILD) $(LDFLAGS)

test-opt: CPPFLAGS += -I source/outputs -I test -D OUTPUT
test-opt: CFLAGS += -O3 $(CWARNS_OPT)
test-opt: build/exe-test-opt
	@build/exe-test-opt

OBJS_TEST_OPT_BUILD := $(foreach OBJ, $(OBJS_LIB) $(OBJS_LANG) $(OBJS_OUTPUT) $(OBJS_DEBUG) $(OBJS_TEST_LANGUAGES), build/objects/opt/$(OBJ))

build/exe-test-opt: $(OBJS_TEST_OPT_BUILD) | build/test
	$(CC) -o $@ $(CFLAGS) $(OBJS_TEST_OPT_BUILD) $(LDFLAGS)

build/test:
	mkdir -p build/test/

################################################################################

.PHONY: dists releases

########################################

.PHONY: dist dist-linux64 dll-linux64 lib-linux64 convert-linux64 table-linux64 translate-linux64 release-linux64

dist:  dist-linux64

dists: dist-linux64

FILES_LINUX64 := \
	dists/x86_64-linux/liblouisAPH-linux64-$(VERSION).so \
	dists/x86_64-linux/liblouisAPH-linux64-$(VERSION).a \
	dists/x86_64-linux/lou_convert \
	dists/x86_64-linux/lou_table \
	dists/x86_64-linux/lou_translate \

dist-linux64: dll-linux64 lib-linux64 translate-linux64 table-linux64 convert-linux64

dll-linux64: CFLAGS += -O3 -fPIC -fvisibility=hidden $(CWARNS_OPT)
dll-linux64: dists/x86_64-linux/liblouisAPH-linux64-$(VERSION).so

OBJS_DLL_LINUX64 := $(foreach OBJ, $(OBJS_LIB) $(OBJS_LANG) $(OBJ_LIB_IFACE), dists/objects/x86_64-linux/dll/$(OBJ))

dists/x86_64-linux/liblouisAPH-linux64-$(VERSION).so: $(OBJS_DLL_LINUX64) | dists/x86_64-linux
	$(CC) -o $@ -shared -s $(CFLAGS) $(OBJS_DLL_LINUX64)

lib-linux64: CFLAGS += -O3 $(CWARNS_OPT)
lib-linux64: dists/x86_64-linux/liblouisAPH-linux64-$(VERSION).a

OBJS_LIB_LINUX64 := $(foreach OBJ, $(OBJS_LIB) $(OBJS_LANG) $(OBJ_LIB_IFACE), dists/objects/x86_64-linux/$(OBJ))

dists/x86_64-linux/liblouisAPH-linux64-$(VERSION).a: $(OBJS_LIB_LINUX64) | dists/x86_64-linux
	ar -rcv $@ $(OBJS_LIB_LINUX64)

convert-linux64: CPPFLAGS += -I source/outputs -D OUTPUT
convert-linux64: CFLAGS += -O3 $(CWARNS_OPT)
convert-linux64: dists/x86_64-linux/lou_convert

OBJS_CONVERT_LINUX64 := $(foreach OBJ, $(OBJS_CONVERT), dists/objects/x86_64-linux/$(OBJ))

dists/x86_64-linux/lou_convert: $(OBJS_CONVERT_LINUX64) | dists/x86_64-linux
	$(CC) -o $@ $(CFLAGS) $(OBJS_CONVERT_LINUX64) $(LDFLAGS)

table-linux64: CPPFLAGS += -I source/outputs -D OUTPUT
table-linux64: CFLAGS += -O3 $(CWARNS_OPT)
table-linux64: dists/x86_64-linux/lou_table

OBJS_TABLE_LINUX64 := $(foreach OBJ, $(OBJS_TABLE), dists/objects/x86_64-linux/$(OBJ))

dists/x86_64-linux/lou_table: $(OBJS_TABLE_LINUX64) | dists/x86_64-linux
	$(CC) -o $@ $(CFLAGS) $(OBJS_TABLE_LINUX64) $(LDFLAGS)

translate-linux64: CPPFLAGS += -I source/outputs -D OUTPUT
translate-linux64: CFLAGS += -O3 $(CWARNS_OPT)
translate-linux64: dists/x86_64-linux/lou_translate

OBJS_TRANSLATE_LINUX64 := $(foreach OBJ, $(OBJS_TRANSLATE), dists/objects/x86_64-linux/$(OBJ))

dists/x86_64-linux/lou_translate: $(OBJS_TRANSLATE_LINUX64) | dists/x86_64-linux
	$(CC) -o $@ $(CFLAGS) $(OBJS_TRANSLATE_LINUX64) $(LDFLAGS)

dists/x86_64-linux:
	mkdir -p dists/x86_64-linux/

releases: release-linux64

release-linux64: dist-linux64 releases/LibLouisAPH-linux64-$(VERSION).tar.bz2

releases/LibLouisAPH-linux64-$(VERSION).tar.bz2: $(FILES_LINUX64)
	mkdir -p releases/LibLouisAPH-linux64-$(VERSION)/
	cp -R dists/x86_64-linux/* releases/LibLouisAPH-linux64-$(VERSION)/
	cp -R tables/ releases/LibLouisAPH-linux64-$(VERSION)/
	cp LibLouisAPH.h COPYING COPYING.LESSER releases/LibLouisAPH-linux64-$(VERSION)/
	cd releases && tar jvfc LibLouisAPH-linux64-$(VERSION).tar.bz2 LibLouisAPH-linux64-$(VERSION)/

########################################

.PHONY: dist-linux32 dll-linux32 lib-linux32 convert-linux32 table-linux32 translate-linux32

dists: dist-linux32

FILES_LINUX32 := \
	dists/i686-linux/liblouisAPH-linux32-$(VERSION).so \
	dists/i686-linux/liblouisAPH-linux32-$(VERSION).a \
	dists/i686-linux/lou_convert \
	dists/i686-linux/lou_table \
	dists/i686-linux/lou_translate \

dist-linux32: dll-linux32 lib-linux32 translate-linux32 table-linux32 convert-linux32

dll-linux32: CFLAGS += -O3 -m32 $(CWARNS_OPT)
dll-linux32: dists/i686-linux/liblouisAPH-linux32-$(VERSION).so

OBJS_DLL_LINUX32 := $(foreach OBJ, $(OBJS_LIB) $(OBJS_LANG) $(OBJ_LIB_IFACE), dists/objects/i686-linux/$(OBJ))

dists/i686-linux/liblouisAPH-linux32-$(VERSION).so: $(OBJS_DLL_LINUX32) | dists/i686-linux
	$(CC) -o $@ -m32 -shared $(CFLAGS) $(OBJS_DLL_LINUX32)

lib-linux32: CFLAGS += -O3 -m32 $(CWARNS_OPT)
lib-linux32: dists/i686-linux/liblouisAPH-linux32-$(VERSION).a

OBJS_LIB_LINUX32 := $(foreach OBJ, $(OBJS_LIB) $(OBJS_LANG) $(OBJ_LIB_IFACE), dists/objects/i686-linux/$(OBJ))

dists/i686-linux/liblouisAPH-linux32-$(VERSION).a: $(OBJS_LIB_LINUX32) | dists/i686-linux
	ar -rcv $@ $(OBJS_LIB_LINUX32)

convert-linux32: CPPFLAGS += -I source/outputs -D OUTPUT
convert-linux32: CFLAGS += -O3 -m32 $(CWARNS_OPT)
convert-linux32: dists/i686-linux/lou_convert

OBJS_CONVERT_LINUX32 := $(foreach OBJ, $(OBJS_CONVERT), dists/objects/i686-linux/$(OBJ))

dists/i686-linux/lou_convert: $(OBJS_CONVERT_LINUX32) | dists/i686-linux
	$(CC) -o $@ -m32 $(CFLAGS) $(OBJS_CONVERT_LINUX32) $(LDFLAGS)

table-linux32: CPPFLAGS += -I source/outputs -D OUTPUT
table-linux32: CFLAGS += -O3 -m32 $(CWARNS_OPT)
table-linux32: dists/i686-linux/lou_table

OBJS_TABLE_LINUX32 := $(foreach OBJ, $(OBJS_TABLE), dists/objects/i686-linux/$(OBJ))

dists/i686-linux/lou_table: $(OBJS_TABLE_LINUX32) | dists/i686-linux
	$(CC) -o $@ -m32 $(CFLAGS) $(OBJS_TABLE_LINUX32) $(LDFLAGS)

translate-linux32: CPPFLAGS += -I source/outputs -D OUTPUT
translate-linux32: CFLAGS += -O3 -m32 $(CWARNS_OPT)
translate-linux32: dists/i686-linux/lou_translate

OBJS_TRANSLATE_LINUX32 := $(foreach OBJ, $(OBJS_TRANSLATE), dists/objects/i686-linux/$(OBJ))

dists/i686-linux/lou_translate: $(OBJS_TRANSLATE_LINUX32) | dists/i686-linux
	$(CC) -o $@ -m32 $(CFLAGS) $(OBJS_TRANSLATE_LINUX32) $(LDFLAGS)

dists/i686-linux:
	mkdir -p dists/i686-linux/

releases: release-linux32

release-linux32: dist-linux32 releases/LibLouisAPH-linux32-$(VERSION).tar.bz2

releases/LibLouisAPH-linux32-$(VERSION).tar.bz2: $(FILES_LINUX32)
	mkdir -p releases/LibLouisAPH-linux32-$(VERSION)/
	cp -R dists/i686-linux/* releases/LibLouisAPH-linux32-$(VERSION)/
	cp -R tables/ releases/LibLouisAPH-linux32-$(VERSION)/
	cp LibLouisAPH.h COPYING COPYING.LESSER releases/LibLouisAPH-linux32-$(VERSION)/
	cd releases && tar jvfc LibLouisAPH-linux32-$(VERSION).tar.bz2 LibLouisAPH-linux32-$(VERSION)/

########################################

.PHONY: dist-win64 dll-win64 convert-win64 table-win64 translate-win64

HAS_MINGW64 := $(shell if (which $(CC_WIN64) &> /dev/null ); then echo 1; else echo 0; fi )

ifneq ($(HAS_MINGW64),1)

dist-win64 dll-win64 convert-win64 table-win64 translate-win64: FORCE
	@echo missing $(CC_WIN64)

else

dists: dist-win64

FILES_WIN64 := \
	dists/x86_64-win/liblouisAPH-win64-$(VERSION).dll \
	dists/x86_64-win/lou_convert.exe \
	dists/x86_64-win/lou_table.exe \
	dists/x86_64-win/lou_translate.exe \

dist-win64: dll-win64 translate-win64 table-win64 convert-win64

dll-win64: CC = $(CC_WIN64)
dll-win64: CFLAGS += -O3 $(CWARNS_OPT)
dll-win64: dists/x86_64-win/liblouisAPH-win64-$(VERSION).dll

OBJS_DLL_WIN64 := $(foreach OBJ, $(OBJS_LIB) $(OBJS_LANG) $(OBJ_LIB_IFACE), dists/objects/x86_64-win/$(OBJ))

dists/x86_64-win/liblouisAPH-win64-$(VERSION).dll: $(OBJS_DLL_WIN64) | dists/x86_64-win
	$(CC) -o $@ -shared $(CFLAGS) $(OBJS_DLL_WIN64)

convert-win64: CC = $(CC_WIN64)
convert-win64: CPPFLAGS += -I source/outputs -D OUTPUT
convert-win64: CFLAGS += -O3 $(CWARNS_OPT)
convert-win64: dists/x86_64-win/lou_convert.exe

OBJS_CONVERT_WIN64 := $(foreach OBJ, $(OBJS_CONVERT), dists/objects/x86_64-win/$(OBJ))

dists/x86_64-win/lou_convert.exe: $(OBJS_CONVERT_WIN64) | dists/x86_64-win
	$(CC) -o $@ $(CFLAGS) $(OBJS_CONVERT_WIN64) $(LDFLAGS)

table-win64: CC = $(CC_WIN64)
table-win64: CPPFLAGS += -I source/outputs -D OUTPUT
table-win64: CFLAGS += -O3 $(CWARNS_OPT)
table-win64: dists/x86_64-win/lou_table.exe

OBJS_TABLE_WIN64 := $(foreach OBJ, $(OBJS_TABLE), dists/objects/x86_64-win/$(OBJ))

dists/x86_64-win/lou_table.exe: $(OBJS_TABLE_WIN64) | dists/x86_64-win
	$(CC) -o $@ $(CFLAGS) $(OBJS_TABLE_WIN64) $(LDFLAGS)

translate-win64: CC = $(CC_WIN64)
translate-win64: CPPFLAGS += -I source/outputs -D OUTPUT
translate-win64: CFLAGS += -O3 $(CWARNS_OPT)
translate-win64: dists/x86_64-win/lou_translate.exe

OBJS_TRANSLATE_WIN64 := $(foreach OBJ, $(OBJS_TRANSLATE), dists/objects/x86_64-win/$(OBJ))

dists/x86_64-win/lou_translate.exe: $(OBJS_TRANSLATE_WIN64) | dists/x86_64-win
	$(CC) -o $@ $(CFLAGS) $(OBJS_TRANSLATE_WIN64) $(LDFLAGS)

dists/x86_64-win:
	mkdir -p dists/x86_64-win/

releases: release-win64

release-win64: dist-win64 releases/LibLouisAPH-win64-$(VERSION).zip

releases/LibLouisAPH-win64-$(VERSION).zip: $(FILES_WIN64)
	mkdir -p releases/LibLouisAPH-win64-$(VERSION)/
	cp -R dists/x86_64-win/* releases/LibLouisAPH-win64-$(VERSION)/
	cp -R tables/ releases/LibLouisAPH-win64-$(VERSION)/
	cp LibLouisAPH.h COPYING COPYING.LESSER releases/LibLouisAPH-win64-$(VERSION)/
	cd releases && zip -r -9 LibLouisAPH-win64-$(VERSION).zip LibLouisAPH-win64-$(VERSION)/

endif

########################################

.PHONY: dist-win32 dll-win32 convert-win32 table-win32 translate-win32 release-win32

HAS_MINGW32 := $(shell if (which $(CC_WIN32) &> /dev/null ); then echo 1; else echo 0; fi )

ifneq ($(HAS_MINGW32),1)

dist-win32 dll-win32 convert-win32 table-win32 translate-win32 release-win32: FORCE
	@echo missing $(CC_WIN32)

else

dists: dist-win32

FILES_WIN32 := \
	dists/i686-win/liblouisAPH-win32-$(VERSION).dll \
	dists/i686-win/lou_convert.exe \
	dists/i686-win/lou_table.exe \
	dists/i686-win/lou_translate.exe \

dist-win32: dll-win32 convert-win32 table-win32 translate-win32

dll-win32: CC = $(CC_WIN32)
dll-win32: CFLAGS += -O3 $(CWARNS_OPT)
dll-win32: dists/i686-win/liblouisAPH-win32-$(VERSION).dll

OBJS_DLL_WIN32 := $(foreach OBJ, $(OBJS_LIB) $(OBJS_LANG) $(OBJ_LIB_IFACE), dists/objects/i686-win/$(OBJ))

dists/i686-win/liblouisAPH-win32-$(VERSION).dll: $(OBJS_DLL_WIN32) | dists/i686-win
	$(CC) -o $@ -shared $(CFLAGS) $(OBJS_DLL_WIN32)

convert-win32: CC = $(CC_WIN32)
convert-win32: CPPFLAGS += -I source/outputs -D OUTPUT
convert-win32: CFLAGS = -O3 $(CWARNS_OPT)
convert-win32: dists/i686-win/lou_convert.exe

OBJS_CONVERT_WIN32 := $(foreach OBJ, $(OBJS_CONVERT), dists/objects/i686-win/$(OBJ))

dists/i686-win/lou_convert.exe: $(OBJS_CONVERT_WIN32) | dists/i686-win
	$(CC) -o $@ $(CFLAGS) $(OBJS_CONVERT_WIN32) $(LDFLAGS)

table-win32: CC = $(CC_WIN32)
table-win32: CPPFLAGS += -I source/outputs -D OUTPUT
table-win32: CFLAGS += -O3 $(CWARNS_OPT)
table-win32: dists/i686-win/lou_table.exe

OBJS_TABLE_WIN32 := $(foreach OBJ, $(OBJS_TABLE), dists/objects/i686-win/$(OBJ))

dists/i686-win/lou_table.exe: $(OBJS_TABLE_WIN32) | dists/i686-win
	$(CC) -o $@ $(CFLAGS) $(OBJS_TABLE_WIN32) $(LDFLAGS)

translate-win32: CC = $(CC_WIN32)
translate-win32: CPPFLAGS += -I source/outputs -D OUTPUT
translate-win32: CFLAGS += -O3 $(CWARNS_OPT)
translate-win32: dists/i686-win/lou_translate.exe

OBJS_TRANSLATE_WIN32 := $(foreach OBJ, $(OBJS_TRANSLATE), dists/objects/i686-win/$(OBJ))

dists/i686-win/lou_translate.exe: $(OBJS_TRANSLATE_WIN32) | dists/i686-win
	$(CC) -o $@ $(CFLAGS) $(OBJS_TRANSLATE_WIN32) $(LDFLAGS)

dists/i686-win:
	mkdir -p dists/i686-win/

releases: release-win32

release-win32: dist-win32 releases/LibLouisAPH-win32-$(VERSION).zip

releases/LibLouisAPH-win32-$(VERSION).zip: $(FILES_WIN32)
	mkdir -p releases/LibLouisAPH-win32-$(VERSION)/
	cp -R dists/i686-win/* releases/LibLouisAPH-win32-$(VERSION)/
	cp -R tables/ releases/LibLouisAPH-win32-$(VERSION)/
	cp LibLouisAPH.h COPYING COPYING.LESSER releases/LibLouisAPH-win32-$(VERSION)/
	cd releases && zip -r -9 LibLouisAPH-win32-$(VERSION).zip LibLouisAPH-win32-$(VERSION)/

endif

########################################

.PHONY: dist-mac64 dll-mac64 convert-mac64 table-mac64 translate-mac64 release-mac64

HAS_OSXCROSS64 := $(shell if (which $(CC_MAC64) &> /dev/null ); then echo 1; else echo 0; fi )

ifneq ($(HAS_OSXCROSS64),1)

dist-mac64 dll-mac64 convert-mac64 table-mac64 translate-mac64 release-mac64: FORCE
	@echo missing $(CC_MAC64)

else

dists: dist-mac64

FILES_MAC64 := \
	dists/x86_64-mac/liblouisAPH-mac64-$(VERSION).dylib \
	dists/x86_64-mac/lou_convert \
	dists/x86_64-mac/lou_table \
	dists/x86_64-mac/lou_translate \

dist-mac64: dll-mac64 translate-mac64 table-mac64 convert-mac64

dll-mac64: CC = $(CC_MAC64)
dll-mac64: CFLAGS += -O3 $(CWARNS_OPT)
dll-mac64: dists/x86_64-mac/liblouisAPH-mac64-$(VERSION).dylib

OBJS_DLL_MAC64 := $(foreach OBJ, $(OBJS_LIB) $(OBJS_LANG) $(OBJ_LIB_IFACE), dists/objects/x86_64-mac/$(OBJ))

dists/x86_64-mac/liblouisAPH-mac64-$(VERSION).dylib: $(OBJS_DLL_MAC64) | dists/x86_64-mac
	$(CC) -o $@ -shared $(CFLAGS) $(OBJS_DLL_MAC64)

convert-mac64: CC = $(CC_MAC64)
convert-mac64: CPPFLAGS += -I source/outputs -D OUTPUT
convert-mac64: CFLAGS += -O3 $(CWARNS_OPT)
convert-mac64: dists/x86_64-mac/lou_convert

OBJS_CONVERT_MAC64 := $(foreach OBJ, $(OBJS_CONVERT), dists/objects/x86_64-mac/$(OBJ))

dists/x86_64-mac/lou_convert: $(OBJS_CONVERT_MAC64) | dists/x86_64-mac
	$(CC) -o $@ $(CFLAGS) $(OBJS_CONVERT_MAC64) $(LDFLAGS)

table-mac64: CC = $(CC_MAC64)
table-mac64: CPPFLAGS += -I source/outputs -D OUTPUT
table-mac64: CFLAGS += -O3 $(CWARNS_OPT)
table-mac64: dists/x86_64-mac/lou_table

OBJS_TABLE_MAC64 := $(foreach OBJ, $(OBJS_TABLE), dists/objects/x86_64-mac/$(OBJ))

dists/x86_64-mac/lou_table: $(OBJS_TABLE_MAC64) | dists/x86_64-mac
	$(CC) -o $@ $(CFLAGS) $(OBJS_TABLE_MAC64) $(LDFLAGS)

translate-mac64: CC = $(CC_MAC64)
translate-mac64: CPPFLAGS += -I source/outputs -D OUTPUT
translate-mac64: CFLAGS += -O3 $(CWARNS_OPT)
translate-mac64: dists/x86_64-mac/lou_translate

OBJS_TRANSLATE_MAC64 := $(foreach OBJ, $(OBJS_TRANSLATE), dists/objects/x86_64-mac/$(OBJ))

dists/x86_64-mac/lou_translate: $(OBJS_TRANSLATE_MAC64) | dists/x86_64-mac
	$(CC) -o $@ $(CFLAGS) $(OBJS_TRANSLATE_MAC64) $(LDFLAGS)

dists/x86_64-mac:
	mkdir -p dists/x86_64-mac/

releases: release-mac64

release-mac64: dist-mac64 releases/LibLouisAPH-mac64-$(VERSION).zip

releases/LibLouisAPH-mac64-$(VERSION).zip: $(FILES_MAC64)
	mkdir -p releases/LibLouisAPH-mac64-$(VERSION)/
	cp -R dists/x86_64-mac/* releases/LibLouisAPH-mac64-$(VERSION)/
	cp -R tables/ releases/LibLouisAPH-mac64-$(VERSION)/
	cp LibLouisAPH.h COPYING COPYING.LESSER releases/LibLouisAPH-mac64-$(VERSION)/
	cd releases && zip -r -9 LibLouisAPH-mac64-$(VERSION).zip LibLouisAPH-mac64-$(VERSION)/

endif

########################################

.PHONY: dist-mac32 dll-mac32 convert-mac32 table-mac32 translate-mac32

HAS_OSXCROSS32 := $(shell if (which $(CC_MAC32) &> /dev/null ); then echo 1; else echo 0; fi )

ifneq ($(HAS_OSXCROSS32),1)

dist-mac32 dll-mac32 convert-mac32 table-mac32 translate-mac32: FORCE
	@echo missing $(CC_MAC32)

else

dists: dist-mac32

FILES_MAC32 := \
	dists/i386-mac/liblouisAPH-mac32-$(VERSION).dylib \
	dists/i386-mac/lou_convert \
	dists/i386-mac/lou_table \
	dists/i386-mac/lou_translate \

dist-mac32: dll-mac32 translate-mac32 table-mac32 convert-mac32

dll-mac32: CC = $(CC_MAC32)
dll-mac32: CFLAGS += -O3 $(CWARNS_OPT)
dll-mac32: dists/i386-mac/liblouisAPH-mac32-$(VERSION).dylib

OBJS_DLL_MAC32 := $(foreach OBJ, $(OBJS_LIB) $(OBJS_LANG) $(OBJ_LIB_IFACE), dists/objects/i386-mac/$(OBJ))

dists/i386-mac/liblouisAPH-mac32-$(VERSION).dylib: $(OBJS_DLL_MAC32) | dists/i386-mac
	$(CC) -o $@ -shared $(CFLAGS) $(OBJS_DLL_MAC32)

convert-mac32: CC = $(CC_MAC32)
convert-mac32: CPPFLAGS += -I source/outputs -D OUTPUT
convert-mac32: CFLAGS += -O3 $(CWARNS_OPT)
convert-mac32: dists/i386-mac/lou_convert

OBJS_CONVERT_MAC32 := $(foreach OBJ, $(OBJS_CONVERT), dists/objects/i386-mac/$(OBJ))

dists/i386-mac/lou_convert: $(OBJS_CONVERT_MAC32) | dists/i386-mac
	$(CC) -o $@ $(CFLAGS) $(OBJS_CONVERT_MAC32) $(LDFLAGS)

table-mac32: CC = $(CC_MAC32)
table-mac32: CPPFLAGS += -I source/outputs -D OUTPUT
table-mac32: CFLAGS += -O3 $(CWARNS_OPT)
table-mac32: dists/i386-mac/lou_table

OBJS_TABLE_MAC32 := $(foreach OBJ, $(OBJS_TABLE), dists/objects/i386-mac/$(OBJ))

dists/i386-mac/lou_table: $(OBJS_TABLE_MAC32) | dists/i386-mac
	$(CC) -o $@ $(CFLAGS) $(OBJS_TABLE_MAC32) $(LDFLAGS)

translate-mac32: CC = $(CC_MAC32)
translate-mac32: CPPFLAGS += -I source/outputs -D OUTPUT
translate-mac32: CFLAGS += -O3 $(CWARNS_OPT)
translate-mac32: dists/i386-mac/lou_translate

OBJS_TRANSLATE_MAC32 := $(foreach OBJ, $(OBJS_TRANSLATE), dists/objects/i386-mac/$(OBJ))

dists/i386-mac/lou_translate: $(OBJS_TRANSLATE_MAC32) | dists/i386-mac
	$(CC) -o $@ $(CFLAGS) $(OBJS_TRANSLATE_MAC32) $(LDFLAGS)

dists/i386-mac:
	mkdir -p dists/i386-mac/

releases: release-mac32

release-mac32: dist-mac32 releases/LibLouisAPH-mac32-$(VERSION).zip

releases/LibLouisAPH-mac32-$(VERSION).zip: $(FILES_MAC32)
	mkdir -p releases/LibLouisAPH-mac32-$(VERSION)/
	cp -R dists/i386-mac/* releases/LibLouisAPH-mac32-$(VERSION)/
	cp -R tables/ releases/LibLouisAPH-mac32-$(VERSION)/
	cp LibLouisAPH.h COPYING COPYING.LESSER releases/LibLouisAPH-mac32-$(VERSION)/
	cd releases && zip -r -9 LibLouisAPH-mac32-$(VERSION).zip LibLouisAPH-mac32-$(VERSION)/

endif

################################################################################

deps: build/Makedeps
	@cat build/Makedeps

build/Makedeps: CPPFLAGS += -I . -I source/outputs -I test -D OUTPUT
build/Makedeps: | build
	@for BUILD_DIR in dists/objects/x86_64-linux dists/objects/i686-linux dists/objects/x86_64-win dists/objects/i686-win dists/objects/x86_64-mac dists/objects/i386-mac ; \
	do \
		echo "#####  $$BUILD_DIR" >> build/Makedeps ; \
		echo >> build/Makedeps ; \
		for DIR in source tools ; \
		do \
			for SRC in `find $$DIR -name '*.c'` ; \
			do \
				$(CC) -MT $$BUILD_DIR/$${SRC%.c}.o -MM $$SRC $(CPPFLAGS) >> build/Makedeps ; \
			done ; \
			for SOURCE_DIR in `find $$DIR -type d` ; \
			do \
				if ( ls $$SOURCE_DIR/*.c &> /dev/null ) ; \
				then \
					printf '\n' >> build/Makedeps ; \
					echo "$$BUILD_DIR/$$SOURCE_DIR/%.o: $$SOURCE_DIR/%.c | $$BUILD_DIR/$$SOURCE_DIR" >> build/Makedeps ; \
					printf '\t$$(CC) -o $$@ -c $$(CPPFLAGS) $$(CFLAGS) $$< $(LDFLAGS)\n' >> build/Makedeps ; \
					printf '\n' >> build/Makedeps ; \
					echo "$$BUILD_DIR/$$SOURCE_DIR:" >> build/Makedeps ; \
					printf "\tmkdir -p $$BUILD_DIR/$$SOURCE_DIR/\n" >> build/Makedeps ; \
					printf '\n' >> build/Makedeps ; \
				fi ; \
			done ; \
		done ; \
	done ; \
	for BUILD_DIR in build/objects ; \
	do \
		echo "#####  $$BUILD_DIR" >> build/Makedeps ; \
		echo >> build/Makedeps ; \
		for DIR in source tools test debug ; \
		do \
			for SRC in `find $$DIR -name '*.c'` ; \
			do \
				$(CC) -MT $$BUILD_DIR/$${SRC%.c}.o -MM $$SRC $(CPPFLAGS) >> build/Makedeps ; \
			done ; \
			for SOURCE_DIR in `find $$DIR -type d` ; \
			do \
				if ( ls $$SOURCE_DIR/*.c &> /dev/null ) ; \
				then \
					printf '\n' >> build/Makedeps ; \
					echo "$$BUILD_DIR/$$SOURCE_DIR/%.o: $$SOURCE_DIR/%.c | $$BUILD_DIR/$$SOURCE_DIR" >> build/Makedeps ; \
					printf '\t$$(CC) -o $$@ -c $$(CPPFLAGS) $$(CFLAGS) $$< $(LDFLAGS)\n' >> build/Makedeps ; \
					printf '\n' >> build/Makedeps ; \
					echo "$$BUILD_DIR/$$SOURCE_DIR:" >> build/Makedeps ; \
					printf "\tmkdir -p $$BUILD_DIR/$$SOURCE_DIR/\n" >> build/Makedeps ; \
					printf '\n' >> build/Makedeps ; \
				fi ; \
			done ; \
		done ; \
	done ; \
	echo "#####  DLL" >> build/Makedeps ; \
	echo >> build/Makedeps ; \
	for BUILD_DIR in build/objects dists/objects/x86_64-linux ; \
	do \
		for SOURCE_DIR in source source/languages ; \
		do \
			for SRC in `find $$SOURCE_DIR -name '*.c'` ; \
			do \
				$(CC) -MT $$BUILD_DIR/dll/$${SRC%.c}.o -MM $$SRC $(CPPFLAGS) >> build/Makedeps ; \
			done ; \
			printf '\n' >> build/Makedeps ; \
			echo "$$BUILD_DIR/dll/$$SOURCE_DIR/%.o: $$SOURCE_DIR/%.c | $$BUILD_DIR/dll/$$SOURCE_DIR" >> build/Makedeps ; \
			printf '\t$$(CC) -o $$@ -c $$(CPPFLAGS) $$(CFLAGS) $$< $(LDFLAGS)\n' >> build/Makedeps ; \
			printf '\n' >> build/Makedeps ; \
			echo "$$BUILD_DIR/dll/$$SOURCE_DIR:" >> build/Makedeps ; \
			printf "\tmkdir -p $$BUILD_DIR/dll/$$SOURCE_DIR/\n" >> build/Makedeps ; \
			printf '\n' >> build/Makedeps ; \
		done ; \
	done ; \
	echo "#####  OPT" >> build/Makedeps ; \
	echo >> build/Makedeps ; \
	for BUILD_DIR in build/objects ; \
	do \
		for SOURCE_DIR in source source/languages source/outputs debug test test/languages ; \
		do \
			for SRC in `find $$SOURCE_DIR -name '*.c'` ; \
			do \
				$(CC) -MT $$BUILD_DIR/opt/$${SRC%.c}.o -MM $$SRC $(CPPFLAGS) >> build/Makedeps ; \
			done ; \
			printf '\n' >> build/Makedeps ; \
			echo "$$BUILD_DIR/opt/$$SOURCE_DIR/%.o: $$SOURCE_DIR/%.c | $$BUILD_DIR/opt/$$SOURCE_DIR" >> build/Makedeps ; \
			printf '\t$$(CC) -o $$@ -c $$(CPPFLAGS) $$(CFLAGS) $$< $(LDFLAGS)\n' >> build/Makedeps ; \
			printf '\n' >> build/Makedeps ; \
			echo "$$BUILD_DIR/opt/$$SOURCE_DIR:" >> build/Makedeps ; \
			printf "\tmkdir -p $$BUILD_DIR/opt/$$SOURCE_DIR/\n" >> build/Makedeps ; \
			printf '\n' >> build/Makedeps ; \
		done ; \
	done \

build:
	mkdir -p build/

.PHONY: deps

################################################################################

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(MAKECMDGOALS),cleanse)
ifneq ($(MAKECMDGOALS),distclean)
-include build/Makedeps
endif
endif
endif

clean: FORCE
	rm -rf build/

cleanse: clean
	rm -rf dists/
	rm -rf releases/

distclean: cleanse

.PHONY: deps clean cleanse distclean

################################################################################

FORCE:
