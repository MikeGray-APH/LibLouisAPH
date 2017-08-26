#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "LibLouisAPH.h"

/******************************************************************************/

static FILE *output;

static void log_callback(const int level, const char *message)
{
	switch(level)
	{
	case LOUIS_LOG_ALL:      fprintf(output, "ALL:  ");      break;
	case LOUIS_LOG_TRACE:    fprintf(output, "TRACE:  ");    break;
	case LOUIS_LOG_DEBUG:    fprintf(output, "DEBUG:  ");    break;
	case LOUIS_LOG_INFO:     fprintf(output, "INFO:  ");     break;
	case LOUIS_LOG_WARNING:  fprintf(output, "WARNING:  ");  break;
	case LOUIS_LOG_ERROR:    fprintf(output, "ERROR:  ");    break;
	case LOUIS_LOG_FATAL:    fprintf(output, "FATAL:  ");    break;
	}

	fprintf(output, "%s\n", message);
	fflush(output);
}

/*   copied from utf.h   */
static inline void utf16_copy(unsigned short *dst, const unsigned short *src, const int len)
{
	int i;

	for(i = 0; i < len; i++)
		dst[i] = src[i];
	dst[len - 1] = 0;
}

/*   copied from utf-convert.c   */
int utf16le_convert_to_utf8(char *cchars, const int cchars_max, const unsigned short *uchars, const int uchars_len)
{
	int crs, i;

	crs = 0;
	for(i = 0; i < uchars_len; i++)
	{
		if(uchars[i] == 0)
			break;
		else if(uchars[i] < 0x80)
		{
			/*   ensure there is enough space   */
			if(crs > cchars_max - 2)
				break;
			cchars[crs++] = (char)uchars[i] & 0x7f;
		}
		else if(uchars[i] < 0x800)
		{
			/*   ensure there is enough space   */
			if(crs > cchars_max - 3)
				break;
			cchars[crs++] = (uchars[i] >> 6) & 0x1f  | 0xc0;
			cchars[crs++] = (uchars[i]       & 0x3f) | 0x80;
		}

		/*   there will be no UTF16 sequences   */
		else// if(uchars[i] < 0x10000)
		{
			/*   ensure there is enough space   */
			if(crs > cchars_max - 4)
				break;
			cchars[crs++] = (uchars[i] >> 12) & 0x0f  | 0xe0;
			cchars[crs++] = ((uchars[i] >> 6) & 0x3f) | 0x80;
			cchars[crs++] = (uchars[i]        & 0x3f) | 0x80;
		}
		//else if(uchars[i] < 0x110000)
		//{
		//	/*   ensure there is enough space   */
		//	if(crs > cchars_max - 5)
		//		break;
		//	cchars[crs++] = (uchars[i] >> 18)  & 0x07  | 0xf0;
		//	cchars[crs++] = ((uchars[i] >> 12) & 0x3f) | 0x80;
		//	cchars[crs++] = ((uchars[i] >> 6)  & 0x3f) | 0x80;
		//	cchars[crs++] = (uchars[i]         & 0x3f) | 0x80;
		//}
		//else
		//	return 0;
	}

	cchars[crs] = 0;
	return crs;
}

/******************************************************************************/

int main(void)
{
	unsigned short trans[] = u"⠕⠪⠀⠕⠪⠕⠪⠀⠕⠕⠪⠪⠀⠕⠪⠕⠪⠀⠕⠪";
	int trans_chars_map[] = {0,2,3,5,7,8,8,8,12,13,15,17,18};
	int trans_dots_map[] = {0,0,1,2,2,3,3,4,5,5,5,5,8,9,9,10,10,11,12,12};
	unsigned short snart[] = u"x xx xxx xx x";
	unsigned short convert[] = u">< ><>< >><< ><>< ><";
	unsigned short trevnoc[] = u">< ><>< >><< ><>< ><";

	void (*callback)(const int level, const char *message);
	int chars_to_dots_map[0x100], dots_to_chars_map[0x100], cursor;
	char cchars[0x100];
	unsigned short uchars[0x100];
	int uchars_len, i;

	memset(cchars, 0, 0x100);
	memset(uchars, 0, 0x100 * sizeof(unsigned short));
	memset(chars_to_dots_map, 0, 0x100 * sizeof(int));
	memset(dots_to_chars_map, 0, 0x100 * sizeof(int));

	output = fopen("build/test/output-link.txt", "w");
	if(!output)
		output = stdout;

	fputs("testing link\n\n", output);
	if(output != stdout)
		puts("testing link");


	louis_get_version(cchars, 0x100);
	fprintf(output, "louis_get_version         = %s\n", cchars);


	fprintf(output, "louis_get_log_callback    = ");
	if(output != stdout)
		printf("louis_get_log_callback:  ");
	callback = louis_get_log_callback();
	fprintf(output, "0x%lx\n", (unsigned long)callback);
	if(callback)
	{
		fprintf(output, "ERROR:  louis_get_log_callback\n");
		if(output != stdout)
			puts("FAIL");
		return 1;
	}
	if(output != stdout)
		puts("PASS");


	fprintf(output, "louis_set_log_callback:  := 0x%lx\n", (unsigned long)log_callback);
	if(output != stdout)
		printf("louis_set_log_callback:  ");
	louis_set_log_callback(log_callback);

	fprintf(output, "louis_get_log_callback");
	callback = louis_get_log_callback();
	fprintf(output, "    = 0x%lx\n", (unsigned long)callback);
	if(callback != log_callback)
	{
		fprintf(output, "ERROR:  louis_get_log_callback\n");
		if(output != stdout)
			puts("FAIL");
		return 1;
	}
	if(output != stdout)
		puts("PASS");


	fprintf(output, "louis_get_paths           = ");
	if(output != stdout)
		printf("louis_get_paths:  ");
	if(louis_get_paths(cchars, 0x100))
	{
		fprintf(output, "ERROR:  louis_get_paths\n");
		if(output != stdout)
			puts("FAIL");
		return 1;
	}
	fprintf(output, "%s\n", cchars);
	if(cchars[0])
	{
		fprintf(output, "ERROR:  louis_get_paths null\n");
		if(output != stdout)
			puts("FAIL");
		return 1;
	}
	if(output != stdout)
		puts("PASS");


	fputs("louis_set_paths          := tables\n", output);
	if(output != stdout)
		printf("louis_set_paths:  ");
	if(!louis_set_paths("tables"))
	{
		fprintf(output, "ERROR:  louis_set_paths\n");
		if(output != stdout)
			puts("FAIL");
		return 1;
	}
	fprintf(output, "louis_get_paths           = ");
	if(!louis_get_paths(cchars, 0x100))
	{
		fprintf(output, "ERROR:  louis_get_paths\n");
		if(output != stdout)
			puts("FAIL");
		return 1;
	}
	fprintf(output, "%s\n", cchars);
	if(strncmp(cchars, "tables", 7))
	{
		fprintf(output, "ERROR:  louis_get_paths \"tables\"\n");
		if(output != stdout)
			puts("FAIL");
		return 1;
	}
	if(output != stdout)
		puts("PASS");


	fputs("louis_add_paths          := test/tables\n", output);
	if(output != stdout)
		printf("louis_add_paths:  ");
	if(!louis_add_paths("test/tables"))
	{
		fprintf(output, "ERROR:  louis_add_paths\n");
		if(output != stdout)
			puts("FAIL");
		return 1;
	}
	fprintf(output, "louis_get_paths           = ");
	if(!louis_get_paths(cchars, 0x100))
	{
		fprintf(output, "ERROR:  louis_get_paths\n");
		if(output != stdout)
			puts("FAIL");
		return 1;
	}
	fprintf(output, "%s\n", cchars);
	if(strncmp(cchars, "tables:test/tables", 19))
	{
		fprintf(output, "ERROR:  louis_get_paths \"tables:test/tables\"\n");
		if(output != stdout)
			puts("FAIL");
		return 1;
	}
	if(output != stdout)
		puts("PASS");


	fprintf(output, "louis_translate_forward   = ");
	if(output != stdout)
		printf("louis_translate_forward:  ");
	cursor = 7;
	uchars_len = louis_translate_forward(uchars, 0x100, u"x xx xxx xx x", 13, "link.rst", NULL, chars_to_dots_map, dots_to_chars_map, &cursor);
	if(uchars_len < 1)
	{
		fprintf(output, "ERROR:  louis_translate_forward\n");
		if(output != stdout)
			puts("FAIL");
		return 1;
	}
	utf16le_convert_to_utf8(cchars, 0x100, uchars, uchars_len);
	fprintf(output, "%s\n", cchars);
	if(uchars_len != 20)
	{
		fprintf(output, "ERROR:  louis_translate_forward length\n");
		if(output != stdout)
			puts("FAIL");
		return 1;
	}
	for(i = 0; i < uchars_len; i++)
	if(trans[i] != uchars[i])
	{
		fprintf(output, "ERROR:  louis_translate_forward translation\n");
		if(output != stdout)
			puts("FAIL");
		return 1;
	}
	for(i = 0; i < 13; i++)
	if(chars_to_dots_map[i] != trans_chars_map[i])
	{
		fprintf(output, "ERROR:  louis_translate_forward chars_to_dots_map\n");
		if(output != stdout)
			puts("FAIL");
		return 1;
	}
	for(i = 0; i < uchars_len; i++)
	if(dots_to_chars_map[i] != trans_dots_map[i])
	{
		fprintf(output, "ERROR:  louis_translate_forward dots_to_chars_map\n");
		if(output != stdout)
			puts("FAIL");
		return 1;
	}
	if(cursor != 8)
	{
		fprintf(output, "ERROR:  louis_translate_forward cursor\n");
		if(output != stdout)
			puts("FAIL");
		return 1;
	}
	if(output != stdout)
		puts("PASS");


	fprintf(output, "louis_translate_backward  = ");
	if(output != stdout)
		printf("louis_translate_backward:  ");
	cursor = 8;
	uchars_len = louis_translate_backward(uchars, 0x100, u"⠕⠪ ⠕⠪⠕⠪ ⠕⠕⠪⠪ ⠕⠪⠕⠪ ⠕⠪", 20, "link.rst", NULL, chars_to_dots_map, dots_to_chars_map, &cursor);
	if(uchars_len < 1)
	{
		fprintf(output, "ERROR:  louis_translate_backward\n");
		if(output != stdout)
			puts("FAIL");
		return 1;
	}
	utf16le_convert_to_utf8(cchars, 0x100, uchars, uchars_len);
	fprintf(output, "%s\n", cchars);
	if(uchars_len != 13)
	{
		fprintf(output, "ERROR:  louis_translate_backward length\n");
		if(output != stdout)
			puts("FAIL");
		return 1;
	}
	for(i = 0; i < uchars_len; i++)
	if(snart[i] != (char)uchars[i])
	{
		fprintf(output, "ERROR:  louis_translate_backward translation\n");
		if(output != stdout)
			puts("FAIL");
		return 1;
	}
	for(i = 0; i < 20; i++)
	if(chars_to_dots_map[i] != trans_dots_map[i])
	{
		fprintf(output, "ERROR:  louis_translate_backward chars_to_dots_map\n");
		if(output != stdout)
			puts("FAIL");
		return 1;
	}
	for(i = 0; i < uchars_len; i++)
	if(dots_to_chars_map[i] != trans_chars_map[i])
	{
		fprintf(output, "ERROR:  louis_translate_backward dots_to_chars_map\n");
		if(output != stdout)
			puts("FAIL");
		return 1;
	}
	if(cursor != 5)
	{
		fprintf(output, "ERROR:  louis_translate_backward cursor\n");
		if(output != stdout)
			puts("FAIL");
		return 1;
	}
	if(output != stdout)
		puts("PASS");


	fprintf(output, "louis_convert_to          = ");
	if(output != stdout)
		printf("louis_convert_to:  ");
	utf16_copy(uchars, trans, 21);
	if(!louis_convert_to(uchars, 20, "link.cvt"))
	{
		fprintf(output, "ERROR:  louis_convert_to\n");
		if(output != stdout)
			puts("FAIL");
		return 1;
	}
	utf16le_convert_to_utf8(cchars, 0x100, uchars, 20);
	fprintf(output, "%s\n", cchars);
	for(i = 0; i < 20; i++)
	if(convert[i] != uchars[i])
	{
		fprintf(output, "ERROR:  louis_convert_to conversion\n");
		if(output != stdout)
			puts("FAIL");
		return 1;
	}
	if(output != stdout)
		puts("PASS");


	fprintf(output, "louis_convert_from        = ");
	if(output != stdout)
		printf("louis_convert_from:  ");
	utf16_copy(uchars, trevnoc, 21);
	if(!louis_convert_from(uchars, 20, "link.cvt"))
	{
		fprintf(output, "ERROR:  louis_convert_from\n");
		if(output != stdout)
			puts("FAIL");
		return 1;
	}
	utf16le_convert_to_utf8(cchars, 0x100, uchars, 20);
	fprintf(output, "%s\n", cchars);
	for(i = 0; i < 20; i++)
	if(trans[i] != uchars[i])
	{
		fprintf(output, "ERROR:  louis_convert_from conversion\n");
		if(output != stdout)
			puts("FAIL");
		return 1;
	}
	if(output != stdout)
		puts("PASS");


	if(output != stdout)
	{
		puts("");
		fclose(output);
	}

	return 0;
}
