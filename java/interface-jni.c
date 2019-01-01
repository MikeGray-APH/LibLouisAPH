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
#include <string.h>

#include <jni.h>
#include "LibLouisAPH-jni.h"

#include "translate.h"
#include "lookup.h"
#include "log.h"

//#define OUTPUT_IS_COPIED

/******************************************************************************/

static JNIEnv *lookup_env = NULL;
static jclass lookup_class = NULL;
static jmethodID lookup_hook = NULL;

static int lookup_hook_function(char *path, const int path_max, const char *file_name, const int file_name_len ATTRIBUTE_UNUSED)
{
	jstring file_name_string;
	jcharArray path_array;
	jchar *path_chars;
	jint status;
	int i;

	if(lookup_env && lookup_class && lookup_hook)
	{
		file_name_string = (*lookup_env)->NewStringUTF(lookup_env, file_name);
		path_array = (*lookup_env)->NewCharArray(lookup_env, path_max);
		status = (*lookup_env)->CallStaticIntMethod(lookup_env, lookup_class, lookup_hook, path_array, file_name_string);
		if(status)
		{
			path_chars = (*lookup_env)->GetCharArrayElements(lookup_env, path_array, NULL);
			for(i = 0; i < path_max; i++)
				path[i] = (char)path_chars[i];
			path[path_max - 1] = 0;
			(*lookup_env)->ReleaseCharArrayElements(lookup_env, path_array, path_chars, 0);
			return 1;
		}
	}

	return 0;
}

JNIEXPORT void JNICALL
Java_org_aph_liblouisaph_LibLouisAPH_louis_1set_1lookup_1hook(JNIEnv *env, jclass this_class)
{
	jclass no_method_class;
	jthrowable exception;
	jboolean boolean;

	lookup_env = env;

	lookup_class = this_class;
	if(lookup_class == NULL)
		return;

	no_method_class = (*env)->FindClass(env, "java/lang/NoSuchMethodException");
	if(no_method_class == NULL)
		return;

	lookup_hook = (*env)->GetStaticMethodID(env, lookup_class, "lookupHook", "([CLjava/lang/String;)I");
	exception = (*env)->ExceptionOccurred(env);
	if(exception != NULL)
	{
		boolean = (*env)->IsInstanceOf(env, exception, no_method_class);
		if(boolean != JNI_TRUE)
			(*env)->ExceptionClear(env);
		return;
	}

	lookup_set_hook(lookup_hook_function);
}

/******************************************************************************/

static JNIEnv *log_env = NULL;
static jclass log_class = NULL;
static jmethodID log_callback = NULL;

static void log_callback_function(const int level, const char *message)
{
	jstring string;

	if(log_env && log_class && log_callback)
	{
		string = (*log_env)->NewStringUTF(log_env, message);
		(*log_env)->CallStaticVoidMethod(log_env, log_class, log_callback, level, string);
	}
}

JNIEXPORT void JNICALL
Java_org_aph_liblouisaph_LibLouisAPH_louis_1set_1log_1callback(JNIEnv *env, jclass this_class ATTRIBUTE_UNUSED)
{
	jclass no_method_class;
	jthrowable exception;
	jboolean boolean;

	log_env = env;

	log_class = this_class;//(*env)->FindClass(env, "org/aph/liblouisaph/LibLouisAPH");
	if(log_class == NULL)
	{
		//puts("\nERROR:  log_class == NULL");
		return;
	}

	no_method_class = (*env)->FindClass(env, "java/lang/NoSuchMethodException");
	if(no_method_class == NULL)
	{
		//puts("\nERROR:  no_method_class == NULL");
		return;
	}

	log_callback = (*env)->GetStaticMethodID(env, log_class, "logCallback", "(ILjava/lang/String;)V");
	exception = (*env)->ExceptionOccurred(env);
	if(exception != NULL)
	{
		boolean = (*env)->IsInstanceOf(env, exception, no_method_class);
		if(boolean != JNI_TRUE)
		{
			//puts("\nERROR:  no_method_class thrown");
			(*env)->ExceptionClear(env);
		}
		return;
	}

	log_set_callback(log_callback_function);
}

/******************************************************************************/

JNIEXPORT jint JNICALL
Java_org_aph_liblouisaph_LibLouisAPH_louis_1get_1version_1length(JNIEnv *env ATTRIBUTE_UNUSED, jclass this_class ATTRIBUTE_UNUSED)
{
	return strlen(VERSION);
}

JNIEXPORT jint JNICALL
Java_org_aph_liblouisaph_LibLouisAPH_louis_1get_1version(JNIEnv *env, jclass this_class ATTRIBUTE_UNUSED, jcharArray version_array)
{
	jchar *version_chars;
	char version[] = VERSION;
	int version_len, version_max, i;

#ifdef OUTPUT_IS_COPIED

	jboolean is_copy = JNI_FALSE;
	version_chars = (*env)->GetCharArrayElements(env, version_array, &is_copy);
	switch(is_copy)
	{
	case JNI_TRUE:   log_message(LOG_INFO, "louis_get_version:  not copied");  break;
	case JNI_FALSE:  log_message(LOG_INFO, "louis_get_version:  copied");      break;
	default:         log_message(LOG_INFO, "louis_get_version:  copied?");    break;
	}

#else

	version_chars = (*env)->GetCharArrayElements(env, version_array, NULL);

#endif

	version_max = (*env)->GetArrayLength(env, version_array);

	version_len = strlen(version);
	if(version_len > version_max - 1)
		version_len = version_max - 1;
	for(i = 0; i < version_len; i++)
		version_chars[i] = version[i];
	version_chars[version_len] = 0;

	(*env)->ReleaseCharArrayElements(env, version_array, version_chars, 0);

	return version_len;
}

/******************************************************************************/

JNIEXPORT jint JNICALL
Java_org_aph_liblouisaph_LibLouisAPH_louis_1get_1paths_1length(JNIEnv *env ATTRIBUTE_UNUSED, jclass this_class ATTRIBUTE_UNUSED)
{
	return lookup_get_paths_length();
}

JNIEXPORT jint JNICALL
Java_org_aph_liblouisaph_LibLouisAPH_louis_1get_1paths(JNIEnv *env, jclass this_class ATTRIBUTE_UNUSED, jcharArray paths_array)
{
	jchar *paths_chars;
	int paths_len, paths_max, i;
	char *paths;

#ifdef OUTPUT_IS_COPIED

	jboolean is_copy = JNI_FALSE;
	paths_chars = (*env)->GetCharArrayElements(env, paths_array, &is_copy);
	switch(is_copy)
	{
	case JNI_TRUE:   log_message(LOG_INFO, "louis_get_paths:  not copied");  break;
	case JNI_FALSE:  log_message(LOG_INFO, "louis_get_paths:  copied");      break;
	default:         log_message(LOG_INFO, "louis_get_paths:  copied?");    break;
	}

#else

	paths_chars = (*env)->GetCharArrayElements(env, paths_array, NULL);

#endif

	paths_max = (*env)->GetArrayLength(env, paths_array);

	paths_len = lookup_get_paths_length();
	if(paths_len < 1)
		return 0;
	if(paths_len > paths_max - 1)
		paths_len = paths_max - 1;
	paths = MALLOC(paths_len + 1);
	lookup_get_paths(paths, paths_len + 1);
	for(i = 0; i < paths_len; i++)
		paths_chars[i] = paths[i];

	(*env)->ReleaseCharArrayElements(env, paths_array, paths_chars, 0);
	FREE(paths);

	return paths_len;
}

JNIEXPORT jint JNICALL
Java_org_aph_liblouisaph_LibLouisAPH_louis_1set_1paths(JNIEnv *env, jclass this_class ATTRIBUTE_UNUSED, jstring paths_string)
{
	const char *paths_chars;
	int status;

#ifdef OUTPUT_IS_COPIED

	jboolean is_copy = JNI_FALSE;
	paths_chars = (*env)->GetStringUTFChars(env, paths_string, &is_copy);
	switch(is_copy)
	{
	case JNI_TRUE:   log_message(LOG_INFO, "louis_set_paths:  not copied");  break;
	case JNI_FALSE:  log_message(LOG_INFO, "louis_set_paths:  copied");      break;
	default:         log_message(LOG_INFO, "louis_set_paths:  copied?");    break;
	}

#else

	paths_chars = (*env)->GetStringUTFChars(env, paths_string, NULL);

#endif

	status = lookup_set_paths(paths_chars);
	(*env)->ReleaseStringUTFChars(env, paths_string, paths_chars);
	return status;
}

JNIEXPORT jint JNICALL
Java_org_aph_liblouisaph_LibLouisAPH_louis_1add_1paths(JNIEnv *env, jclass this_class ATTRIBUTE_UNUSED, jstring paths_string)
{
	const char *paths_chars;
	int status;

#ifdef OUTPUT_IS_COPIED

	jboolean is_copy = JNI_FALSE;
	paths_chars = (*env)->GetStringUTFChars(env, paths_string, &is_copy);
	switch(is_copy)
	{
	case JNI_TRUE:   log_message(LOG_INFO, "louis_add_paths:  not copied");  break;
	case JNI_FALSE:  log_message(LOG_INFO, "louis_add_paths:  copied");      break;
	default:         log_message(LOG_INFO, "louis_add_paths:  copied?");    break;
	}

#else

	paths_chars = (*env)->GetStringUTFChars(env, paths_string, NULL);

#endif

	status = lookup_add_paths(paths_chars);
	(*env)->ReleaseStringUTFChars(env, paths_string, paths_chars);
	return status;
}

/******************************************************************************/

/*   copied from interface.c   */
static int lookup_and_translate(
	Unicode *dots,
	const int dots_len,
	const Unicode *chars,
	const int chars_len,
	const char *table_names,
	const char *conversion_name,
	const enum rule_direction direction,
	int *chars_to_dots_map,
	int *dots_to_chars_map,
	int *cursor)
{
	struct table **tables;
	struct conversion *conversion;
	int status, table_cnt;

	ASSERT(dots)
	ASSERT(dots_len > 0)
	ASSERT(chars)
	ASSERT(chars_len > 0)
	ASSERT(table_names)

	tables = lookup_tables(&table_cnt, table_names);
	if(!tables)
		return 0;

	if(conversion_name)
	{
		conversion = lookup_conversion(conversion_name);
		if(!conversion)
		{
			FREE(tables);
			return 0;
		}
	}
	else
		conversion = NULL;

	status = translate_start(
		dots, dots_len, chars, chars_len,
		(const struct table * const*)tables, table_cnt, conversion, direction,
		chars_to_dots_map, dots_to_chars_map, cursor);

	FREE(tables);

	return status;
}

JNIEXPORT jint JNICALL
Java_org_aph_liblouisaph_LibLouisAPH_louis_1translate(
	JNIEnv *env,
	jclass this_class ATTRIBUTE_UNUSED,
	jcharArray dots_array,
	jstring chars_string,
	jstring tables_string,
	jstring conversion_string,
	jint direction_int,
	jintArray chars_to_dots_map_array,
	jintArray dots_to_chars_map_array,
	jintArray cursor_map_array)
{
	jchar *dots_chars;
	const jchar *chars_chars;
	const char *tables_chars, *conversion_chars;
	enum rule_direction direction;
	int dots_len, chars_len, *chars_to_dots_map_ints, *dots_to_chars_map_ints, *cursor_map_int, status;

#ifdef DEBUG

	if(sizeof(int) != sizeof(jint))
	{
		log_message(LOG_FATAL, "louis_translate:  sizeof(int) = %u != sizeof(jint) = %u", sizeof(int), sizeof(jint));
		return -1;
	}
	if(sizeof(Unicode) != sizeof(jchar))
	{
		log_message(LOG_FATAL, "louis_translate:  sizeof(Unicode) = %u != sizeof(jchar) = %u", sizeof(Unicode), sizeof(jchar));
		return -1;
	}

#endif

#ifdef OUTPUT_IS_COPIED

	log_message(0, NULL);
	jboolean is_copy = JNI_FALSE;
	dots_chars = (*env)->GetCharArrayElements(env, dots_array, &is_copy);
	switch(is_copy)
	{
	case JNI_TRUE:   log_message(LOG_INFO, "louis_translate:  not copied");  break;
	case JNI_FALSE:  log_message(LOG_INFO, "louis_translate:  copied");      break;
	default:         log_message(LOG_INFO, "louis_translate:  copied?");    break;
	}

	is_copy = JNI_FALSE;
	chars_chars = (*env)->GetStringChars(env, chars_string, &is_copy);
	switch(is_copy)
	{
	case JNI_TRUE:   log_message(LOG_INFO, "louis_translate:  not copied");  break;
	case JNI_FALSE:  log_message(LOG_INFO, "louis_translate:  copied");      break;
	default:         log_message(LOG_INFO, "louis_translate:  copied?");    break;
	}

	is_copy = JNI_FALSE;
	tables_chars = (*env)->GetStringUTFChars(env, tables_string, &is_copy);
	switch(is_copy)
	{
	case JNI_TRUE:   log_message(LOG_INFO, "louis_translate:  not copied");  break;
	case JNI_FALSE:  log_message(LOG_INFO, "louis_translate:  copied");      break;
	default:         log_message(LOG_INFO, "louis_translate:  copied?");    break;
	}
#else

	dots_chars = (*env)->GetCharArrayElements(env, dots_array, NULL);
	chars_chars = (*env)->GetStringChars(env, chars_string, NULL);
	tables_chars = (*env)->GetStringUTFChars(env, tables_string, NULL);

#endif

	dots_len = (*env)->GetArrayLength(env, dots_array);
	chars_len = (*env)->GetStringLength(env, chars_string);

	conversion_chars = NULL;
	if(conversion_string)
		conversion_chars = (*env)->GetStringUTFChars(env, conversion_string, NULL);

#if defined _WIN32

	jint *chars_to_dots_map_jints, *dots_to_chars_map_jints, *cursor_map_jint;

	chars_to_dots_map_jints = NULL;
	chars_to_dots_map_ints = NULL;
	if(chars_to_dots_map_array)
	{
		chars_to_dots_map_jints = (*env)->GetIntArrayElements(env, chars_to_dots_map_array, NULL);
		chars_to_dots_map_ints = MALLOC(chars_len * sizeof(int));
	}

	dots_to_chars_map_jints = NULL;
	dots_to_chars_map_ints = NULL;
	if(dots_to_chars_map_array)
	{
		dots_to_chars_map_jints = (*env)->GetIntArrayElements(env, dots_to_chars_map_array, NULL);
		dots_to_chars_map_ints = MALLOC(dots_len * sizeof(int));
	}

	cursor_map_jint = NULL;
	cursor_map_int = NULL;
	if(cursor_map_array)
	{
		cursor_map_jint = (*env)->GetIntArrayElements(env, cursor_map_array, NULL);
		cursor_map_int = MALLOC(sizeof(int));
	}

#else

	chars_to_dots_map_ints = NULL;
	if(chars_to_dots_map_array)
		chars_to_dots_map_ints = (*env)->GetIntArrayElements(env, chars_to_dots_map_array, NULL);
	dots_to_chars_map_ints = NULL;
	if(dots_to_chars_map_array)
		dots_to_chars_map_ints = (*env)->GetIntArrayElements(env, dots_to_chars_map_array, NULL);
	cursor_map_int = NULL;
	if(cursor_map_array)
		cursor_map_int = (*env)->GetIntArrayElements(env, cursor_map_array, NULL);

#endif

	if(direction_int > 0)
		direction = FORWARD;
	else
		direction = BACKWARD;
	status = lookup_and_translate(
		dots_chars, dots_len, chars_chars, chars_len,
		tables_chars, conversion_chars, direction,
		chars_to_dots_map_ints, dots_to_chars_map_ints, cursor_map_int);

	(*env)->ReleaseCharArrayElements(env, dots_array, dots_chars, 0);
	(*env)->ReleaseStringChars(env, chars_string, chars_chars);
	(*env)->ReleaseStringUTFChars(env, tables_string, tables_chars);
	if(conversion_chars)
		(*env)->ReleaseStringUTFChars(env, conversion_string, conversion_chars);

#if defined _WIN32

	int i;

	if(chars_to_dots_map_jints)
	{
		if(chars_to_dots_map_ints)
		{
			for(i = 0; i < chars_len; i++)
				chars_to_dots_map_jints[i] = chars_to_dots_map_ints[i];
			FREE(chars_to_dots_map_ints);
		}
		(*env)->ReleaseIntArrayElements(env, chars_to_dots_map_array, chars_to_dots_map_jints, 0);
	}

	if(dots_to_chars_map_jints)
	{
		if(dots_to_chars_map_ints)
		{
			for(i = 0; i < chars_len; i++)
				dots_to_chars_map_jints[i] = dots_to_chars_map_ints[i];
			FREE(dots_to_chars_map_ints);
		}
		(*env)->ReleaseIntArrayElements(env, dots_to_chars_map_array, dots_to_chars_map_jints, 0);
	}

	if(cursor_map_jint)
	{
		if(cursor_map_int)
		{
			cursor_map_jint[0] = cursor_map_int[0];
			FREE(cursor_map_int);
		}
		(*env)->ReleaseIntArrayElements(env, cursor_map_array, cursor_map_jint, 0);
	}

#else

	if(chars_to_dots_map_ints)
		(*env)->ReleaseIntArrayElements(env, chars_to_dots_map_array, chars_to_dots_map_ints, 0);
	if(dots_to_chars_map_ints)
		(*env)->ReleaseIntArrayElements(env, dots_to_chars_map_array, dots_to_chars_map_ints, 0);
	if(cursor_map_int)
		(*env)->ReleaseIntArrayElements(env, cursor_map_array, cursor_map_int, 0);

#endif

	return status;
}

/******************************************************************************/

JNIEXPORT jint JNICALL
Java_org_aph_liblouisaph_LibLouisAPH_louis_1convert(
	JNIEnv *env,
	jclass this_class ATTRIBUTE_UNUSED,
	jcharArray cells_array,
	jstring conversion_string,
	jint direction_int)
{
	struct conversion *conversion;
	jchar *cells_chars;
	const char *conversion_chars;
	int cells_len;

#ifdef OUTPUT_IS_COPIED

	log_message(0, NULL);
	jboolean is_copy = JNI_FALSE;
	cells_chars = (*env)->GetCharArrayElements(env, cells_array, &is_copy);
	switch(is_copy)
	{
	case JNI_TRUE:   log_message(LOG_INFO, "louis_get_version:  not copied");  break;
	case JNI_FALSE:  log_message(LOG_INFO, "louis_get_version:  copied");      break;
	default:         log_message(LOG_INFO, "louis_get_version:  copied?");    break;
	}

	is_copy = JNI_FALSE;
	conversion_chars = (*env)->GetStringUTFChars(env, conversion_string, &is_copy);
	switch(is_copy)
	{
	case JNI_TRUE:   log_message(LOG_INFO, "louis_get_version:  not copied");  break;
	case JNI_FALSE:  log_message(LOG_INFO, "louis_get_version:  copied");      break;
	default:         log_message(LOG_INFO, "louis_get_version:  copied?");    break;
	}
#else

	cells_chars = (*env)->GetCharArrayElements(env, cells_array, NULL);
	conversion_chars = (*env)->GetStringUTFChars(env, conversion_string, NULL);

#endif

	cells_len = (*env)->GetArrayLength(env, cells_array);

	conversion = lookup_conversion(conversion_chars);
	if(!conversion)
	{
		log_message(LOG_ERROR, "unable to open conversion %s\n", conversion_chars);
		return 0;
	}
	if(direction_int > 0)
		conversion_convert_to(cells_chars, cells_len, conversion);
	else
		conversion_convert_from(cells_chars, cells_len, conversion);

	(*env)->ReleaseCharArrayElements(env, cells_array, cells_chars, 0);
	(*env)->ReleaseStringUTFChars(env, conversion_string, conversion_chars);

	return 1;
}

/******************************************************************************/
