#pragma once

#include "../stdafx.h"
#include "../Interfaces/IConvertibleToByteArray.h"

namespace SMF
{
	enum FileFormat
	{
		SINGLE_TRACK	= 0x00,
		MULTIPLE_TRACK	= 0x01,
		MULTIPLE_SONG	= 0x02
	};

	class HeaderChunk :
		IConvertibleToByteArray
	{
	public:
		const char chunkType[4] = { 'M', 'T', 'h', 'd' };
		const short headerLength = 6;
		FileFormat fileFormat;
		short numberOfTracks;
		short division;

		HeaderChunk();
		~HeaderChunk();
	};
}

