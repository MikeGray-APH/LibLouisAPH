/*

LibLouisAPH Braille Translation and Back-Translation Library

Copyright (C) 2017 Mike Gray, American Printing House for the Blind, Inc.

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

#include <stdlib.h>

#include "type.h"
#include "utf.h"
#include "log.h"

/******************************************************************************/

int utf16le_convert_to_int(Unicode *uchars, const int uchars_len)
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

int utf16le_convert_escapes(Unicode *uchars, const int uchars_len)
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

int utf8_convert_to_utf16le(Unicode *uchars, const int uchars_max, const char *cchars, const int cchars_len)
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
	static const Unicode offsets[6] = { 0x0000, 0x3080, 0x2080, 0x2080, 0x2080, 0x2080, };
	Unicode uchar;
	int cnt, crs, i;

	crs = 0;
	for(i = 0; i < cchars_len; i++)
	{
		if(cchars[i] == 0)
			break;
		cnt = byte_count[(unsigned char)cchars[i]];
		if(i + cnt >= cchars_len)
			break;

		uchar = 0;
		switch(cnt)
		{
		case 5:  //uchar += (unsigned char)cchars[i++];  uchar <<= 6;
		case 4:  //uchar += (unsigned char)cchars[i++];  uchar <<= 6;
		case 3:  //uchar += (unsigned char)cchars[i++];  uchar <<= 6;

			log_message(LOG_ERROR, "invalid UTF8 character\n");
			return -1;

		case 2:  uchar += (unsigned char)cchars[i++];  uchar <<= 6;
		case 1:  uchar += (unsigned char)cchars[i++];  uchar <<= 6;
		case 0:  uchar += (unsigned char)cchars[i];
		}
		uchar -= offsets[cnt];
		uchars[crs++] = uchar;

		/*   ensure there is enough space   */
		if(crs >= uchars_max)
		{
			crs--;
			break;
		}
	}

	ASSERT(crs < uchars_max)
	uchars[crs] = 0;
	return crs;
}

int utf16le_convert_to_utf8(char *cchars, const int cchars_max, const Unicode *uchars, const int uchars_len)
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

	ASSERT(crs < cchars_max)
	cchars[crs] = 0;
	return crs;
}

/******************************************************************************/
