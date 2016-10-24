#include "HeaderChunk.h"

using namespace SMF;

HeaderChunk::HeaderChunk(FileFormat ff)
{
	this->fileFormat = ff;
}

byte* HeaderChunk::toByteArray()
{
	byte* ret = new byte[14] { 0x00 };

	for (size_t i = 0; i < 4; i++)
		ret[i] = this->chunkType[i];

	ret[7] = 0x06;

	ret[9] = this->fileFormat;

	//To get bits in range x -> y we need to
	//Shift right bits that we want to the lowest position
	//Mask the bits that we want
	//e. g.

	ret[10] = (this->numberOfTracks >> 8) & 0xFF;
	ret[11] = this->numberOfTracks & 0xFF;

	ret[12] = (this->division >> 8) & 0xFF;
	ret[13] = this->division & 0xFF;

	return ret;
}


HeaderChunk::~HeaderChunk()
{
}


