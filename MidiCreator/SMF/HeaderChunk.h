#pragma once

#include "../stdafx.h"
#include "Abstract/IConvertibleToByteCollection.h"
#include "Enums/FileFormat.h"

namespace SMF
{
	class HeaderChunk : public IConvertibleToByteCollection
	{
	private:
		const std::array<char, 4> _chunkType = { 'M', 'T', 'h', 'd' };
		const uint8_t _headerLength = 6;
		FileFormat _fileFormat;
		short _numberOfTracks;

		//Unit of time for delta timing. If the value is positive, then it represents the units per beat. 
		//For example, +96 would mean 96 ticks per beat(quarter-note). 
		//If the value is negative, delta times are in SMPTE compatible units.
		//(Subdivisions of a second)
		short _division;

	public:
		explicit HeaderChunk(FileFormat ff, short numOfTracks = 0, short division = 0);

		void addTrack() { this->_numberOfTracks++; }

		//IConvertibleToByteCollection
		std::vector<uint8_t> toByteVector() const override;

		//Getters/setters
		short numberOfTracks() const { return this->_numberOfTracks; }

		void fileFormat(const FileFormat ff) { this->_fileFormat = ff; }
		FileFormat fileFormat() const { return this->_fileFormat; }

		void division(const short val) { this->_division = val; }
		short division() const { return this->_division; }
	};
}