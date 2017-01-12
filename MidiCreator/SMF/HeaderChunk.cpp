#include "HeaderChunk.h"

using namespace SMF;

HeaderChunk::HeaderChunk(FileFormat ff, short numOfTracks, short division) :
	_fileFormat(ff),
	_numberOfTracks(numOfTracks),
	_division(division)
{

}

std::vector<uint8_t> HeaderChunk::toByteVector() const
{
	std::vector<uint8_t> ret(14, 0x00);

	for (size_t i = 0; i < this->_chunkType.size(); i++)
	{
		ret[i] = this->_chunkType[i];
	}

	ret[7] = this->_headerLength;
	ret[9] = static_cast<uint8_t>(this->_fileFormat);

	//To get bits in range x -> y we need to
	//Shift right bits that we want to the lowest position
	//Mask the bits that we want

	ret[10] = (this->_numberOfTracks >> 8) & 0xFF;
	ret[11] = this->_numberOfTracks & 0xFF;

	ret[12] = (this->_division >> 8) & 0xFF;
	ret[13] = this->_division & 0xFF;

	return ret;
}