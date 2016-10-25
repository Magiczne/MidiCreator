#include "StandardMIDIFile.h"

using namespace SMF;

StandardMIDIFile::StandardMIDIFile()
{
}

std::vector<uint8_t> StandardMIDIFile::toByteVector()
{
	std::vector<uint8_t> ret = this->headerChunk->toByteVector();

	std::vector<uint8_t> trackBytes;

	std::vector<uint8_t> tmpVector;
	for (auto &a : this->trackChunks)
	{
		tmpVector = a.toByteVector();
		trackBytes.insert(trackBytes.end(), tmpVector.begin(), tmpVector.end());
	}

	ret.insert(ret.end(), trackBytes.begin(), trackBytes.end());

	return ret;
}


StandardMIDIFile::~StandardMIDIFile()
{
}
