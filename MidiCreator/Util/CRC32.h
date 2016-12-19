#pragma once
//
// crc.h is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// any later version.
//
// crc.h is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//


typedef unsigned int   UInt32;
typedef unsigned short UInt16;
typedef unsigned char  UInt8;

/**
* htonl()
*/
#ifndef HTONL

// use <arpa/inet.h>
// #define HTONL(v)  htonl(v)

// use ANSI C bit operators
#if defined(LITTLE_ENDIAN)
#define HTONL(v)    ( ((v&0xff000000)>>24) | ((v&0xff0000)>>8) | ((v&0xff00)<<8) | ((v&0xff)<<24) )
#else
#define HTONL(v)        (v)
#endif

// use x86 assembler
// #define HTONL _asm_htonl
// inline unsigned int _asm_htonl( unsigned int v ) {
//	 __asm {
//		MOV     eax, v
//		BSWAP   eax
//	 }
// }

#endif


/**
* CRC32
*/
template <class DT = UInt32, DT QUOTIENT = 0x04c11db7>
class CRC32
{
public:
	CRC32() { Reset(); }
	void Reset() { crc = 0; }
	explicit operator DT () { return crc; }

	// update
	DT update(UInt8 *data, unsigned len);

	//Magiczne 2016
	DT update(const std::vector<uint8_t>& data);

private:
	// CRC value
	DT crc;

	// help function
	static DT crc32B(UInt8 *data, unsigned len, UInt32 result = 0);
	static DT crc32DW(UInt8 *data, unsigned len, UInt32 result = 0);
};


// CRC-32-IEEE 802.3  (V.42, MPEG-2, PNG [15], POSIX cksum)
typedef CRC32<UInt32, 0x04c11db7> CRC32_IEEE802;

// CRC-32C (Castagnoli)
typedef CRC32<UInt32, 0x1EDC6F41> CRC32_C;

// CRC-32K (Koopman)
typedef CRC32<UInt32, 0x741B8CD7> CRC32_K;

// CRC-32Q (aviation; AIXM [16])
typedef CRC32<UInt32, 0x814141AB> CRC32_A;


/**
*
* basic algorithm
*
*/
template <class DT, DT QUOTIENT>
DT CRC32<DT, QUOTIENT>::crc32B(UInt8 *data, unsigned len, UInt32 result)
{
	unsigned                 i, j;
	UInt8       octet;

	result = ~result;

	for (i = 0; i<len; i++)
	{
		octet = *(data++);
		for (j = 0; j<8; j++)
		{
			if ((octet >> 7) ^ (result >> 31))
			{
				result = (result << 1) ^ QUOTIENT;
			}
			else
			{
				result = (result << 1);
			}
			octet <<= 1;
		}
	}

	return ~result;             /* The complement of the remainder */
}


/**
*
* This code is copyright � 1993 Richard Black. All rights are reserved.
* You may use this code only if it includes a statement to that effect.
*
*/

template <UInt32 QUOTIENT>
struct crc32_table_t {

	UInt32 crctab[256];

	crc32_table_t() {

		unsigned i, j;

		UInt32 crc;

		for (i = 0; i < 256; i++)
		{
			crc = i << 24;
			for (j = 0; j < 8; j++)
			{
				if (crc & 0x80000000)
					crc = (crc << 1) ^ QUOTIENT;
				else
					crc = crc << 1;
			}

			crctab[i] = HTONL(crc);
		}
	}
};


template <class DT, DT QUOTIENT>
DT CRC32<DT, QUOTIENT>::crc32DW(UInt8 *data, unsigned len, UInt32 result)
{
	static crc32_table_t<QUOTIENT> table;
	// ReSharper disable CppEntityNeverUsed
	UInt32 *crctab = table.crctab;
	// ReSharper restore CppEntityNeverUsed

	UInt32 *p = reinterpret_cast<UInt32 *>(data);
	UInt32 *e = reinterpret_cast<UInt32 *>(data + len);

	// assert( (len&0x03) == 0 );

	result = HTONL(~result);

	while (p<e)
	{

		result ^= *p++;

#if defined(LITTLE_ENDIAN)
		result = crctab[result & 0xff] ^ result >> 8;
		result = crctab[result & 0xff] ^ result >> 8;
		result = crctab[result & 0xff] ^ result >> 8;
		result = crctab[result & 0xff] ^ result >> 8;
#elif defined(BIG_ENDIAN)
		result = crctab[result >> 24] ^ result << 8;
		result = crctab[result >> 24] ^ result << 8;
		result = crctab[result >> 24] ^ result << 8;
		result = crctab[result >> 24] ^ result << 8;
#else
#error need to define LITTLE_ENDIAN or BIG_ENDIAN
#endif

	}

	return HTONL(~result);
}


/**
*
*  calculate CRC32
*
*/
template <class DT, DT QUOTIENT>
DT CRC32<DT, QUOTIENT>::update(UInt8 *data, unsigned len)
{
	unsigned len1 = len & 0x03;
	unsigned len2 = len - len1;

	if (len2>0) {
		crc = crc32DW(data, len2, crc);
	}

	if (len1>0) {
		crc = crc32B(data + len2, len1, crc);
	}


	return crc;
}

//Magiczne 2016
template <class DT, DT QUOTIENT>
DT CRC32<DT, QUOTIENT>::update(const std::vector<uint8_t>& data)
{
	unsigned len1 = data.size() & 0x03;
	unsigned len2 = data.size() - len1;

	if (len2>0) {
		crc = crc32DW(&data[0], len2, crc);
	}

	if (len1>0) {
		crc = crc32B(&data[0] + len2, len1, crc);
	}

	return crc;
}