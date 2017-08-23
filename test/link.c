#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "LibLouisAPH.h"

/******************************************************************************/

static void log_callback(const int level, const char *message)
{
	switch(level)
	{
	case LOUIS_LOG_ALL:      fprintf(stderr, "ALL:  ");      break;
	case LOUIS_LOG_TRACE:    fprintf(stderr, "TRACE:  ");    break;
	case LOUIS_LOG_DEBUG:    fprintf(stderr, "DEBUG:  ");    break;
	case LOUIS_LOG_INFO:     fprintf(stderr, "INFO:  ");     break;
	case LOUIS_LOG_WARNING:  fprintf(stderr, "WARNING:  ");  break;
	case LOUIS_LOG_ERROR:    fprintf(stderr, "ERROR:  ");    break;
	case LOUIS_LOG_FATAL:    fprintf(stderr, "FATAL:  ");    break;
	}

	fprintf(stderr, "%s\n", message);
	fflush(stderr);
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
	void (*callback)(const int level, const char *message);
	unsigned short trans[] = u"⠕⠪⠀⠕⠪⠕⠪⠀⠕⠕⠪⠪⠀⠕⠪⠕⠪⠀⠕⠪";
	unsigned short snart[] = u"x xx xxx xx x";
	unsigned short convert[] = u">< ><>< >><< ><>< ><";
	unsigned short trevnoc[] = u">< ><>< >><< ><>< ><";

	char cchars[0x100] = {0};
	unsigned short uchars[0x100] = {0};
	int uchars_len, i;

	puts("test link");

	puts("louis_set_log_callback");
	louis_set_log_callback(log_callback);

	printf("louis_get_log_callback");
	callback = louis_get_log_callback();
	printf("    = 0x%lx\n", (unsigned long)callback);
	if(callback != log_callback)
	{
		fprintf(stderr, "ERROR:  louis_get_log_callback\n");
		return 1;
	}

	louis_get_version(cchars, 0x100);
	printf("version                   = %s\n", cchars);

	puts("louis_set_paths          := test");
	if(!louis_set_paths("test"))
	{
		fprintf(stderr, "ERROR:  louis_set_paths\n");
		return 1;
	}

	printf("louis_get_paths");
	fflush(stdout);
	if(!louis_get_paths(cchars, 0x100))
	{
		fprintf(stderr, "\nERROR:  louis_get_paths\n");
		return 1;
	}
	printf("           = %s\n", cchars);
	if(strncmp(cchars, "test", 5))
	{
		fprintf(stderr, "\nERROR:  louis_get_paths not \"test\"\n");
		return 1;
	}

	puts("louis_add_paths          := test/tables");
	if(!louis_add_paths("test/tables"))
	{
		fprintf(stderr, "ERROR:  louis_add_paths\n");
		return 1;
	}

	printf("louis_get_paths");
	fflush(stdout);
	if(!louis_get_paths(cchars, 0x100))
	{
		fprintf(stderr, "\nERROR:  louis_get_paths\n");
		return 1;
	}
	printf("           = %s\n", cchars);
	if(strncmp(cchars, "test:test/tables", 17))
	{
		fprintf(stderr, "\nERROR:  louis_get_paths not \"test:test/tables\"\n");
		return 1;
	}


	printf("louis_translate_forward");
	fflush(stdout);
	uchars_len = louis_translate_forward(uchars, 0x100, u"x xx xxx xx x", 13, "link.rst", NULL, NULL, NULL, NULL);
	if(uchars_len < 1)
	{
		fprintf(stderr, "\nERROR:  louis_translate_forward FAIL\n");
		return 1;
	}
	utf16le_convert_to_utf8(cchars, 0x100, uchars, uchars_len);
	printf("   = %s\n", cchars);

	if(uchars_len != 20)
	{
		fprintf(stderr, "ERROR:  louis_translate_forward FAIL:  length\n");
		return 1;
	}
	for(i = 0; i < uchars_len; i++)
	if(trans[i] != uchars[i])
	{
		fprintf(stderr, "ERROR:  louis_translate_forward FAIL:  trans\n");
		return 1;
	}


	printf("louis_translate_backward");
	fflush(stdout);
	uchars_len = louis_translate_backward(uchars, 0x100, u"⠕⠪ ⠕⠪⠕⠪ ⠕⠕⠪⠪ ⠕⠪⠕⠪ ⠕⠪", 20, "link.rst", NULL, NULL, NULL, NULL);
	if(uchars_len < 1)
	{
		fprintf(stderr, "\nERROR:  louis_translate_backward\n");
		return 1;
	}
	utf16le_convert_to_utf8(cchars, 0x100, uchars, uchars_len);
	printf("  = %s\n", cchars);

	if(uchars_len != 13)
	{
		fprintf(stderr, "ERROR:  louis_translate_backward FAIL\n");
		return 1;
	}
	for(i = 0; i < uchars_len; i++)
	if(snart[i] != (char)uchars[i])
	{
		fprintf(stderr, "ERROR:  louis_translate_backward FAIL\n");
		return 1;
	}


	printf("louis_convert_to");
	fflush(stdout);
	utf16_copy(uchars, trans, 21);
	if(!louis_convert_to(uchars, 20, "link.cvt"))
	{
		fprintf(stderr, "\nERROR:  louis_convert_to\n");
		return 1;
	}
	utf16le_convert_to_utf8(cchars, 0x100, uchars, 20);
	printf("          = %s\n", cchars);

	for(i = 0; i < 20; i++)
	if(convert[i] != uchars[i])
	{
		fprintf(stderr, "ERROR:  louis_convert_to FAIL conversion\n");
		return 1;
	}


	printf("louis_convert_from");
	fflush(stdout);
	utf16_copy(uchars, trevnoc, 21);
	if(!louis_convert_from(uchars, 20, "link.cvt"))
	{
		fprintf(stderr, "\nERROR:  louis_convert_from\n");
		return 1;
	}
	utf16le_convert_to_utf8(cchars, 0x100, uchars, 20);
	printf("        = %s\n", cchars);

	for(i = 0; i < 20; i++)
	if(trans[i] != uchars[i])
	{
		fprintf(stderr, "ERROR:  louis_convert_from FAIL conversion\n");
		return 1;
	}

	return 0;
}
