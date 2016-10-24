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
	private:
		const char chunkType[4] = { 'M', 'T', 'h', 'd' };
		const short headerLength = 6;
		FileFormat fileFormat;
		short numberOfTracks = 0;
		short division = 0;

	public:
		HeaderChunk(FileFormat);
		~HeaderChunk();

		//Getters
		inline const short& getNumberOfTracks() const { return this->numberOfTracks; }
		inline const FileFormat& getFileFormat() const { return this->fileFormat; }
		
		inline void addTrack() { this->numberOfTracks++; }

		//IConvertibleToByteArray
		virtual byte* toByteArray();
	};
}

