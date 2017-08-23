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

VERSION := 0.1.0

CC = gcc
CPPFLAGS = -D VERSION=\"$(VERSION)\" -I source -I source/language
CFLAGS = -std="c11"
LDFLAGS =

DLL          := build/liblouisAPH.so
LIB          := build/liblouisAPH.a
LIB-LINUX64  := dists/x86_64-linux/liblouisAPH.a
DLL-LINUX64  := dists/x86_64-linux/liblouisAPH.so
LIB-LINUX32  := dists/i686-linux/liblouisAPH.a
DLL-LINUX32  := dists/i686-linux/liblouisAPH.so
DLL-WIN64    := dists/x86_64-win/liblouisAPH.dll
DLL-WIN32    := dists/i686-win/liblouisAPH.dll
DLL-MAC64    := dists/x86_64-mac/liblouisAPH.dylib
DLL-MAC32    := dists/i386-mac/liblouisAPH.dylib

EXE := exe

OBJS_LIB := \
	build/utf-convert.o \
	build/table.o \
	build/conversion.o \
	build/compile.o \
	build/translate.o \
	build/pattern.o \
	build/lookup.o \
	build/log.o \

OBJ_LIB_IFACE := build/interface.o

OBJS_LANG := \
	build/language/generic-common.o \
	build/language/generic-forward.o \
	build/language/generic-backward.o \

OBJS_OUTPUT := \
	build/output/utf-output.o \
	build/output/pattern-output.o \
	build/output/conversion-output.o \
	build/output/table-output.o \

OBJS_DEBUG := \
	build/debug/debug.o \
	build/debug/memory.o \

OBJ_DEBUG_MAIN := build/debug/main.o

OBJS_TEST := \
	build/test/test.o \
	build/test/library.o \
	build/test/ueb.o \

OBJ_TEST_MAIN := build/test/main.o

OBJ_TEST_LINK := build/test/link.o

OBJS_CONVERT := \
	build/utf-convert.o \
	build/table.o \
	build/compile.o \
	build/pattern.o \
	build/conversion.o \
	build/lookup.o \
	build/log.o \
	build/output/utf-output.o \
	build/output/conversion-output.o \
	build/tools/lou_convert.o \

OBJS_TABLE := \
	build/utf-convert.o \
	build/table.o \
	build/compile.o \
	build/pattern.o \
	build/conversion.o \
	build/lookup.o \
	build/log.o \
	build/output/utf-output.o \
	build/output/pattern-output.o \
	build/output/table-output.o \
	build/output/conversion-output.o \
	build/tools/lou_table.o \

OBJS_TRANSLATE := \
	$(OBJS_LIB) \
	$(OBJS_LANG) \
	build/output/utf-output.o \
	build/tools/lou_translate.o \

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

$(EXE).db: CPPFLAGS += -I source/output -D DEBUG #-D DEBUG_MEMORY
$(EXE).db: CFLAGS += -ggdb $(CWARNS_DEBUG) -fstack-protector
$(EXE).db: $(OBJS_LIB) $(OBJS_LANG) $(OBJS_OUTPUT) $(OBJS_DEBUG) $(OBJ_LIB_IFACE) $(OBJ_DEBUG_MAIN)
	$(CC) -o $(EXE).db $(LDFLAGS) $(OBJS_LIB) $(OBJS_LANG) $(OBJS_OUTPUT) $(OBJS_DEBUG) $(OBJ_LIB_IFACE) $(OBJ_DEBUG_MAIN)

build/%.o: source/%.c | build
	@echo $(CC) $<
	@$(CC) -c -o $@ $(CPPFLAGS) $(CFLAGS) $<

build/language/%.o: source/language/%.c | build/language
	@echo $(CC) $<
	@$(CC) -c -o $@ $(CPPFLAGS) $(CFLAGS) $<

build/output/%.o: source/output/%.c | build/output
	@echo $(CC) $<
	@$(CC) -c -o $@ $(CPPFLAGS) $(CFLAGS) $<

build/debug/%.o: debug/%.c | build/debug
	@echo $(CC) $<
	@$(CC) -c -o $@ $(CPPFLAGS) $(CFLAGS) $<

build/language: | build
	@mkdir -p build/language

build/output: | build
	@mkdir -p build/output

build/debug: | build
	@mkdir -p build/debug

build:
	@mkdir -p build

db: $(EXE).db
	gdb --command=debug/gdb/main.gdb $(EXE).db


build/dll/build/%.o: source/%.c | build/dll/build
	@echo $(CC) $<
	@$(CC) -fpic -c -o $@ $(CPPFLAGS) $(CFLAGS) $<

build/dll/build/language/%.o: source/language/%.c | build/dll/build/language
	@echo $(CC) $<
	@$(CC) -fpic -c -o $@ $(CPPFLAGS) $(CFLAGS) $<

build/dll/build/output/%.o: source/output/%.c | build/dll/build/output
	@echo $(CC) $<
	@$(CC) -fpic -c -o $@ $(CPPFLAGS) $(CFLAGS) $<

build/dll/build/debug/%.o: debug/%.c | build/dll/build/debug
	@echo $(CC) $<
	@$(CC) -fpic -c -o $@ $(CPPFLAGS) $(CFLAGS) $<

build/dll/build/language: | build/dll/build
	@mkdir -p build/dll/build/language

build/dll/build/output: | build/dll/build
	@mkdir -p build/dll/build/output

build/dll/build/debug: | build/dll/build
	@mkdir -p build/dll/build/debug

build/dll/build: | build
	@mkdir -p build/dll/build

dll: $(DLL)

$(DLL): CFLAGS += -fpic -ggdb $(CWARNS_DEBUG) -fstack-protector
$(DLL): $(foreach OBJ, $(OBJS_LIB) $(OBJS_LANG) $(OBJ_LIB_IFACE), build/dll/$(OBJ)) | build
	$(CC) -o $(DLL) -shared $(foreach OBJ, $(OBJS_LIB) $(OBJS_LANG) $(OBJ_LIB_IFACE), build/dll/$(OBJ))

lib: $(LIB)

$(LIB): CFLAGS +=  -ggdb $(CWARNS_DEBUG) -fstack-protector
$(LIB): $(OBJS_LIB) $(OBJS_LANG) $(OBJ_LIB_IFACE) | build
	ar -rcv $(LIB) $(OBJS_LIB) $(OBJS_LANG) $(OBJ_LIB_IFACE)


build/test/%.o: test/%.c | build/test
	@echo $(CC) $<
	@$(CC) -c -o $@ $(CPPFLAGS) $(CFLAGS) $<

build/test: | build
	@mkdir -p build/test

test: CPPFLAGS += -I source/output -D DEBUG #-D DEBUG_MEMORY
test: CFLAGS += -ggdb $(CWARNS_DEBUG) -fstack-protector
test: test-link $(EXE).test
	./$(EXE).test

test-link: CPPFLAGS += -I . -I source/output -D DEBUG #-D DEBUG_MEMORY
test-link: CFLAGS += -ggdb $(CWARNS_DEBUG) -fstack-protector
test-link: LDFLAGS += -L build -llouisAPH
test-link: $(DLL) $(EXE).link
	env LD_LIBRARY_PATH=build ./$(EXE).link

$(EXE).link: $(OBJ_TEST_LINK) | build
	$(CC) -o $(EXE).link $(OBJ_TEST_LINK) $(LDFLAGS)


test-db: CPPFLAGS += -I source/output -D DEBUG #-D DEBUG_MEMORY
test-db: CFLAGS += -ggdb $(CWARNS_DEBUG) -fstack-protector
test-db: $(EXE).test
	gdb --command=debug/gdb/test.gdb $(EXE).test

test-opt: CPPFLAGS += -I source/output -D OUTPUT
test-opt: CFLAGS += -O3 $(CWARNS_OPT)
test-opt: $(EXE).test
	./$(EXE).test

$(EXE).test: $(OBJS_LIB) $(OBJS_LANG) $(OBJS_OUTPUT) $(OBJS_DEBUG) $(OBJS_TEST) $(OBJ_TEST_MAIN) | build
	$(CC) -o $(EXE).test $(LDFLAGS) $(OBJS_LIB) $(OBJS_LANG) $(OBJS_OUTPUT) $(OBJS_DEBUG) $(OBJS_TEST) $(OBJ_TEST_MAIN)


deps: build/Makedeps
	@cat build/Makedeps

build/Makedeps: CPPFLAGS += -I . -I source/output -D OUTPUT
build/Makedeps: | build
	@rm -f build/Makedeps
	@for SRC in `ls source/*.c source/language/*.c source/output/*.c tools/*.c test/*.c debug/*.c`; do \
		BASE=$${SRC##*/}; \
		$(CC) $(CPPFLAGS) -MM $$SRC -MT build/$${BASE%.c}.o >> build/Makedeps; \
	done

-include build/Makedeps


clean: FORCE
	rm -rf build/ $(EXE)*

cleanse: clean
	rm -rf dists/ LibLouisAPH-*.bz2 LibLouisAPH-*.zip LibLouisAPH-*.asc LibLouisAPH-*.sig

.PHONY: db dll lib test test-link test-db test-opt deps clean cleanse

################################################################################

build/tools/%.o: tools/%.c | build/tools
	@echo $(CC) $<
	@$(CC) -c -o $@ $(CPPFLAGS) $(CFLAGS) $<

build/tools:
	@mkdir -p build/tools

tools: CPPFLAGS += -D DEBUG # -D DEBUG_MEMORY
tools: CFLAGS += -ggdb $(CWARNS_DEBUG)
tools: translate table convert

convert: CPPFLAGS += -I source/output -D OUTPUT
convert: build/tools/lou_convert

build/tools/lou_convert: $(OBJS_CONVERT) | build/tools
	$(CC) -o $@ $(LDFLAGS) $(OBJS_CONVERT)

table: CPPFLAGS += -I source/output -D OUTPUT
table: build/tools/lou_table

build/tools/lou_table: $(OBJS_TABLE) | build/tools
	$(CC) -o $@ $(LDFLAGS) $(OBJS_TABLE)

translate: CPPFLAGS += -I source/output -D OUTPUT
translate: build/tools/lou_translate

build/tools/lou_translate: $(OBJS_TRANSLATE) | build/tools
	$(CC) -o $@ $(LDFLAGS) $(OBJS_TRANSLATE)

.PHONY: tools convert table translate

################################################################################

dist:  dist-linux64

dist-linux64: dll-linux64 lib-linux64 translate-linux64 table-linux64 convert-linux64
	cp -R tables/ dists/x86_64-linux/

dll-linux64: $(DLL-LINUX64)

$(DLL-LINUX64): CFLAGS += -O3 -fPIC $(CWARNS_OPT) -fvisibility=hidden
$(DLL-LINUX64): $(foreach OBJ, $(OBJS_LIB) $(OBJS_LANG) $(OBJ_LIB_IFACE), build/dll/$(OBJ)) | dists/x86_64-linux
	$(CC) -o $(DLL-LINUX64) -shared -s -fvisibility=hidden $(foreach OBJ, $(OBJS_LIB) $(OBJS_LANG) $(OBJ_LIB_IFACE), build/dll/$(OBJ))

lib-linux64: $(LIB-LINUX64)

$(LIB-LINUX64): CFLAGS += -O3 $(CWARNS_OPT)
$(LIB-LINUX64): $(OBJS_LIB) $(OBJS_LANG) $(OBJ_LIB_IFACE) | dists/x86_64-linux
	ar -rcv $(LIB-LINUX64) $(OBJS_LIB) $(OBJS_LANG) $(OBJ_LIB_IFACE)

convert-linux64: CPPFLAGS += -I source/output -D OUTPUT
convert-linux64: CFLAGS += -O3 $(CWARNS_OPT)
convert-linux64: dists/x86_64-linux/lou_convert

dists/x86_64-linux/lou_convert: $(OBJS_CONVERT) | build/tools dists/x86_64-linux
	$(CC) -o $@ $(LDFLAGS) $(OBJS_CONVERT)

table-linux64: CPPFLAGS += -I source/output -D OUTPUT
table-linux64: CFLAGS += -O3 $(CWARNS_OPT)
table-linux64: dists/x86_64-linux/lou_table

dists/x86_64-linux/lou_table: $(OBJS_TABLE) | build/tools dists/x86_64-linux
	$(CC) -o $@ $(LDFLAGS) $(OBJS_TABLE)

translate-linux64: CPPFLAGS += -I source/output -D OUTPUT
translate-linux64: CFLAGS += -O3 $(CWARNS_OPT)
translate-linux64: dists/x86_64-linux/lou_translate

dists/x86_64-linux/lou_translate: $(OBJS_TRANSLATE) | build/tools dists/x86_64-linux
	$(CC) -o $@ $(LDFLAGS) $(OBJS_TRANSLATE)

dists/x86_64-linux:
	mkdir -p dists/x86_64-linux

.PHONY: dist dist-linux64 dll-linux64 lib-linux64 convert-linux64 table-linux64 translate-linux64

################################################################################

dist-linux32: dll-linux32 lib-linux32 translate-linux32 table-linux32 convert-linux32
	cp -R tables/ dists/i686-linux/

dll-linux32: $(DLL-LINUX32)

$(DLL-LINUX32): CFLAGS += -m32 -O3 $(CWARNS_OPT)
$(DLL-LINUX32): $(OBJS_LIB) $(OBJS_LANG) $(OBJ_LIB_IFACE) | dists/i686-linux
	$(CC) -m32 -o $(DLL-LINUX32) -shared $(OBJS_LIB) $(OBJS_LANG) $(OBJ_LIB_IFACE)

lib-linux32: $(LIB-LINUX32)

$(LIB-LINUX32): CFLAGS += -m32 -O3 $(CWARNS_OPT)
$(LIB-LINUX32): $(OBJS_LIB) $(OBJS_LANG) $(OBJ_LIB_IFACE) | dists/i686-linux
	ar -rcv $(LIB-LINUX32) $(OBJS_LIB) $(OBJS_LANG) $(OBJ_LIB_IFACE)

convert-linux32: CPPFLAGS += -I source/output -D OUTPUT
convert-linux32: CFLAGS += -m32 -O3 $(CWARNS_OPT)
convert-linux32: dists/i686-linux/lou_convert

dists/i686-linux/lou_convert: $(OBJS_CONVERT) | build/tools dists/i686-linux
	$(CC) -m32 -o $@ $(LDFLAGS) $(OBJS_CONVERT)

table-linux32: CPPFLAGS += -I source/output -D OUTPUT
table-linux32: CFLAGS += -m32 -O3 $(CWARNS_OPT)
table-linux32: dists/i686-linux/lou_table

dists/i686-linux/lou_table: $(OBJS_TABLE) | build/tools dists/i686-linux
	$(CC) -m32 -o $@ $(LDFLAGS) $(OBJS_TABLE)

translate-linux32: CPPFLAGS += -I source/output -D OUTPUT
translate-linux32: CFLAGS += -m32 -O3 $(CWARNS_OPT)
translate-linux32: dists/i686-linux/lou_translate

dists/i686-linux/lou_translate: $(OBJS_TRANSLATE) | build/tools dists/i686-linux
	$(CC) -m32 -o $@ $(LDFLAGS) $(OBJS_TRANSLATE)

dists/i686-linux:
	mkdir -p dists/i686-linux

.PHONY: dist-linux32 dll-linux32 lib-linux32 convert-linux32 table-linux32 translate-linux32

################################################################################

dist-win64: dll-win64 translate-win64 table-win64 convert-win64
	cp -R tables/ dists/x86_64-win/

dll-win64: $(DLL-WIN64)

$(DLL-WIN64): CC = x86_64-w64-mingw32-gcc
$(DLL-WIN64): CFLAGS += -O3 $(CWARNS_OPT)
$(DLL-WIN64): $(OBJS_LIB) $(OBJS_LANG) $(OBJ_LIB_IFACE) | dists/x86_64-win
	$(CC) -o $(DLL-WIN64) -shared $(OBJS_LIB) $(OBJS_LANG) $(OBJ_LIB_IFACE)

convert-win64: CC = x86_64-w64-mingw32-gcc
convert-win64: CPPFLAGS += -I source/output -D OUTPUT
convert-win64: CFLAGS += -O3 $(CWARNS_OPT)
convert-win64: dists/x86_64-win/lou_convert.exe

dists/x86_64-win/lou_convert.exe: $(OBJS_CONVERT) | build/tools dists/x86_64-win
	$(CC) -o $@ $(LDFLAGS) $(OBJS_CONVERT)

table-win64: CC = x86_64-w64-mingw32-gcc
table-win64: CPPFLAGS += -I source/output -D OUTPUT
table-win64: CFLAGS += -O3 $(CWARNS_OPT)
table-win64: dists/x86_64-win/lou_table.exe

dists/x86_64-win/lou_table.exe: $(OBJS_TABLE) | build/tools dists/x86_64-win
	$(CC) -o $@ $(LDFLAGS) $(OBJS_TABLE)

translate-win64: CC = x86_64-w64-mingw32-gcc
translate-win64: CPPFLAGS += -I source/output -D OUTPUT
translate-win64: CFLAGS += -O3 $(CWARNS_OPT)
translate-win64: dists/x86_64-win/lou_translate.exe

dists/x86_64-win/lou_translate.exe: $(OBJS_TRANSLATE) | build/tools dists/x86_64-win
	$(CC) -o $@ $(LDFLAGS) $(OBJS_TRANSLATE)

dists/x86_64-win:
	mkdir -p dists/x86_64-win

.PHONY: dist-win64 dll-win64 convert-win64 table-win64 translate-win64

################################################################################

dist-win32: dll-win32 convert-win32 table-win32 translate-win32
	cp -R tables/ dists/i686-win/

dll-win32: $(DLL-WIN32)

$(DLL-WIN32): CC = i686-w64-mingw32-gcc
$(DLL-WIN32): CFLAGS += -O3 $(CWARNS_OPT)
$(DLL-WIN32): $(OBJS_LIB) $(OBJS_LANG) $(OBJ_LIB_IFACE) | dists/i686-win
	$(CC) -o $(DLL-WIN32) -shared $(OBJS_LIB) $(OBJS_LANG) $(OBJ_LIB_IFACE)

convert-win32: CC = i686-w64-mingw32-gcc
convert-win32: CPPFLAGS += -I source/output -D OUTPUT
convert-win32: CFLAGS = -O3 $(CWARNS_OPT)
convert-win32: dists/i686-win/lou_convert.exe

dists/i686-win/lou_convert.exe: $(OBJS_CONVERT) | build/tools dists/i686-win
	$(CC) -o $@ $(LDFLAGS) $(OBJS_CONVERT)

table-win32: CC = i686-w64-mingw32-gcc
table-win32: CPPFLAGS += -I source/output -D OUTPUT
table-win32: CFLAGS += -O3 $(CWARNS_OPT)
table-win32: dists/i686-win/lou_table.exe

dists/i686-win/lou_table.exe: $(OBJS_TABLE) | build/tools dists/i686-win
	$(CC) -o $@ $(LDFLAGS) $(OBJS_TABLE)

translate-win32: CC = i686-w64-mingw32-gcc
translate-win32: CPPFLAGS += -I source/output -D OUTPUT
translate-win32: CFLAGS += -O3 $(CWARNS_OPT)
translate-win32: dists/i686-win/lou_translate.exe

dists/i686-win/lou_translate.exe: $(OBJS_TRANSLATE) | build/tools dists/i686-win
	$(CC) -o $@ $(LDFLAGS) $(OBJS_TRANSLATE)

dists/i686-win:
	mkdir -p dists/i686-win

.PHONY: dist-win32 dll-win32 convert-win32 table-win32 translate-win32

################################################################################

dist-mac64: dll-mac64 translate-mac64 table-mac64 convert-mac64
	cp -R tables/ dists/x86_64-mac/

dll-mac64: $(DLL-MAC64)

$(DLL-MAC64): CC = x86_64-apple-darwin15-cc
$(DLL-MAC64): CFLAGS += -O3 $(CWARNS_OPT)
$(DLL-MAC64): $(OBJS_LIB) $(OBJS_LANG) $(OBJ_LIB_IFACE) | dists/x86_64-mac
	$(CC) -o $(DLL-MAC64) -shared $(OBJS_LIB) $(OBJS_LANG) $(OBJ_LIB_IFACE)

convert-mac64: CC = x86_64-apple-darwin15-cc
convert-mac64: CPPFLAGS += -I source/output -D OUTPUT
convert-mac64: CFLAGS += -O3 $(CWARNS_OPT)
convert-mac64: dists/x86_64-mac/lou_convert

dists/x86_64-mac/lou_convert: $(OBJS_CONVERT) | build/tools dists/x86_64-mac
	$(CC) -o $@ $(LDFLAGS) $(OBJS_CONVERT)

table-mac64: CC = x86_64-apple-darwin15-cc
table-mac64: CPPFLAGS += -I source/output -D OUTPUT
table-mac64: CFLAGS += -O3 $(CWARNS_OPT)
table-mac64: dists/x86_64-mac/lou_table

dists/x86_64-mac/lou_table: $(OBJS_TABLE) | build/tools dists/x86_64-mac
	$(CC) -o $@ $(LDFLAGS) $(OBJS_TABLE)

translate-mac64: CC = x86_64-apple-darwin15-cc
translate-mac64: CPPFLAGS += -I source/output -D OUTPUT
translate-mac64: CFLAGS += -O3 $(CWARNS_OPT)
translate-mac64: dists/x86_64-mac/lou_translate

dists/x86_64-mac/lou_translate: $(OBJS_TRANSLATE) | build/tools dists/x86_64-mac
	$(CC) -o $@ $(LDFLAGS) $(OBJS_TRANSLATE)

dists/x86_64-mac:
	mkdir -p dists/x86_64-mac

.PHONY: dist-mac64 dll-mac64 convert-mac64 table-mac64 translate-mac64

################################################################################

dist-mac32: dll-mac32 translate-mac32 table-mac32 convert-mac32
	cp -R tables/ dists/i386-mac/

dll-mac32: $(DLL-MAC32)

$(DLL-MAC32): CC = i386-apple-darwin15-cc
$(DLL-MAC32): CFLAGS += -O3 $(CWARNS_OPT)
$(DLL-MAC32): $(OBJS_LIB) $(OBJS_LANG) $(OBJ_LIB_IFACE) | dists/i386-mac
	$(CC) -o $(DLL-MAC32) -shared $(OBJS_LIB) $(OBJS_LANG) $(OBJ_LIB_IFACE)

convert-mac32: CC = i386-apple-darwin15-cc
convert-mac32: CPPFLAGS += -I source/output -D OUTPUT
convert-mac32: CFLAGS += -O3 $(CWARNS_OPT)
convert-mac32: dists/i386-mac/lou_convert

dists/i386-mac/lou_convert: $(OBJS_CONVERT) | build/tools dists/i386-mac
	$(CC) -o $@ $(LDFLAGS) $(OBJS_CONVERT)

table-mac32: CC = i386-apple-darwin15-cc
table-mac32: CPPFLAGS += -I source/output -D OUTPUT
table-mac32: CFLAGS += -O3 $(CWARNS_OPT)
table-mac32: dists/i386-mac/lou_table

dists/i386-mac/lou_table: $(OBJS_TABLE) | build/tools dists/i386-mac
	$(CC) -o $@ $(LDFLAGS) $(OBJS_TABLE)

translate-mac32: CC = i386-apple-darwin15-cc
translate-mac32: CPPFLAGS += -I source/output -D OUTPUT
translate-mac32: CFLAGS += -O3 $(CWARNS_OPT)
translate-mac32: dists/i386-mac/lou_translate

dists/i386-mac/lou_translate: $(OBJS_TRANSLATE) | build/tools dists/i386-mac
	$(CC) -o $@ $(LDFLAGS) $(OBJS_TRANSLATE)

dists/i386-mac:
	mkdir -p dists/i386-mac

.PHONY: dist-mac32 dll-mac32 convert-mac32 table-mac32 translate-mac32

################################################################################

dists: FORCE
	$(MAKE) dist-linux64
	$(MAKE) clean
	$(MAKE) dist-linux32
	$(MAKE) clean
	$(MAKE) dist-win64
	$(MAKE) clean
	$(MAKE) dist-win32
	$(MAKE) clean
	$(MAKE) dist-mac64
	$(MAKE) clean
	$(MAKE) dist-mac32
	$(MAKE) clean

LibLouisAPH-linux64-$(VERSION).tar.bz2:
	rm -rf LibLouisAPH-linux64-$(VERSION)/
	mkdir LibLouisAPH-linux64-$(VERSION)/
	cp -R dists/x86_64-linux/* LibLouisAPH-linux64-$(VERSION)/
	cp LibLouisAPH.h COPYING COPYING.LESSER LibLouisAPH-linux64-$(VERSION)/
	tar jvfc $@ LibLouisAPH-linux64-$(VERSION)/
	rm -rf LibLouisAPH-linux64-$(VERSION)/

LibLouisAPH-linux32-$(VERSION).tar.bz2:
	rm -rf LibLouisAPH-linux32-$(VERSION)/
	mkdir LibLouisAPH-linux32-$(VERSION)/
	cp -R dists/i686-linux/* LibLouisAPH-linux32-$(VERSION)/
	cp LibLouisAPH.h COPYING COPYING.LESSER LibLouisAPH-linux32-$(VERSION)/
	tar jvfc $@ LibLouisAPH-linux32-$(VERSION)/
	rm -rf LibLouisAPH-linux32-$(VERSION)/

LibLouisAPH-win64-$(VERSION).zip:
	rm -rf LibLouisAPH-win64-$(VERSION)/
	mkdir LibLouisAPH-win64-$(VERSION)/
	cp -R dists/x86_64-win/* LibLouisAPH-win64-$(VERSION)/
	cp LibLouisAPH.h COPYING COPYING.LESSER LibLouisAPH-win64-$(VERSION)/
	zip -r -9 $@ LibLouisAPH-win64-$(VERSION)/
	rm -rf LibLouisAPH-win64-$(VERSION)/

LibLouisAPH-win32-$(VERSION).zip:
	rm -rf LibLouisAPH-win32-$(VERSION)/
	mkdir LibLouisAPH-win32-$(VERSION)/
	cp -R dists/i686-win/* LibLouisAPH-win32-$(VERSION)/
	cp LibLouisAPH.h COPYING COPYING.LESSER LibLouisAPH-win32-$(VERSION)/
	zip -r -9 $@ LibLouisAPH-win32-$(VERSION)/
	rm -rf LibLouisAPH-win32-$(VERSION)/

LibLouisAPH-mac64-$(VERSION).zip:
	rm -rf LibLouisAPH-mac64-$(VERSION)/
	mkdir LibLouisAPH-mac64-$(VERSION)/
	cp -R dists/x86_64-mac/* LibLouisAPH-mac64-$(VERSION)/
	cp LibLouisAPH.h COPYING COPYING.LESSER LibLouisAPH-mac64-$(VERSION)/
	zip -r -9 $@ LibLouisAPH-mac64-$(VERSION)/
	rm -rf LibLouisAPH-mac64-$(VERSION)/

LibLouisAPH-mac32-$(VERSION).zip:
	rm -rf LibLouisAPH-mac32-$(VERSION)/
	mkdir LibLouisAPH-mac32-$(VERSION)/
	cp -R dists/i386-mac/* LibLouisAPH-mac32-$(VERSION)/
	cp LibLouisAPH.h COPYING COPYING.LESSER LibLouisAPH-mac32-$(VERSION)/
	zip -r -9 $@ LibLouisAPH-mac32-$(VERSION)/
	rm -rf LibLouisAPH-mac32-$(VERSION)/

LibLouisAPH-source-$(VERSION).zip:
	rm -rf LibLouisAPH-source-$(VERSION)/
	mkdir LibLouisAPH-source-$(VERSION)/
	cp -R debug/ docs/ source/ tables/ test/ tools/ Makefile COPYING COPYING.LESSER README.md LibLouisAPH.h LibLouisAPH-source-$(VERSION)/
	zip -r -9 $@ LibLouisAPH-source-$(VERSION)/
	rm -rf LibLouisAPH-source-$(VERSION)/

releases: cleanse LibLouisAPH-source-$(VERSION).zip dists LibLouisAPH-linux64-$(VERSION).tar.bz2 LibLouisAPH-linux32-$(VERSION).tar.bz2 LibLouisAPH-win64-$(VERSION).zip LibLouisAPH-win32-$(VERSION).zip LibLouisAPH-mac64-$(VERSION).zip LibLouisAPH-mac32-$(VERSION).zip

.PHONY: dists releases

################################################################################

FORCE:
