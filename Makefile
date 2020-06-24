#
#   Copyright 2017 American Printing House for the Blind Inc.
#
#   Licensed under the Apache License, Version 2.0 (the "License");
#   you may not use this file except in compliance with the License.
#   You may obtain a copy of the License at
#
#       http://www.apache.org/licenses/LICENSE-2.0
#
#   Unless required by applicable law or agreed to in writing, software
#   distributed under the License is distributed on an "AS IS" BASIS,
#   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#   See the License for the specific language governing permissions and
#   limitations under the License.
#

################################################################################

VERSION := 0.2.38

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
	source/languages/nemeth-forward.o \

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
	test/languages/ueb-math.o \
	test/languages/nemeth.o \

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

CLASSES_JAR := \
	org/aph/liblouisaph/LogCallback.class \
	org/aph/liblouisaph/LibLouisAPH.class \
	org/aph/liblouisaph/Translation.class \
	org/aph/liblouisaph/MainLogCallback.class \
	org/aph/liblouisaph/Main.class \

SOURCES_JAR := \
	org/aph/liblouisaph/LogCallback.java \
	org/aph/liblouisaph/Translation.java \
	org/aph/liblouisaph/LibLouisAPH.java \
	org/aph/liblouisaph/Main.java \

SOURCES_JAVADOC := \
	org/aph/liblouisaph/LogCallback.java \
	org/aph/liblouisaph/Translation.java \
	org/aph/liblouisaph/LibLouisAPH.java \

TABLES := \
	$(wildcard tables/converted/*.*) \
	$(wildcard tables/*.*) \

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
	-Wno-implicit-fallthrough \
	-Wno-memset-elt-size \
	-Wno-unknown-warning-option \
	-Wno-unused-function \
	-Wno-unused-variable \
	-Wno-unused-but-set-variable \

CWARNS_OPTIMAL := \
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
	-Wno-implicit-fallthrough \
	-Wno-inline \
	-Wno-parentheses \
	-Wno-unknown-warning-option \

################################################################################
#
#   Development
#
################################################################################

.PHONY: db dll lib

OBJS_DB_BUILD := $(foreach OBJ, $(OBJS_LIB) $(OBJS_LANG) $(OBJS_OUTPUT) $(OBJS_DEBUG) $(OBJ_DEBUG_MAIN), build/objects/$(OBJ))

build/exe-db: CPPFLAGS += -I source/outputs -D DEBUG
build/exe-db: CFLAGS += -ggdb -fstack-protector $(CWARNS_DEBUG)
build/exe-db: $(OBJS_DB_BUILD) | build
	$(CC) -o $@ $(CFLAGS) $(OBJS_DB_BUILD) $(LDFLAGS)

db: build/exe-db
	gdb --command=debug/gdb/main.gdb build/exe-db

dll: CPPFLAGS += -D DEBUG
dll: CFLAGS += -ggdb -fstack-protector -fPIC $(CWARNS_DEBUG)
dll: build/liblouisAPH.so

OBJS_DLL_BUILD := $(foreach OBJ, $(OBJS_LIB) $(OBJS_LANG) $(OBJ_LIB_IFACE), build/objects/dll/$(OBJ))

build/liblouisAPH.so: $(OBJS_DLL_BUILD) | build
	$(CC) -o $@ -shared $(CFLAGS) $(OBJS_DLL_BUILD)

lib: CPPFLAGS += -D DEBUG
lib: CFLAGS += -ggdb -fstack-protector $(CWARNS_DEBUG)
lib: build/liblouisAPH.a

OBJS_LIB_BUILD := $(foreach OBJ, $(OBJS_LIB) $(OBJS_LANG) $(OBJ_LIB_IFACE), build/objects/$(OBJ))

build/liblouisAPH.a: $(OBJS_LIB_BUILD) | build
	ar -rcv $@ $(OBJS_LIB_BUILD)

########################################

.PHONY: tools convert table translate

tools: translate table convert

build/tools:
	mkdir -p build/tools/

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

################################################################################

.PHONY: java jar javadoc javadoc-jar sources-jar

#   check for java
ifdef JAVA_HOME
HAS_JAVAC := $(shell if (which javac > /dev/null 2>&1 ); then echo 1; else echo 0; fi )
else
HAS_JAVAC := -1
endif

ifneq ($(HAS_JAVAC),1)

#   output java error message
ifneq ($(HAS_JAVAC),-1)

java: FORCE
	@echo missing javac
	@false

jar: java

else

java: FORCE
	@echo JAVA_HOME not set
	@false

jar: java

endif

else

########################################

#   determine jni include directory
ifdef JAVA_HOME
HAS_WIN32_JNI := $(shell if [ -d $(JAVA_HOME)/include/win32 ] ; then echo 1 ; else echo 0 ; fi )
HAS_DARWIN_JNI := $(shell if [ -d $(JAVA_HOME)/include/darwin ] ; then echo 1 ; else echo 0 ; fi )
else
HAS_WIN32_JNI := -1
HAS_DARWIN_JNI := -1
endif

ifeq ($(HAS_WIN32_JNI),1)
JNI_INCLUDES := -I $(JAVA_HOME)/include -I $(JAVA_HOME)/include/win32
else ifeq ($(HAS_DARWIN_JNI),1)
JNI_INCLUDES := -I $(JAVA_HOME)/include -I $(JAVA_HOME)/include/darwin
else
JNI_INCLUDES := -I $(JAVA_HOME)/include -I $(JAVA_HOME)/include/linux
endif

java: CPPFLAGS += $(JNI_INCLUDES) -I build/java
java: CFLAGS += -ggdb -fstack-protector -fPIC $(CWARNS_DEBUG)
java: build/liblouisAPH-jni.so

build/java:
	mkdir -p build/java/

build/java/org/aph/liblouisaph/LibLouisAPH.class: java/org/aph/liblouisaph/LibLouisAPH.java java/org/aph/liblouisaph/LogCallback.java java/org/aph/liblouisaph/Translation.java | build/java
	javac -d build/java -classpath build/java -sourcepath java $<

build/java/org_aph_liblouisaph_LibLouisAPH.h: | build/java
	javac -h build/java -d build/java -sourcepath java java/org/aph/liblouisaph/LibLouisAPH.java

build/java/interface-jni.o: java/interface-jni.c build/java/org_aph_liblouisaph_LibLouisAPH.h | build/java
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) $< $(LDFLAGS)

OBJS_JNI_BUILD := $(foreach OBJ, $(OBJS_LIB) $(OBJS_LANG), build/objects/dll/$(OBJ))

build/liblouisAPH-jni.so: $(OBJS_JNI_BUILD) build/java/interface-jni.o | build
	$(CC) -o $@ -shared $(CFLAGS) $(OBJS_JNI_BUILD) build/java/interface-jni.o

########################################

jar: CPPFLAGS += $(JNI_INCLUDES) -I build/java
jar: CFLAGS += -ggdb -fstack-protector -fPIC $(CWARNS_DEBUG)
jar: build/LibLouisAPH.jar

build/java/manifest.txt: | build/java
	@echo Implementation-Name: LibLouisAPH >  $@
	@echo Implementation-Version: $(VERSION) >> $@
	@echo Implementation-Vender: American Printing House for the Blind >> $@
	@echo Implementation-URL: www.aph.org >> $@
	@echo Automatic-Module-Name:  org.aph.liblouisaph >> $@
	@echo >> $@

build/java/org/aph/liblouisaph/Main.class: java/org/aph/liblouisaph/Main.java
	javac -d build/java -classpath build/java -sourcepath java $<

build/java/liblouisaph.properties: | build/java
	echo Library-Name=liblouisAPH-jni.so > build/java/liblouisaph.properties
	echo Table-Path=tables >> build/java/liblouisaph.properties

CLASSES_JAR_BUILD  := $(foreach OBJ, $(CLASSES_JAR), -C build/java $(OBJ))
FILES_JAR_BUILD    := -C build liblouisAPH-jni.so -C build/java liblouisaph.properties -C java tables/jar.rst -C java tables/jar.cvt

build/LibLouisAPH.jar: build/java/manifest.txt build/java/liblouisaph.properties build/liblouisAPH-jni.so build/java/org/aph/liblouisaph/Main.class
	jar cfme $@ build/java/manifest.txt org.aph.liblouisaph.Main $(CLASSES_JAR_BUILD) $(FILES_JAR_BUILD) $(TABLES)

########################################

sources-jar: build/LibLouisAPH-sources.jar

build/java/manifest-sources.txt: | build/java
	@echo Implementation-Name: LibLouisAPH sources >  $@
	@echo Implementation-Version: $(VERSION) >> $@
	@echo Implementation-Vender: American Printing House for the Blind >> $@
	@echo Implementation-URL: www.aph.org >> $@
	@echo >> $@

SOURCES_JAR_FILES := $(foreach SRC, $(SOURCES_JAR), java/$(SRC))
SOURCES_JAR_BUILD := $(foreach SRC, $(SOURCES_JAR), -C java $(SRC))

build/LibLouisAPH-sources.jar: build/java/manifest-sources.txt $(SOURCES_JAR_FILES) | build
	jar cfm $@ build/java/manifest-sources.txt $(SOURCES_JAR_BUILD)

javadoc-jar: build/LibLouisAPH-javadoc.jar

javadoc: build/java/javadoc/index.html

build/java/javadoc:
	mkdir -p build/java/javadoc/

SOURCES_JAVADOC_FILES := $(foreach SRC, $(SOURCES_JAVADOC), java/$(SRC))

build/java/javadoc/index.html: $(SOURCES_JAVADOC_FILES) | build/java/javadoc
	javadoc $(SOURCES_JAVADOC_FILES) -d build/java/javadoc -Xdoclint:all -noqualifier java.lang

build/java/manifest-javadoc.txt: | build/java
	@echo Implementation-Name: LibLouisAPH javadoc >  $@
	@echo Implementation-Version: $(VERSION) >> $@
	@echo Implementation-Vender: American Printing House for the Blind >> $@
	@echo Implementation-URL: www.aph.org >> $@
	@echo >> $@

build/LibLouisAPH-javadoc.jar: build/java/javadoc/index.html build/java/manifest-javadoc.txt  | build
	cd build/java/javadoc && jar cfm $(@F) ../../java/manifest-javadoc.txt . && mv $(@F) ../../

endif

################################################################################
#
#   Testing
#
################################################################################

.PHONY: test test-all test-lib test-db test-langs test-link test-tools test-opt

test: test-lib test-link test-tools

build/test:
	mkdir -p build/test/

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

test-tools: CPPFLAGS += -D BUFFER_MAX=7
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
test-opt: CFLAGS += -O3 $(CWARNS_OPTIMAL)
test-opt: build/exe-test-opt
	@build/exe-test-opt

OBJS_TEST_OPT_BUILD := $(foreach OBJ, $(OBJS_LIB) $(OBJS_LANG) $(OBJS_OUTPUT) $(OBJS_DEBUG) $(OBJS_TEST_LANGUAGES), build/objects/opt/$(OBJ))

build/exe-test-opt: $(OBJS_TEST_OPT_BUILD) | build/test
	$(CC) -o $@ $(CFLAGS) $(OBJS_TEST_OPT_BUILD) $(LDFLAGS)

########################################

.PHONY: test-java test-jar

ifneq ($(HAS_JAVAC),1)

test-java: jar

else

test: test-java test-jar

build/java/test:
	mkdir -p build/java/test/

test-java: CPPFLAGS += $(JNI_INCLUDES) -I build/java -D DEBUG
test-java: CFLAGS += -ggdb -fstack-protector -fPIC $(CWARNS_DEBUG)
test-java: build/java/org/aph/liblouisaph/Test.class
	@java -cp build/java/ -Djava.library.path=build org/aph/liblouisaph/Test

build/java/org/aph/liblouisaph/Test.class: java/org/aph/liblouisaph/Test.java build/liblouisAPH-jni.so | build/java build/test
	javac -d build/java -classpath build/java -sourcepath java $<

test-jar: CPPFLAGS += $(JNI_INCLUDES) -I build/java -D DEBUG
test-jar: CFLAGS += -ggdb -fstack-protector -fPIC $(CWARNS_DEBUG)
test-jar: build/java/test/TestJar.class
	@java -cp build/java/test/:build/LibLouisAPH.jar TestJar internal
	@java -cp build/java/test/:build/LibLouisAPH.jar TestJar external
	@java -cp build/java/test/:build/LibLouisAPH.jar -Djava.library.path=build TestJar system

build/java/test/TestJar.class: java/TestJar.java build/LibLouisAPH.jar | build/java/test build/test
	javac -d build/java/test/ -classpath build/java/ -sourcepath java $<

endif

################################################################################

.PHONY: dists releases

################################################################################
#
#   Linux 64 bit
#
################################################################################

.PHONY: dist-linux64 dll-linux64 lib-linux64

dists: dist-linux64

dist-linux64: dll-linux64 lib-linux64

dists/x86_64-linux:
	mkdir -p dists/x86_64-linux/

FILES_RELEASE_LINUX64 := \
	dists/x86_64-linux/liblouisAPH-linux64-$(VERSION).so \
	dists/x86_64-linux/liblouisAPH-linux64-$(VERSION).a \
	dists/x86_64-linux/lou_convert \
	dists/x86_64-linux/lou_table \
	dists/x86_64-linux/lou_translate \

dll-linux64: CFLAGS += -O3 -fPIC -fvisibility=hidden $(CWARNS_OPTIMAL)
dll-linux64: dists/x86_64-linux/liblouisAPH-linux64-$(VERSION).so

OBJS_DLL_LINUX64 := $(foreach OBJ, $(OBJS_LIB) $(OBJS_LANG) $(OBJ_LIB_IFACE), dists/x86_64-linux/objects/dll/$(OBJ))

dists/x86_64-linux/liblouisAPH-linux64-$(VERSION).so: $(OBJS_DLL_LINUX64) | dists/x86_64-linux
	$(CC) -o $@ -shared -s $(CFLAGS) $(OBJS_DLL_LINUX64)

lib-linux64: CFLAGS += -O3 $(CWARNS_OPTIMAL)
lib-linux64: dists/x86_64-linux/liblouisAPH-linux64-$(VERSION).a

OBJS_LIB_LINUX64 := $(foreach OBJ, $(OBJS_LIB) $(OBJS_LANG) $(OBJ_LIB_IFACE), dists/x86_64-linux/objects/$(OBJ))

dists/x86_64-linux/liblouisAPH-linux64-$(VERSION).a: $(OBJS_LIB_LINUX64) | dists/x86_64-linux
	ar -rcv $@ $(OBJS_LIB_LINUX64)

########################################

.PHONY: convert-linux64 table-linux64 translate-linux64

dist-linux64: translate-linux64 table-linux64 convert-linux64

convert-linux64: CPPFLAGS += -I source/outputs -D OUTPUT
convert-linux64: CFLAGS += -O3 $(CWARNS_OPTIMAL)
convert-linux64: dists/x86_64-linux/lou_convert

OBJS_CONVERT_LINUX64 := $(foreach OBJ, $(OBJS_CONVERT), dists/x86_64-linux/objects/$(OBJ))

dists/x86_64-linux/lou_convert: $(OBJS_CONVERT_LINUX64) | dists/x86_64-linux
	$(CC) -o $@ $(CFLAGS) $(OBJS_CONVERT_LINUX64) $(LDFLAGS)

table-linux64: CPPFLAGS += -I source/outputs -D OUTPUT
table-linux64: CFLAGS += -O3 $(CWARNS_OPTIMAL)
table-linux64: dists/x86_64-linux/lou_table

OBJS_TABLE_LINUX64 := $(foreach OBJ, $(OBJS_TABLE), dists/x86_64-linux/objects/$(OBJ))

dists/x86_64-linux/lou_table: $(OBJS_TABLE_LINUX64) | dists/x86_64-linux
	$(CC) -o $@ $(CFLAGS) $(OBJS_TABLE_LINUX64) $(LDFLAGS)

translate-linux64: CPPFLAGS += -I source/outputs -D OUTPUT
translate-linux64: CFLAGS += -O3 $(CWARNS_OPTIMAL)
translate-linux64: dists/x86_64-linux/lou_translate

OBJS_TRANSLATE_LINUX64 := $(foreach OBJ, $(OBJS_TRANSLATE), dists/x86_64-linux/objects/$(OBJ))

dists/x86_64-linux/lou_translate: $(OBJS_TRANSLATE_LINUX64) | dists/x86_64-linux
	$(CC) -o $@ $(CFLAGS) $(OBJS_TRANSLATE_LINUX64) $(LDFLAGS)

########################################

.PHONY: jars-linux64 jar-linux64 javadoc-jar-linux64 sources-jar-linux64

ifneq ($(HAS_JAVAC),1)

jars-linux64: jar

jar-linux64: jar

else

dist-linux64: jars-linux64

FILES_RELEASE_LINUX64 := \
	$(FILES_RELEASE_LINUX64) \
	dists/x86_64-linux/liblouisAPH-jni-linux64-$(VERSION).so \
	dists/x86_64-linux/LibLouisAPH-linux64-$(VERSION).jar \
	dists/x86_64-linux/LibLouisAPH-sources-$(VERSION).jar \
	dists/x86_64-linux/LibLouisAPH-javadoc-$(VERSION).jar \

jars-linux64: jar-linux64 javadoc-jar-linux64 sources-jar-linux64

jar-linux64: CPPFLAGS += $(JNI_INCLUDES) -I build/java
jar-linux64: CFLAGS += -O3 -fPIC -fvisibility=hidden $(CWARNS_OPTIMAL)
jar-linux64: dists/x86_64-linux/LibLouisAPH-linux64-$(VERSION).jar

dists/x86_64-linux/objects/java:
	mkdir -p dists/x86_64-linux/objects/java/

dists/x86_64-linux/manifest.txt: | dists/x86_64-linux
	@echo Implementation-Name: LibLouisAPH Linux 64 bit >  $@
	@echo Implementation-Version: $(VERSION) >> $@
	@echo Implementation-Vender: American Printing House for the Blind >> $@
	@echo Implementation-URL: www.aph.org >> $@
	@echo Automatic-Module-Name:  org.aph.liblouisaph >> $@
	@echo >> $@

dists/x86_64-linux/liblouisaph.properties: | dists/x86_64-linux
	echo Library-Name=liblouisAPH-jni-linux64-$(VERSION).so > dists/x86_64-linux/liblouisaph.properties
	echo Table-Path=tables >> dists/x86_64-linux/liblouisaph.properties

dists/x86_64-linux/objects/java/interface-jni.o: java/interface-jni.c build/java/org_aph_liblouisaph_LibLouisAPH.h | dists/x86_64-linux/objects/java
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) $< $(LDFLAGS)

OBJS_JNI_LINUX64 := $(foreach OBJ, $(OBJS_LIB) $(OBJS_LANG), dists/x86_64-linux/objects/dll/$(OBJ))

dists/x86_64-linux/liblouisAPH-jni-linux64-$(VERSION).so: $(OBJS_JNI_LINUX64) dists/x86_64-linux/objects/java/interface-jni.o | dists/x86_64-linux
	$(CC) -o $@ -shared -s $(OBJS_JNI_LINUX64) dists/x86_64-linux/objects/java/interface-jni.o

FILES_JAR_LINUX64 := -C dists/x86_64-linux liblouisAPH-jni-linux64-$(VERSION).so -C dists/x86_64-linux liblouisaph.properties

dists/x86_64-linux/LibLouisAPH-linux64-$(VERSION).jar: dists/x86_64-linux/manifest.txt dists/x86_64-linux/liblouisaph.properties dists/x86_64-linux/liblouisAPH-jni-linux64-$(VERSION).so build/java/org/aph/liblouisaph/Main.class | dists/x86_64-linux
	jar cfme $@ dists/x86_64-linux/manifest.txt org.aph.liblouisaph.Main $(CLASSES_JAR_BUILD) $(FILES_JAR_LINUX64) $(TABLES)

sources-jar-linux64: dists/x86_64-linux/LibLouisAPH-sources-$(VERSION).jar

dists/x86_64-linux/LibLouisAPH-sources-$(VERSION).jar: build/LibLouisAPH-sources.jar | dists/x86_64-linux
	cp $< $@

javadoc-jar-linux64: dists/x86_64-linux/LibLouisAPH-javadoc-$(VERSION).jar

dists/x86_64-linux/LibLouisAPH-javadoc-$(VERSION).jar: build/LibLouisAPH-javadoc.jar | dists/x86_64-linux
	cp $< $@

endif

########################################

.PHONY: release-linux64

releases: release-linux64

release-linux64: dist-linux64 releases/LibLouisAPH-linux64-$(VERSION).tar.bz2

releases/LibLouisAPH-linux64-$(VERSION).tar.bz2: $(FILES_RELEASE_LINUX64)
	mkdir -p releases/LibLouisAPH-linux64-$(VERSION)/
	cp -R $(FILES_RELEASE_LINUX64) releases/LibLouisAPH-linux64-$(VERSION)/
	cp -R tables/ releases/LibLouisAPH-linux64-$(VERSION)/
	cp LibLouisAPH.h LICENSE-2.0.txt releases/LibLouisAPH-linux64-$(VERSION)/
	cd releases && tar jvfc LibLouisAPH-linux64-$(VERSION).tar.bz2 LibLouisAPH-linux64-$(VERSION)/

################################################################################
#
#   Linux 32 bit
#
################################################################################

.PHONY: dist-linux32 dll-linux32 lib-linux32

dists: dist-linux32

dist-linux32: dll-linux32 lib-linux32

dists/i686-linux:
	mkdir -p dists/i686-linux/

FILES_RELEASE_LINUX32 := \
	dists/i686-linux/liblouisAPH-linux32-$(VERSION).so \
	dists/i686-linux/liblouisAPH-linux32-$(VERSION).a \
	dists/i686-linux/lou_convert \
	dists/i686-linux/lou_table \
	dists/i686-linux/lou_translate \

dll-linux32: CFLAGS += -O3 -m32 $(CWARNS_OPTIMAL)
dll-linux32: dists/i686-linux/liblouisAPH-linux32-$(VERSION).so

OBJS_DLL_LINUX32 := $(foreach OBJ, $(OBJS_LIB) $(OBJS_LANG) $(OBJ_LIB_IFACE), dists/i686-linux/objects/$(OBJ))

dists/i686-linux/liblouisAPH-linux32-$(VERSION).so: $(OBJS_DLL_LINUX32) | dists/i686-linux
	$(CC) -o $@ -m32 -shared $(CFLAGS) $(OBJS_DLL_LINUX32)

lib-linux32: CFLAGS += -O3 -m32 $(CWARNS_OPTIMAL)
lib-linux32: dists/i686-linux/liblouisAPH-linux32-$(VERSION).a

OBJS_LIB_LINUX32 := $(foreach OBJ, $(OBJS_LIB) $(OBJS_LANG) $(OBJ_LIB_IFACE), dists/i686-linux/objects/$(OBJ))

dists/i686-linux/liblouisAPH-linux32-$(VERSION).a: $(OBJS_LIB_LINUX32) | dists/i686-linux
	ar -rcv $@ $(OBJS_LIB_LINUX32)

########################################

.PHONY: convert-linux32 table-linux32 translate-linux32

dist-linux32: translate-linux32 table-linux32 convert-linux32

convert-linux32: CPPFLAGS += -I source/outputs -D OUTPUT
convert-linux32: CFLAGS += -O3 -m32 $(CWARNS_OPTIMAL)
convert-linux32: dists/i686-linux/lou_convert

OBJS_CONVERT_LINUX32 := $(foreach OBJ, $(OBJS_CONVERT), dists/i686-linux/objects/$(OBJ))

dists/i686-linux/lou_convert: $(OBJS_CONVERT_LINUX32) | dists/i686-linux
	$(CC) -o $@ -m32 $(CFLAGS) $(OBJS_CONVERT_LINUX32) $(LDFLAGS)

table-linux32: CPPFLAGS += -I source/outputs -D OUTPUT
table-linux32: CFLAGS += -O3 -m32 $(CWARNS_OPTIMAL)
table-linux32: dists/i686-linux/lou_table

OBJS_TABLE_LINUX32 := $(foreach OBJ, $(OBJS_TABLE), dists/i686-linux/objects/$(OBJ))

dists/i686-linux/lou_table: $(OBJS_TABLE_LINUX32) | dists/i686-linux
	$(CC) -o $@ -m32 $(CFLAGS) $(OBJS_TABLE_LINUX32) $(LDFLAGS)

translate-linux32: CPPFLAGS += -I source/outputs -D OUTPUT
translate-linux32: CFLAGS += -O3 -m32 $(CWARNS_OPTIMAL)
translate-linux32: dists/i686-linux/lou_translate

OBJS_TRANSLATE_LINUX32 := $(foreach OBJ, $(OBJS_TRANSLATE), dists/i686-linux/objects/$(OBJ))

dists/i686-linux/lou_translate: $(OBJS_TRANSLATE_LINUX32) | dists/i686-linux
	$(CC) -o $@ -m32 $(CFLAGS) $(OBJS_TRANSLATE_LINUX32) $(LDFLAGS)

########################################

.PHONY: jars-linux32 jar-linux32 javadoc-jar-linux32 sources-jar-linux32

ifneq ($(HAS_JAVAC),1)

jars-linux32: jar

jar-linux32: jar

else

dist-linux32: jars-linux32

FILES_RELEASE_LINUX32 := \
	$(FILES_RELEASE_LINUX32) \
	dists/i686-linux/liblouisAPH-jni-linux32-$(VERSION).so \
	dists/i686-linux/LibLouisAPH-linux32-$(VERSION).jar \
	dists/i686-linux/LibLouisAPH-sources-$(VERSION).jar \
	dists/i686-linux/LibLouisAPH-javadoc-$(VERSION).jar \

jars-linux32: jar-linux32 javadoc-jar-linux32 sources-jar-linux32

jar-linux32: CPPFLAGS += $(JNI_INCLUDES) -I build/java
jar-linux32: CFLAGS += -O3 -m32 $(CWARNS_OPTIMAL)
jar-linux32: dists/i686-linux/LibLouisAPH-linux32-$(VERSION).jar

dists/i686-linux/objects/java:
	mkdir -p dists/i686-linux/objects/java/

dists/i686-linux/manifest.txt: | dists/i686-linux
	@echo Implementation-Name: LibLouisAPH Linux 32 bit >  $@
	@echo Implementation-Version: $(VERSION) >> $@
	@echo Implementation-Vender: American Printing House for the Blind >> $@
	@echo Implementation-URL: www.aph.org >> $@
	@echo >> $@

dists/i686-linux/liblouisaph.properties: | dists/i686-linux
	echo Library-Name=liblouisAPH-jni-linux32-$(VERSION).so > dists/i686-linux/liblouisaph.properties
	echo Table-Path=tables >> dists/i686-linux/liblouisaph.properties

dists/i686-linux/objects/java/interface-jni.o: java/interface-jni.c build/java/org_aph_liblouisaph_LibLouisAPH.h | dists/i686-linux/objects/java
	$(CC) -o $@ -m32 -c $(CPPFLAGS) $(CFLAGS) $< $(LDFLAGS)

OBJS_JNI_LINUX32 := $(foreach OBJ, $(OBJS_LIB) $(OBJS_LANG), dists/i686-linux/objects/$(OBJ))

dists/i686-linux/liblouisAPH-jni-linux32-$(VERSION).so: $(OBJS_JNI_LINUX32) dists/i686-linux/objects/java/interface-jni.o | dists/i686-linux
	$(CC) -o $@ -m32 -shared -s $(OBJS_JNI_LINUX32) dists/i686-linux/objects/java/interface-jni.o

FILES_JAR_LINUX32 := -C dists/i686-linux liblouisAPH-jni-linux32-$(VERSION).so -C dists/i686-linux liblouisaph.properties

dists/i686-linux/LibLouisAPH-linux32-$(VERSION).jar: dists/i686-linux/manifest.txt dists/i686-linux/liblouisaph.properties dists/i686-linux/liblouisAPH-jni-linux32-$(VERSION).so build/java/org/aph/liblouisaph/Main.class | dists/i686-linux
	jar cfme $@ dists/i686-linux/manifest.txt org.aph.liblouisaph.Main $(CLASSES_JAR_BUILD) $(TABLES) $(FILES_JAR_LINUX32)

sources-jar-linux32: dists/i686-linux/LibLouisAPH-sources-$(VERSION).jar

dists/i686-linux/LibLouisAPH-sources-$(VERSION).jar: build/LibLouisAPH-sources.jar | dists/i686-linux
	cp $< $@

javadoc-jar-linux32: dists/i686-linux/LibLouisAPH-javadoc-$(VERSION).jar

dists/i686-linux/LibLouisAPH-javadoc-$(VERSION).jar: build/LibLouisAPH-javadoc.jar | dists/i686-linux
	cp $< $@

endif

########################################

.PHONY: release-linux32

releases: release-linux32

release-linux32: dist-linux32 releases/LibLouisAPH-linux32-$(VERSION).tar.bz2

releases/LibLouisAPH-linux32-$(VERSION).tar.bz2: $(FILES_RELEASE_LINUX32)
	mkdir -p releases/LibLouisAPH-linux32-$(VERSION)/
	cp -R $(FILES_RELEASE_LINUX32) releases/LibLouisAPH-linux32-$(VERSION)/
	cp -R tables/ releases/LibLouisAPH-linux32-$(VERSION)/
	cp LibLouisAPH.h LICENSE-2.0.txt releases/LibLouisAPH-linux32-$(VERSION)/
	cd releases && tar jvfc LibLouisAPH-linux32-$(VERSION).tar.bz2 LibLouisAPH-linux32-$(VERSION)/

################################################################################
#
#   Windows 64 bit
#
################################################################################

.PHONY: dist-win64 dll-win64 convert-win64 table-win64 translate-win64
.PHONY: jars-win64 jar-win64 javadoc-jar-win64 sources-jar-win64
.PHONY: release-win64

HAS_MINGW64 := $(shell if (which $(CC_WIN64) > /dev/null 2>&1 ); then echo 1; else echo 0; fi )

ifneq ($(HAS_MINGW64),1)

dist-win64 dll-win64 convert-win64 table-win64 translate-win64: FORCE
	@echo missing $(CC_WIN64)
	@false

jars-win64 jar-win64 javadoc-jar-win64 sources-jar-win64: dist-win64
release-win64: dist-win64

else

dists: dist-win64

dist-win64: dll-win64 convert-win64 table-win64 translate-win64

dists/x86_64-win:
	mkdir -p dists/x86_64-win/

FILES_RELEASE_WIN64 := \
	dists/x86_64-win/liblouisAPH-win64-$(VERSION).dll \
	dists/x86_64-win/lou_convert.exe \
	dists/x86_64-win/lou_table.exe \
	dists/x86_64-win/lou_translate.exe \

dll-win64: CC = $(CC_WIN64)
dll-win64: CFLAGS += -O3 $(CWARNS_OPTIMAL)
dll-win64: dists/x86_64-win/liblouisAPH-win64-$(VERSION).dll

OBJS_DLL_WIN64 := $(foreach OBJ, $(OBJS_LIB) $(OBJS_LANG) $(OBJ_LIB_IFACE), dists/x86_64-win/objects/$(OBJ))

dists/x86_64-win/liblouisAPH-win64-$(VERSION).dll: $(OBJS_DLL_WIN64) | dists/x86_64-win
	$(CC) -o $@ -shared $(CFLAGS) $(OBJS_DLL_WIN64)

convert-win64: CC = $(CC_WIN64)
convert-win64: CPPFLAGS += -I source/outputs -D OUTPUT
convert-win64: CFLAGS += -O3 $(CWARNS_OPTIMAL)
convert-win64: dists/x86_64-win/lou_convert.exe

OBJS_CONVERT_WIN64 := $(foreach OBJ, $(OBJS_CONVERT), dists/x86_64-win/objects/$(OBJ))

dists/x86_64-win/lou_convert.exe: $(OBJS_CONVERT_WIN64) | dists/x86_64-win
	$(CC) -o $@ $(CFLAGS) $(OBJS_CONVERT_WIN64) $(LDFLAGS)

table-win64: CC = $(CC_WIN64)
table-win64: CPPFLAGS += -I source/outputs -D OUTPUT
table-win64: CFLAGS += -O3 $(CWARNS_OPTIMAL)
table-win64: dists/x86_64-win/lou_table.exe

OBJS_TABLE_WIN64 := $(foreach OBJ, $(OBJS_TABLE), dists/x86_64-win/objects/$(OBJ))

dists/x86_64-win/lou_table.exe: $(OBJS_TABLE_WIN64) | dists/x86_64-win
	$(CC) -o $@ $(CFLAGS) $(OBJS_TABLE_WIN64) $(LDFLAGS)

translate-win64: CC = $(CC_WIN64)
translate-win64: CPPFLAGS += -I source/outputs -D OUTPUT
translate-win64: CFLAGS += -O3 $(CWARNS_OPTIMAL)
translate-win64: dists/x86_64-win/lou_translate.exe

OBJS_TRANSLATE_WIN64 := $(foreach OBJ, $(OBJS_TRANSLATE), dists/x86_64-win/objects/$(OBJ))

dists/x86_64-win/lou_translate.exe: $(OBJS_TRANSLATE_WIN64) | dists/x86_64-win
	$(CC) -o $@ $(CFLAGS) $(OBJS_TRANSLATE_WIN64) $(LDFLAGS)

########################################

ifneq ($(HAS_JAVAC),1)

jars-win64 jar-win64 javadoc-jar-win64 sources-jar-win64: jar

else

dist-win64: jars-win64

FILES_RELEASE_WIN64 := \
	$(FILES_RELEASE_WIN64) \
	dists/x86_64-win/liblouisAPH-jni-win64-$(VERSION).dll \
	dists/x86_64-win/LibLouisAPH-win64-$(VERSION).jar \
	dists/x86_64-win/LibLouisAPH-sources-$(VERSION).jar \
	dists/x86_64-win/LibLouisAPH-javadoc-$(VERSION).jar \

jars-win64: jar-win64 javadoc-jar-win64 sources-jar-win64

jar-win64: CC = $(CC_WIN64)
jar-win64: CPPFLAGS += $(JNI_INCLUDES) -I build/java
jar-win64: CFLAGS += -O3 $(CWARNS_OPTIMAL)
jar-win64: dists/x86_64-win/LibLouisAPH-win64-$(VERSION).jar

dists/x86_64-win/objects/java:
	mkdir -p dists/x86_64-win/objects/java/

dists/x86_64-win/manifest.txt: | dists/x86_64-win
	@echo Implementation-Name: LibLouisAPH Windows 64 bit >  $@
	@echo Implementation-Version: $(VERSION) >> $@
	@echo Implementation-Vender: American Printing House for the Blind >> $@
	@echo Implementation-URL: www.aph.org >> $@
	@echo Automatic-Module-Name:  org.aph.liblouisaph >> $@
	@echo >> $@

dists/x86_64-win/liblouisaph.properties: | dists/x86_64-win
	echo Library-Name=liblouisAPH-jni-win64-$(VERSION).dll > dists/x86_64-win/liblouisaph.properties
	echo Table-Path=tables >> dists/x86_64-win/liblouisaph.properties

dists/x86_64-win/objects/java/interface-jni.o: java/interface-jni.c build/java/org_aph_liblouisaph_LibLouisAPH.h | dists/x86_64-win/objects/java
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) $< $(LDFLAGS)

OBJS_JNI_WIN64 := $(foreach OBJ, $(OBJS_LIB) $(OBJS_LANG), dists/x86_64-win/objects/$(OBJ))

dists/x86_64-win/liblouisAPH-jni-win64-$(VERSION).dll: $(OBJS_JNI_WIN64) dists/x86_64-win/objects/java/interface-jni.o | dists/x86_64-win
	$(CC) -o $@ -shared $(OBJS_JNI_WIN64) dists/x86_64-win/objects/java/interface-jni.o

FILES_JAR_WIN64 := -C dists/x86_64-win liblouisAPH-jni-win64-$(VERSION).dll -C dists/x86_64-win liblouisaph.properties

dists/x86_64-win/LibLouisAPH-win64-$(VERSION).jar: dists/x86_64-win/manifest.txt dists/x86_64-win/liblouisaph.properties dists/x86_64-win/liblouisAPH-jni-win64-$(VERSION).dll build/java/org/aph/liblouisaph/Main.class | dists/x86_64-win
	jar cfme $@ dists/x86_64-win/manifest.txt org.aph.liblouisaph.Main $(CLASSES_JAR_BUILD) $(TABLES) $(FILES_JAR_WIN64)

sources-jar-win64: dists/x86_64-win/LibLouisAPH-sources-$(VERSION).jar

dists/x86_64-win/LibLouisAPH-sources-$(VERSION).jar: build/LibLouisAPH-sources.jar | dists/x86_64-win
	cp $< $@

javadoc-jar-win64: dists/x86_64-win/LibLouisAPH-javadoc-$(VERSION).jar

dists/x86_64-win/LibLouisAPH-javadoc-$(VERSION).jar: build/LibLouisAPH-javadoc.jar | dists/x86_64-win
	cp $< $@

endif

########################################

releases: release-win64

release-win64: dist-win64 releases/LibLouisAPH-win64-$(VERSION).zip

releases/LibLouisAPH-win64-$(VERSION).zip: $(FILES_RELEASE_WIN64)
	mkdir -p releases/LibLouisAPH-win64-$(VERSION)/
	cp -R $(FILES_RELEASE_WIN64) releases/LibLouisAPH-win64-$(VERSION)/
	cp -R tables/ releases/LibLouisAPH-win64-$(VERSION)/
	cp LibLouisAPH.h LICENSE-2.0.txt releases/LibLouisAPH-win64-$(VERSION)/
	cd releases && zip -r -9 LibLouisAPH-win64-$(VERSION).zip LibLouisAPH-win64-$(VERSION)/

endif

################################################################################
#
#   Windows 32 bit
#
################################################################################

.PHONY: dist-win32 dll-win32 convert-win32 table-win32 translate-win32
.PHONY: jars-win32 jar-win32 javadoc-jar-win32 sources-jar-win32
.PHONY: release-win32

HAS_MINGW32 := $(shell if (which $(CC_WIN32) > /dev/null 2>&1 ); then echo 1; else echo 0; fi )

ifneq ($(HAS_MINGW32),1)

dist-win32 dll-win32 convert-win32 table-win32 translate-win32: FORCE
	@echo missing $(CC_WIN32)
	@false

jars-win32 jar-win32 javadoc-jar-win32 sources-jar-win32: dist-win32
release-win32: dist-win32

else

dists: dist-win32

dist-win32: dll-win32 convert-win32 table-win32 translate-win32

dists/i686-win:
	mkdir -p dists/i686-win/

FILES_RELEASE_WIN32 := \
	dists/i686-win/liblouisAPH-win32-$(VERSION).dll \
	dists/i686-win/lou_convert.exe \
	dists/i686-win/lou_table.exe \
	dists/i686-win/lou_translate.exe \

dll-win32: CC = $(CC_WIN32)
dll-win32: CFLAGS += -O3 $(CWARNS_OPTIMAL)
dll-win32: dists/i686-win/liblouisAPH-win32-$(VERSION).dll

OBJS_DLL_WIN32 := $(foreach OBJ, $(OBJS_LIB) $(OBJS_LANG) $(OBJ_LIB_IFACE), dists/i686-win/objects/$(OBJ))

dists/i686-win/liblouisAPH-win32-$(VERSION).dll: $(OBJS_DLL_WIN32) | dists/i686-win
	$(CC) -o $@ -shared $(CFLAGS) $(OBJS_DLL_WIN32)

convert-win32: CC = $(CC_WIN32)
convert-win32: CPPFLAGS += -I source/outputs -D OUTPUT
convert-win32: CFLAGS += -O3 $(CWARNS_OPTIMAL)
convert-win32: dists/i686-win/lou_convert.exe

OBJS_CONVERT_WIN32 := $(foreach OBJ, $(OBJS_CONVERT), dists/i686-win/objects/$(OBJ))

dists/i686-win/lou_convert.exe: $(OBJS_CONVERT_WIN32) | dists/i686-win
	$(CC) -o $@ $(CFLAGS) $(OBJS_CONVERT_WIN32) $(LDFLAGS)

table-win32: CC = $(CC_WIN32)
table-win32: CPPFLAGS += -I source/outputs -D OUTPUT
table-win32: CFLAGS += -O3 $(CWARNS_OPTIMAL)
table-win32: dists/i686-win/lou_table.exe

OBJS_TABLE_WIN32 := $(foreach OBJ, $(OBJS_TABLE), dists/i686-win/objects/$(OBJ))

dists/i686-win/lou_table.exe: $(OBJS_TABLE_WIN32) | dists/i686-win
	$(CC) -o $@ $(CFLAGS) $(OBJS_TABLE_WIN32) $(LDFLAGS)

translate-win32: CC = $(CC_WIN32)
translate-win32: CPPFLAGS += -I source/outputs -D OUTPUT
translate-win32: CFLAGS += -O3 $(CWARNS_OPTIMAL)
translate-win32: dists/i686-win/lou_translate.exe

OBJS_TRANSLATE_WIN32 := $(foreach OBJ, $(OBJS_TRANSLATE), dists/i686-win/objects/$(OBJ))

dists/i686-win/lou_translate.exe: $(OBJS_TRANSLATE_WIN32) | dists/i686-win
	$(CC) -o $@ $(CFLAGS) $(OBJS_TRANSLATE_WIN32) $(LDFLAGS)

########################################

ifneq ($(HAS_JAVAC),1)

jars-win32 jar-win32 javadoc-jar-win32 sources-jar-win32: jar

else

dist-win32: jars-win32

FILES_RELEASE_WIN32 := \
	$(FILES_RELEASE_WIN32) \
	dists/i686-win/liblouisAPH-jni-win32-$(VERSION).dll \
	dists/i686-win/LibLouisAPH-win32-$(VERSION).jar \
	dists/i686-win/LibLouisAPH-sources-$(VERSION).jar \
	dists/i686-win/LibLouisAPH-javadoc-$(VERSION).jar \

jars-win32: jar-win32 javadoc-jar-win32 sources-jar-win32

jar-win32: CC = $(CC_WIN32)
jar-win32: CPPFLAGS += $(JNI_INCLUDES) -I build/java
jar-win32: CFLAGS += -O3 $(CWARNS_OPTIMAL)
jar-win32: dists/i686-win/LibLouisAPH-win32-$(VERSION).jar

dists/i686-win/objects/java:
	mkdir -p dists/i686-win/objects/java/

dists/i686-win/manifest.txt: | dists/i686-win
	@echo Implementation-Name: LibLouisAPH Windows 32 bit >  $@
	@echo Implementation-Version: $(VERSION) >> $@
	@echo Implementation-Vender: American Printing House for the Blind >> $@
	@echo Implementation-URL: www.aph.org >> $@
	@echo >> $@

dists/i686-win/liblouisaph.properties: | dists/i686-win
	echo Library-Name=liblouisAPH-jni-win32-$(VERSION).dll > dists/i686-win/liblouisaph.properties
	echo Table-Path=tables >> dists/i686-win/liblouisaph.properties

dists/i686-win/objects/java/interface-jni.o: java/interface-jni.c build/java/org_aph_liblouisaph_LibLouisAPH.h | dists/i686-win/objects/java
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) $< $(LDFLAGS)

OBJS_JNI_WIN32 := $(foreach OBJ, $(OBJS_LIB) $(OBJS_LANG), dists/i686-win/objects/$(OBJ))

dists/i686-win/liblouisAPH-jni-win32-$(VERSION).dll: $(OBJS_JNI_WIN32) dists/i686-win/objects/java/interface-jni.o | dists/i686-win
	$(CC) -o $@ -shared -Wl,--add-stdcall-alias $(OBJS_JNI_WIN32) dists/i686-win/objects/java/interface-jni.o

FILES_JAR_WIN32 := -C dists/i686-win liblouisAPH-jni-win32-$(VERSION).dll -C dists/i686-win liblouisaph.properties

dists/i686-win/LibLouisAPH-win32-$(VERSION).jar: dists/i686-win/manifest.txt dists/i686-win/liblouisaph.properties dists/i686-win/liblouisAPH-jni-win32-$(VERSION).dll build/java/org/aph/liblouisaph/Main.class | dists/i686-win
	jar cfme $@ dists/i686-win/manifest.txt org.aph.liblouisaph.Main $(CLASSES_JAR_BUILD) $(TABLES) $(FILES_JAR_WIN32)

sources-jar-win32: dists/i686-win/LibLouisAPH-sources-$(VERSION).jar

dists/i686-win/LibLouisAPH-sources-$(VERSION).jar: build/LibLouisAPH-sources.jar | dists/i686-win
	cp $< $@

javadoc-jar-win32: dists/i686-win/LibLouisAPH-javadoc-$(VERSION).jar

dists/i686-win/LibLouisAPH-javadoc-$(VERSION).jar: build/LibLouisAPH-javadoc.jar | dists/i686-win
	cp $< $@

endif

########################################

releases: release-win32

release-win32: dist-win32 releases/LibLouisAPH-win32-$(VERSION).zip

releases/LibLouisAPH-win32-$(VERSION).zip: $(FILES_RELEASE_WIN32)
	mkdir -p releases/LibLouisAPH-win32-$(VERSION)/
	cp -R $(FILES_RELEASE_WIN32) releases/LibLouisAPH-win32-$(VERSION)/
	cp -R tables/ releases/LibLouisAPH-win32-$(VERSION)/
	cp LibLouisAPH.h LICENSE-2.0.txt releases/LibLouisAPH-win32-$(VERSION)/
	cd releases && zip -r -9 LibLouisAPH-win32-$(VERSION).zip LibLouisAPH-win32-$(VERSION)/

endif

################################################################################
#
#   Mac 64 bit
#
################################################################################

.PHONY: dist-mac64 dll-mac64 convert-mac64 table-mac64 translate-mac64
.PHONY: jars-mac64 jar-mac64 javadoc-jar-mac64 sources-jar-mac64
.PHONY: release-mac64

HAS_OSXCROSS64 := $(shell if (which $(CC_MAC64) > /dev/null 2>&1 ); then echo 1; else echo 0; fi )

ifneq ($(HAS_OSXCROSS64),1)

dist-mac64 dll-mac64 convert-mac64 table-mac64 translate-mac64 release-mac64: FORCE
	@echo missing $(CC_MAC64)
	@false

jars-mac64 jar-mac64 javadoc-jar-mac64 sources-jar-mac64: dist-mac64
release-mac64: dist-mac64

else

dists: dist-mac64

dist-mac64: dll-mac64 convert-mac64 table-mac64 translate-mac64

dists/x86_64-mac:
	mkdir -p dists/x86_64-mac/

FILES_RELEASE_MAC64 := \
	dists/x86_64-mac/liblouisAPH-mac64-$(VERSION).dylib \
	dists/x86_64-mac/lou_convert \
	dists/x86_64-mac/lou_table \
	dists/x86_64-mac/lou_translate \

dll-mac64: CC = $(CC_MAC64)
dll-mac64: CFLAGS += -O3 $(CWARNS_OPTIMAL)
dll-mac64: dists/x86_64-mac/liblouisAPH-mac64-$(VERSION).dylib

OBJS_DLL_MAC64 := $(foreach OBJ, $(OBJS_LIB) $(OBJS_LANG) $(OBJ_LIB_IFACE), dists/x86_64-mac/objects/$(OBJ))

dists/x86_64-mac/liblouisAPH-mac64-$(VERSION).dylib: $(OBJS_DLL_MAC64) | dists/x86_64-mac
	$(CC) -o $@ -shared $(CFLAGS) $(OBJS_DLL_MAC64)

convert-mac64: CC = $(CC_MAC64)
convert-mac64: CPPFLAGS += -I source/outputs -D OUTPUT
convert-mac64: CFLAGS += -O3 $(CWARNS_OPTIMAL)
convert-mac64: dists/x86_64-mac/lou_convert

OBJS_CONVERT_MAC64 := $(foreach OBJ, $(OBJS_CONVERT), dists/x86_64-mac/objects/$(OBJ))

dists/x86_64-mac/lou_convert: $(OBJS_CONVERT_MAC64) | dists/x86_64-mac
	$(CC) -o $@ $(CFLAGS) $(OBJS_CONVERT_MAC64) $(LDFLAGS)

table-mac64: CC = $(CC_MAC64)
table-mac64: CPPFLAGS += -I source/outputs -D OUTPUT
table-mac64: CFLAGS += -O3 $(CWARNS_OPTIMAL)
table-mac64: dists/x86_64-mac/lou_table

OBJS_TABLE_MAC64 := $(foreach OBJ, $(OBJS_TABLE), dists/x86_64-mac/objects/$(OBJ))

dists/x86_64-mac/lou_table: $(OBJS_TABLE_MAC64) | dists/x86_64-mac
	$(CC) -o $@ $(CFLAGS) $(OBJS_TABLE_MAC64) $(LDFLAGS)

translate-mac64: CC = $(CC_MAC64)
translate-mac64: CPPFLAGS += -I source/outputs -D OUTPUT
translate-mac64: CFLAGS += -O3 $(CWARNS_OPTIMAL)
translate-mac64: dists/x86_64-mac/lou_translate

OBJS_TRANSLATE_MAC64 := $(foreach OBJ, $(OBJS_TRANSLATE), dists/x86_64-mac/objects/$(OBJ))

dists/x86_64-mac/lou_translate: $(OBJS_TRANSLATE_MAC64) | dists/x86_64-mac
	$(CC) -o $@ $(CFLAGS) $(OBJS_TRANSLATE_MAC64) $(LDFLAGS)

########################################

ifneq ($(HAS_JAVAC),1)

jars-mac64 jar-mac64 javadoc-jar-mac64 sources-jar-mac64: jar

else

dist-mac64: jars-mac64

FILES_RELEASE_MAC64 := \
	$(FILES_RELEASE_MAC64) \
	dists/x86_64-mac/liblouisAPH-jni-mac64-$(VERSION).dylib \
	dists/x86_64-mac/LibLouisAPH-mac64-$(VERSION).jar \
	dists/x86_64-mac/LibLouisAPH-sources-$(VERSION).jar \
	dists/x86_64-mac/LibLouisAPH-javadoc-$(VERSION).jar \

jars-mac64: jar-mac64 javadoc-jar-mac64 sources-jar-mac64

jar-mac64: CC = $(CC_MAC64)
jar-mac64: CPPFLAGS += $(JNI_INCLUDES) -I build/java
jar-mac64: CFLAGS += -O3 $(CWARNS_OPTIMAL)
jar-mac64: dists/x86_64-mac/LibLouisAPH-mac64-$(VERSION).jar

dists/x86_64-mac/objects/java:
	mkdir -p dists/x86_64-mac/objects/java/

dists/x86_64-mac/manifest.txt: | dists/x86_64-mac
	@echo Implementation-Name: LibLouisAPH Mac 64 bit >  $@
	@echo Implementation-Version: $(VERSION) >> $@
	@echo Implementation-Vender: American Printing House for the Blind >> $@
	@echo Implementation-URL: www.aph.org >> $@
	@echo Automatic-Module-Name:  org.aph.liblouisaph >> $@
	@echo >> $@

dists/x86_64-mac/liblouisaph.properties: | dists/x86_64-mac
	echo Library-Name=liblouisAPH-jni-mac64-$(VERSION).dylib > dists/x86_64-mac/liblouisaph.properties
	echo Table-Path=tables >> dists/x86_64-mac/liblouisaph.properties

dists/x86_64-mac/objects/java/interface-jni.o: java/interface-jni.c build/java/org_aph_liblouisaph_LibLouisAPH.h | dists/x86_64-mac/objects/java
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) $< $(LDFLAGS)

OBJS_JNI_MAC64 := $(foreach OBJ, $(OBJS_LIB) $(OBJS_LANG), dists/x86_64-mac/objects/$(OBJ))

dists/x86_64-mac/liblouisAPH-jni-mac64-$(VERSION).dylib: $(OBJS_JNI_MAC64) dists/x86_64-mac/objects/java/interface-jni.o | dists/x86_64-mac
	$(CC) -o $@ -shared $(OBJS_JNI_MAC64) dists/x86_64-mac/objects/java/interface-jni.o

FILES_JAR_MAC64 := -C dists/x86_64-mac liblouisAPH-jni-mac64-$(VERSION).dylib -C dists/x86_64-mac liblouisaph.properties

dists/x86_64-mac/LibLouisAPH-mac64-$(VERSION).jar: dists/x86_64-mac/manifest.txt dists/x86_64-mac/liblouisaph.properties dists/x86_64-mac/liblouisAPH-jni-mac64-$(VERSION).dylib build/java/org/aph/liblouisaph/Main.class | dists/x86_64-mac
	jar cfme $@ dists/x86_64-mac/manifest.txt org.aph.liblouisaph.Main $(CLASSES_JAR_BUILD) $(TABLES) $(FILES_JAR_MAC64)

sources-jar-mac64: dists/x86_64-mac/LibLouisAPH-sources-$(VERSION).jar

dists/x86_64-mac/LibLouisAPH-sources-$(VERSION).jar: build/LibLouisAPH-sources.jar | dists/x86_64-mac
	cp $< $@

javadoc-jar-mac64: dists/x86_64-mac/LibLouisAPH-javadoc-$(VERSION).jar

dists/x86_64-mac/LibLouisAPH-javadoc-$(VERSION).jar: build/LibLouisAPH-javadoc.jar | dists/x86_64-mac
	cp $< $@

endif

########################################

releases: release-mac64

release-mac64: dist-mac64 releases/LibLouisAPH-mac64-$(VERSION).zip

releases/LibLouisAPH-mac64-$(VERSION).zip: $(FILES_RELEASE_MAC64)
	mkdir -p releases/LibLouisAPH-mac64-$(VERSION)/
	cp -R $(FILES_RELEASE_MAC64) releases/LibLouisAPH-mac64-$(VERSION)/
	cp -R tables/ releases/LibLouisAPH-mac64-$(VERSION)/
	cp LibLouisAPH.h LICENSE-2.0.txt releases/LibLouisAPH-mac64-$(VERSION)/
	cd releases && zip -r -9 LibLouisAPH-mac64-$(VERSION).zip LibLouisAPH-mac64-$(VERSION)/

endif

################################################################################
#
#   Mac 32 bit
#
################################################################################

.PHONY: dist-mac32 dll-mac32 convert-mac32 table-mac32 translate-mac32
.PHONY: jars-mac32 jar-mac32 javadoc-jar-mac32 sources-jar-mac32
.PHONY: release-mac32

HAS_OSXCROSS32 := $(shell if (which $(CC_MAC32) > /dev/null 2>&1 ); then echo 1; else echo 0; fi )

ifneq ($(HAS_OSXCROSS32),1)

dist-mac32 dll-mac32 convert-mac32 table-mac32 translate-mac32: FORCE
	@echo missing $(CC_MAC32)
	@false

jars-mac32 jar-mac32 javadoc-jar-mac32 sources-jar-mac32: dist-mac32
release-mac32: dist-mac32

else

dists: dist-mac32

dist-mac32: dll-mac32 convert-mac32 table-mac32 translate-mac32

dists/i386-mac:
	mkdir -p dists/i386-mac/

FILES_RELEASE_MAC32 := \
	dists/i386-mac/liblouisAPH-mac32-$(VERSION).dylib \
	dists/i386-mac/lou_convert \
	dists/i386-mac/lou_table \
	dists/i386-mac/lou_translate \

dll-mac32: CC = $(CC_MAC32)
dll-mac32: CFLAGS += -O3 $(CWARNS_OPTIMAL)
dll-mac32: dists/i386-mac/liblouisAPH-mac32-$(VERSION).dylib

OBJS_DLL_MAC32 := $(foreach OBJ, $(OBJS_LIB) $(OBJS_LANG) $(OBJ_LIB_IFACE), dists/i386-mac/objects/$(OBJ))

dists/i386-mac/liblouisAPH-mac32-$(VERSION).dylib: $(OBJS_DLL_MAC32) | dists/i386-mac
	$(CC) -o $@ -shared $(CFLAGS) $(OBJS_DLL_MAC32)

convert-mac32: CC = $(CC_MAC32)
convert-mac32: CPPFLAGS += -I source/outputs -D OUTPUT
convert-mac32: CFLAGS += -O3 $(CWARNS_OPTIMAL)
convert-mac32: dists/i386-mac/lou_convert

OBJS_CONVERT_MAC32 := $(foreach OBJ, $(OBJS_CONVERT), dists/i386-mac/objects/$(OBJ))

dists/i386-mac/lou_convert: $(OBJS_CONVERT_MAC32) | dists/i386-mac
	$(CC) -o $@ $(CFLAGS) $(OBJS_CONVERT_MAC32) $(LDFLAGS)

table-mac32: CC = $(CC_MAC32)
table-mac32: CPPFLAGS += -I source/outputs -D OUTPUT
table-mac32: CFLAGS += -O3 $(CWARNS_OPTIMAL)
table-mac32: dists/i386-mac/lou_table

OBJS_TABLE_MAC32 := $(foreach OBJ, $(OBJS_TABLE), dists/i386-mac/objects/$(OBJ))

dists/i386-mac/lou_table: $(OBJS_TABLE_MAC32) | dists/i386-mac
	$(CC) -o $@ $(CFLAGS) $(OBJS_TABLE_MAC32) $(LDFLAGS)

translate-mac32: CC = $(CC_MAC32)
translate-mac32: CPPFLAGS += -I source/outputs -D OUTPUT
translate-mac32: CFLAGS += -O3 $(CWARNS_OPTIMAL)
translate-mac32: dists/i386-mac/lou_translate

OBJS_TRANSLATE_MAC32 := $(foreach OBJ, $(OBJS_TRANSLATE), dists/i386-mac/objects/$(OBJ))

dists/i386-mac/lou_translate: $(OBJS_TRANSLATE_MAC32) | dists/i386-mac
	$(CC) -o $@ $(CFLAGS) $(OBJS_TRANSLATE_MAC32) $(LDFLAGS)

########################################

ifneq ($(HAS_JAVAC),1)

jars-mac32 jar-mac32 javadoc-jar-mac32 sources-jar-mac32: jar

else

dist-mac32: jars-mac32

FILES_RELEASE_MAC32 := \
	$(FILES_RELEASE_MAC32) \
	dists/i386-mac/liblouisAPH-jni-mac32-$(VERSION).dylib \
	dists/i386-mac/LibLouisAPH-mac32-$(VERSION).jar \
	dists/i386-mac/LibLouisAPH-sources-$(VERSION).jar \
	dists/i386-mac/LibLouisAPH-javadoc-$(VERSION).jar \

jars-mac32: jar-mac32 javadoc-jar-mac32 sources-jar-mac32

jar-mac32: CC = $(CC_MAC32)
jar-mac32: CPPFLAGS += $(JNI_INCLUDES) -I build/java
jar-mac32: CFLAGS += -O3 $(CWARNS_OPTIMAL)
jar-mac32: dists/i386-mac/LibLouisAPH-mac32-$(VERSION).jar

dists/i386-mac/objects/java:
	mkdir -p dists/i386-mac/objects/java/

dists/i386-mac/manifest.txt: | dists/i386-mac
	@echo Implementation-Name: LibLouisAPH Mac 32 bit >  $@
	@echo Implementation-Version: $(VERSION) >> $@
	@echo Implementation-Vender: American Printing House for the Blind >> $@
	@echo Implementation-URL: www.aph.org >> $@
	@echo >> $@

dists/i386-mac/liblouisaph.properties: | dists/i386-mac
	echo Library-Name=liblouisAPH-jni-mac32-$(VERSION).dylib > dists/i386-mac/liblouisaph.properties
	echo Table-Path=tables >> dists/i386-mac/liblouisaph.properties

dists/i386-mac/objects/java/interface-jni.o: java/interface-jni.c build/java/org_aph_liblouisaph_LibLouisAPH.h | dists/i386-mac/objects/java
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) $< $(LDFLAGS)

OBJS_JNI_MAC32 := $(foreach OBJ, $(OBJS_LIB) $(OBJS_LANG), dists/i386-mac/objects/$(OBJ))

dists/i386-mac/liblouisAPH-jni-mac32-$(VERSION).dylib: $(OBJS_JNI_MAC32) dists/i386-mac/objects/java/interface-jni.o | dists/i386-mac
	$(CC) -o $@ -shared $(OBJS_JNI_MAC32) dists/i386-mac/objects/java/interface-jni.o

FILES_JAR_MAC32 := -C dists/i386-mac liblouisAPH-jni-mac32-$(VERSION).dylib -C dists/i386-mac liblouisaph.properties

dists/i386-mac/LibLouisAPH-mac32-$(VERSION).jar: dists/i386-mac/manifest.txt dists/i386-mac/liblouisaph.properties dists/i386-mac/liblouisAPH-jni-mac32-$(VERSION).dylib build/java/org/aph/liblouisaph/Main.class | dists/i386-mac
	jar cfme $@ dists/i386-mac/manifest.txt org.aph.liblouisaph.Main $(CLASSES_JAR_BUILD) $(TABLES) $(FILES_JAR_MAC32)

sources-jar-mac32: dists/i386-mac/LibLouisAPH-sources-$(VERSION).jar

dists/i386-mac/LibLouisAPH-sources-$(VERSION).jar: build/LibLouisAPH-sources.jar | dists/i386-mac
	cp $< $@

javadoc-jar-mac32: dists/i386-mac/LibLouisAPH-javadoc-$(VERSION).jar

dists/i386-mac/LibLouisAPH-javadoc-$(VERSION).jar: build/LibLouisAPH-javadoc.jar | dists/i386-mac
	cp $< $@

endif

########################################

releases: release-mac32

release-mac32: dist-mac32 releases/LibLouisAPH-mac32-$(VERSION).zip

releases/LibLouisAPH-mac32-$(VERSION).zip: $(FILES_RELEASE_MAC32)
	mkdir -p releases/LibLouisAPH-mac32-$(VERSION)/
	cp -R $(FILES_RELEASE_MAC32) releases/LibLouisAPH-mac32-$(VERSION)/
	cp -R tables/ releases/LibLouisAPH-mac32-$(VERSION)/
	cp LibLouisAPH.h LICENSE-2.0.txt releases/LibLouisAPH-mac32-$(VERSION)/
	cd releases && zip -r -9 LibLouisAPH-mac32-$(VERSION).zip LibLouisAPH-mac32-$(VERSION)/

endif

################################################################################
#
#   Generic Jar
#
################################################################################

.PHONY: dist-jar

ifneq ($(HAS_JAVAC),1)

dist-jar: jar

else

dists: dist-jar

dist-jar: dists/jar/LibLouisAPH-$(VERSION).jar

dists/jar/org/aph/liblouisaph/LibLouisAPH.class: java/org/aph/liblouisaph/LibLouisAPH.java java/org/aph/liblouisaph/LogCallback.java java/org/aph/liblouisaph/Translation.java | dists/jar
	javac -d dists/jar -classpath dists/jar -sourcepath java $<

dists/jar/manifest.txt: | dists/jar
	@echo Implementation-Name: LibLouisAPH >  $@
	@echo Implementation-Version: $(VERSION) >> $@
	@echo Implementation-Vender: American Printing House for the Blind >> $@
	@echo Implementation-URL: www.aph.org >> $@
	@echo Automatic-Module-Name:  org.aph.liblouisaph >> $@
	@echo >> $@

dists/jar/LibLouisAPH-$(VERSION).jar: dists/jar/manifest.txt dists/jar/org/aph/liblouisaph/LibLouisAPH.class | dists/jar
	jar cfm $@ dists/jar/manifest.txt -C dists/jar org/aph/liblouisaph/LibLouisAPH.class -C dists/jar org/aph/liblouisaph/LogCallback.class -C dists/jar org/aph/liblouisaph/Translation.class

dists/jar:
	mkdir -p dists/jar/

endif

################################################################################

.PHONY: deps

deps: build/Makedeps
	@cat build/Makedeps

build:
	mkdir -p build/

build/Makedeps: CPPFLAGS += -I . -I source/outputs -I test -D OUTPUT
build/Makedeps: | build
	@for BUILD_DIR in dists/x86_64-linux/objects dists/i686-linux/objects dists/x86_64-win/objects dists/i686-win/objects dists/x86_64-mac/objects dists/i386-mac/objects ; \
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
				if ( ls $$SOURCE_DIR/*.c > /dev/null 2>&1 ) ; \
				then \
					printf '\n' >> build/Makedeps ; \
					echo "$$BUILD_DIR/$$SOURCE_DIR:" >> build/Makedeps ; \
					printf "\tmkdir -p $$BUILD_DIR/$$SOURCE_DIR/\n" >> build/Makedeps ; \
					printf '\n' >> build/Makedeps ; \
					echo "$$BUILD_DIR/$$SOURCE_DIR/%.o: $$SOURCE_DIR/%.c | $$BUILD_DIR/$$SOURCE_DIR" >> build/Makedeps ; \
					printf '\t$$(CC) -o $$@ -c $$(CPPFLAGS) $$(CFLAGS) $$< $(LDFLAGS)\n' >> build/Makedeps ; \
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
				if ( ls $$SOURCE_DIR/*.c > /dev/null 2>&1 ) ; \
				then \
					printf '\n' >> build/Makedeps ; \
					echo "$$BUILD_DIR/$$SOURCE_DIR:" >> build/Makedeps ; \
					printf "\tmkdir -p $$BUILD_DIR/$$SOURCE_DIR/\n" >> build/Makedeps ; \
					printf '\n' >> build/Makedeps ; \
					echo "$$BUILD_DIR/$$SOURCE_DIR/%.o: $$SOURCE_DIR/%.c | $$BUILD_DIR/$$SOURCE_DIR" >> build/Makedeps ; \
					printf '\t$$(CC) -o $$@ -c $$(CPPFLAGS) $$(CFLAGS) $$< $(LDFLAGS)\n' >> build/Makedeps ; \
					printf '\n' >> build/Makedeps ; \
				fi ; \
			done ; \
		done ; \
	done ; \
	echo "#####  DLL" >> build/Makedeps ; \
	echo >> build/Makedeps ; \
	for BUILD_DIR in build/objects dists/x86_64-linux/objects ; \
	do \
		for SOURCE_DIR in source source/languages ; \
		do \
			for SRC in `find $$SOURCE_DIR -name '*.c'` ; \
			do \
				$(CC) -MT $$BUILD_DIR/dll/$${SRC%.c}.o -MM $$SRC $(CPPFLAGS) >> build/Makedeps ; \
			done ; \
			printf '\n' >> build/Makedeps ; \
			echo "$$BUILD_DIR/dll/$$SOURCE_DIR:" >> build/Makedeps ; \
			printf "\tmkdir -p $$BUILD_DIR/dll/$$SOURCE_DIR/\n" >> build/Makedeps ; \
			printf '\n' >> build/Makedeps ; \
			echo "$$BUILD_DIR/dll/$$SOURCE_DIR/%.o: $$SOURCE_DIR/%.c | $$BUILD_DIR/dll/$$SOURCE_DIR" >> build/Makedeps ; \
			printf '\t$$(CC) -o $$@ -c $$(CPPFLAGS) $$(CFLAGS) $$< $(LDFLAGS)\n' >> build/Makedeps ; \
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
			echo "$$BUILD_DIR/opt/$$SOURCE_DIR:" >> build/Makedeps ; \
			printf "\tmkdir -p $$BUILD_DIR/opt/$$SOURCE_DIR/\n" >> build/Makedeps ; \
			printf '\n' >> build/Makedeps ; \
			echo "$$BUILD_DIR/opt/$$SOURCE_DIR/%.o: $$SOURCE_DIR/%.c | $$BUILD_DIR/opt/$$SOURCE_DIR" >> build/Makedeps ; \
			printf '\t$$(CC) -o $$@ -c $$(CPPFLAGS) $$(CFLAGS) $$< $(LDFLAGS)\n' >> build/Makedeps ; \
			printf '\n' >> build/Makedeps ; \
		done ; \
	done \

################################################################################

.PHONY: clean cleanse distclean

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(MAKECMDGOALS),cleanse)
ifneq ($(MAKECMDGOALS),distclean)
ifneq ($(MAKECMDGOALS),javadoc)
ifneq ($(MAKECMDGOALS),javadoc-jar)
ifneq ($(MAKECMDGOALS),sources-jar)
-include build/Makedeps
endif
endif
endif
endif
endif
endif

clean: FORCE
	rm -rf build/

cleanse: clean
	rm -rf dists/
	rm -rf releases/

distclean: cleanse

################################################################################

FORCE:
