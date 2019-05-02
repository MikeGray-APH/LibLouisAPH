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
#include <stdint.h>

#include "type.h"
#include "utf.h"
#include "log.h"

/******************************************************************************/

int utf16_convert_to_int(unichar *uchars, const int uchars_len)
{
	char cchars[0x100];
	int len, i;

	len = uchars_len;
	if(uchars_len >= 0xff)
		len = 0xff;

	/*   simple conversion   */
	for(i = 0; i < len; i++)
		cchars[i] = (char)uchars[i];
	cchars[i] = 0;

	return strtol(cchars, NULL, 0);
}

int utf16_convert_escapes(unichar *uchars, const int uchars_len)
{
	int crs, off, hex, i;

	if(uchars_len < 2)
		return uchars_len;

	crs =
	off = 0;
	while(off < uchars_len)
	{
		if(!uchars[off])
			break;
		else if(uchars[off] == u'\\')
		{
			off++;
			if(!uchars[off])
				return 0;
			else if(off >= uchars_len)
				return 0;
			switch(uchars[off])
			{
			default:    uchars[crs++] = uchars[off++];  break;
			case u'n':  uchars[crs++] = u'\n';  off++;  break;
			case u'r':  uchars[crs++] = u'\r';  off++;  break;
			case u't':  uchars[crs++] = u'\t';  off++;  break;
			case u's':  uchars[crs++] = u' ';   off++;  break;

			case u'x':  case u'X':  case u'u':  case u'U':

				if(off + 5 > uchars_len)
					return 0;
				hex = 0;
				off++;
				for(i = 0; i < 4; i++)
				{
					if(!uchars[off])
						return 0;
					else if(uchars[off] >= u'0' && uchars[off] <= u'9')
						hex += ((uchars[off++] - u'0')) << ((3 - i) * 4);
					else if(uchars[off] >= u'A' && uchars[off] <= u'F')
						hex += ((uchars[off++] - u'A') + 10) << ((3 - i) * 4);
					else if(uchars[off] >= u'a' && uchars[off] <= u'f')
						hex += ((uchars[off++] - u'a') + 10) << ((3 - i) * 4);
				}
				uchars[crs++] = hex;
				break;
			}
		}
		else
			uchars[crs++] = uchars[off++];
	}

	if(crs <= uchars_len)
		uchars[crs] = 0;
#ifdef DEBUG
	else
		ASSERT(0)
#endif
	return crs;
}

/******************************************************************************/

int utf8_convert_to_utf16(unichar *uchars, const int uchars_max, const char *cchars, const int cchars_len, int *cchars_crs)
{
	static const char byte_count[256] =
	{
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2, 3,3,3,3,3,3,3,3,4,4,4,4,5,5,5,5,
	};
	static const uint32_t offsets[6] = { 0x00000000, 0x00003080, 0x000e2080, 0x03c82080, 0xfa082080, 0x82082080, };
	uint32_t uchar32;
	int cnt, crs, i;

	crs = 0;
	for(i = 0; i < cchars_len; i++)
	{
		if(cchars[i] == 0)
			break;

		cnt = byte_count[(unsigned char)cchars[i]];
		if(i + cnt >= cchars_len)
			break;
		uchar32 = 0;
		switch(cnt)
		{
		case 5:  uchar32 += (unsigned char)cchars[i++];  uchar32 <<= 6;
		case 4:  uchar32 += (unsigned char)cchars[i++];  uchar32 <<= 6;
		case 3:  uchar32 += (unsigned char)cchars[i++];  uchar32 <<= 6;
		case 2:  uchar32 += (unsigned char)cchars[i++];  uchar32 <<= 6;
		case 1:  uchar32 += (unsigned char)cchars[i++];  uchar32 <<= 6;
		case 0:  uchar32 += (unsigned char)cchars[i];
		}
		uchar32 -= offsets[cnt];

		if(uchar32 < 0xffff)
		{
			if(crs + 1 >= uchars_max)
				break;
			uchars[crs++] = uchar32;
		}
		else
		{
			if(crs + 2 >= uchars_max)
				break;
			uchar32 -= 0x10000;
			uchars[crs++] = (unichar)((uchar32 >> 10)    + 0xd800);
			uchars[crs++] = (unichar)((uchar32 & 0x03ff) + 0xdc00);
		}
	}

	ASSERT(crs < uchars_max)
	uchars[crs] = 0;

	if(cchars_crs)
	{
		*cchars_crs = i;

		for( ; i < cchars_len; i++)
		{
			if(cchars[i] == 0)
				break;

			cnt = byte_count[(unsigned char)cchars[i]];
			if(i + cnt >= cchars_len)
				break;
			uchar32 = 0;
			switch(cnt)
			{
			case 5:  uchar32 += (unsigned char)cchars[i++];  uchar32 <<= 6;
			case 4:  uchar32 += (unsigned char)cchars[i++];  uchar32 <<= 6;
			case 3:  uchar32 += (unsigned char)cchars[i++];  uchar32 <<= 6;
			case 2:  uchar32 += (unsigned char)cchars[i++];  uchar32 <<= 6;
			case 1:  uchar32 += (unsigned char)cchars[i++];  uchar32 <<= 6;
			case 0:  uchar32 += (unsigned char)cchars[i];
			}
			uchar32 -= offsets[cnt];

			if(uchar32 > 0xffff)
				crs++;
			crs++;
		}
	}

	return crs;
}

int utf16_convert_to_utf8(char *cchars, const int cchars_max, const unichar *uchars, const int uchars_len, int *uchars_crs)
{
	uint32_t uchar32;
	int crs, i;

	crs = 0;
	for(i = 0; i < uchars_len; i++)
	{
		if(uchars[i] == 0)
			break;

		uchar32 = uchars[i];
		if(uchar32 >= 0xd800 && uchar32 <= 0xdbff)
		{
			if(i + 1 >= uchars_len)
				break;
			i++;
			if(uchars[i] >= 0xdc00 && uchars[i] <= 0xdfff)
				uchar32  = ((uchar32 - 0xd800) << 10) + (uchars[i] - 0xdc00) + 0x10000;
			else
			{
				i--;
				break;
			}
		}

		if(uchar32 < 0x80)
		{
			if(crs > cchars_max - 2)
				break;
			cchars[crs++] = (char)uchar32 & 0x7f;
		}
		else if(uchar32 < 0x800)
		{
			if(crs > cchars_max - 3)
				break;
			cchars[crs++] = ((uchar32 >> 6) & 0x1f) | 0xc0;
			cchars[crs++] = ((uchar32 >> 0) & 0x3f) | 0x80;
		}
		else if(uchar32 < 0x10000)
		{
			if(crs > cchars_max - 4)
				break;
			cchars[crs++] = ((uchar32 >> 12) & 0x0f) | 0xe0;
			cchars[crs++] = ((uchar32 >>  6) & 0x3f) | 0x80;
			cchars[crs++] = ((uchar32 >>  0) & 0x3f) | 0x80;
		}
		else if(uchar32 < 0x110000)
		{
			if(crs > cchars_max - 5)
				break;
			cchars[crs++] = ((uchar32 >> 18) & 0x07) | 0xf0;
			cchars[crs++] = ((uchar32 >> 12) & 0x3f) | 0x80;
			cchars[crs++] = ((uchar32 >>  6) & 0x3f) | 0x80;
			cchars[crs++] = ((uchar32 >>  0) & 0x3f) | 0x80;
		}
		else
			break;
	}

	ASSERT(crs < cchars_max)
	cchars[crs] = 0;

	if(uchars_crs)
	{
		*uchars_crs = i;

		for( ; i < uchars_len; i++)
		{
			if(uchars[i] == 0)
				break;

			uchar32 = uchars[i];
			if(uchar32 >= 0xd800 && uchar32 <= 0xdbff)
			{
				if(i + 1 >= uchars_len)
					break;
				i++;
				if(uchars[i] >= 0xdc00 && uchars[i] <= 0xdfff)
					uchar32  = ((uchar32 - 0xd800) * 0x400) + (uchars[i] - 0xdc00) + 0x10000;
				else
					break;
			}
			     if(uchar32 < 0x80)
				crs += 1;
			else if(uchar32 < 0x800)
				crs += 2;
			else if(uchar32 < 0x10000)
				crs += 3;
			else if(uchar32 < 0x110000)
				crs += 4;
			else
				break;
		}
	}

	return crs;
}

/******************************************************************************/
