#include "HeaderChunk.h"

using namespace SMF;

HeaderChunk::HeaderChunk(FileFormat ff)
{
	this->fileFormat = ff;
}

std::vector<byte> HeaderChunk::toByteVector()
{
	std::vector<byte> ret(14);

	for (size_t i = 0; i < 4; i++)
		ret[i] = this->chunkType[i];

	ret[5] = ret[6] = ret[8] = 0x00;

	ret[7] = this->headerLength;
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


