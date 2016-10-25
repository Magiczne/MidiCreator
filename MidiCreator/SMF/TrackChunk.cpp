#include "TrackChunk.h"

using namespace SMF;

TrackChunk::TrackChunk()
{
}

std::vector<uint8_t> TrackChunk::toByteVector()
{
	std::vector<uint8_t> ret;

	//chunkType
	for (auto &c : this->chunkType)
		ret.push_back(c);

	//tracksLength
	ret.push_back((this->tracksLength >> 24) & 0xFF);
	ret.push_back((this->tracksLength >> 16) & 0xFF);
	ret.push_back((this->tracksLength >> 8) & 0xFF);
	ret.push_back(this->tracksLength & 0xFF);

	//trackEvents
	std::vector<uint8_t> tmp;
	for (auto &te : this->trackEvents)
	{
		tmp = te->toByteVector();
		ret.insert(ret.end(), tmp.begin(), tmp.end());
	}

	return ret;
}

void TrackChunk::addEvent(TrackEvent* event)
{
	trackEvents.push_back(event);
}

TrackChunk::~TrackChunk()
{
	for (auto &te : this->trackEvents)
		delete te;
}
