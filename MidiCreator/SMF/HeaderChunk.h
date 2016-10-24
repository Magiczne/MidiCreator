#pragma once

#include "../stdafx.h"
#include "../Abstract/IConvertibleToByteArray.h"
#include "Enums/FileFormat.h"

namespace SMF
{
	class HeaderChunk :
		public IConvertibleToByteArray
	{
	private:
		const std::array<char, 4> chunkType = { 'M', 'T', 'h', 'd' };
		const short headerLength = 6;
		FileFormat fileFormat;
		short numberOfTracks = 0;
		short division = 0;

	protected:
		//IConvertibleToByteArray
		virtual std::vector<byte> toByteVector();

	public:
		HeaderChunk(FileFormat);
		~HeaderChunk();

		//Getters
		inline const short& getNumberOfTracks() const { return this->numberOfTracks; }
		inline const FileFormat& getFileFormat() const { return this->fileFormat; }
		
		inline void addTrack() { this->numberOfTracks++; }
	};
}

