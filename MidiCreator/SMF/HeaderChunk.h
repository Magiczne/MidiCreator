#pragma once

#include "../stdafx.h"
#include "../Abstract/IConvertibleToByteCollection.h"
#include "Enums/FileFormat.h"

namespace SMF
{
	class HeaderChunk : 
		public IConvertibleToByteCollection
	{
	private:
		const std::array<char, 4> chunkType = { 'M', 'T', 'h', 'd' };
		const uint8_t headerLength = 6;
		FileFormat fileFormat;
		short numberOfTracks = 0;

		//Unit of time for delta timing. If the value is positive, then it represents the units per beat. 
		//For example, +96 would mean 96 ticks per beat. If the value is negative, delta times are in SMPTE compatible units.
		short division = 0;

	public:
		HeaderChunk(FileFormat);
		~HeaderChunk();

		//Getters
		inline const short& getNumberOfTracks() const { return this->numberOfTracks; }
		inline const FileFormat& getFileFormat() const { return this->fileFormat; }
		inline const short& getDivision() const { return this->division; }

		inline void addTrack() { this->numberOfTracks++; }
		inline void setDivision(short val) { this->division = val; }

		//IConvertibleToByteCollection
		virtual std::vector<uint8_t> toByteVector();
	};
}

