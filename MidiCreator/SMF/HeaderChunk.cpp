#include "HeaderChunk.h"

using namespace SMF;

HeaderChunk::HeaderChunk(FileFormat ff, short numOfTracks = 0, short division = 0) :
	fileFormat(ff),
	numberOfTracks(numOfTracks),
	division(division)
{

}

std::vector<uint8_t> HeaderChunk::toByteVector()
{
	std::vector<uint8_t> ret(14, 0x00);

	for (size_t i = 0; i < this->chunkType.size(); i++)
		ret[i] = this->chunkType[i];

	ret[7] = this->headerLength;
	ret[9] = this->fileFormat;

	//To get bits in range x -> y we need to
	//Shift right bits that we want to the lowest position
	//Mask the bits that we want

	ret[10] = (this->numberOfTracks >> 8) & 0xFF;
	ret[11] = this->numberOfTracks & 0xFF;

	ret[12] = (this->division >> 8) & 0xFF;
	ret[13] = this->division & 0xFF;

	return ret;
}

HeaderChunk::~HeaderChunk()
{
}


