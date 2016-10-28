#include "TrackChunk.h"

#include "Exceptions\IllegalChannelException.h"

using namespace SMF;

TrackChunk::TrackChunk()
{
}

TrackChunk::~TrackChunk()
{
	for (auto &te : this->trackEvents)
		delete te;
}

TrackEvent* TrackChunk::addTrackEvent(TrackEvent* event)
{
	trackEvents.push_back(event);
	return event;
}

TrackEvent* TrackChunk::addTrackEvent(EventType eventType)
{
	auto event = new TrackEvent(eventType);
	trackEvents.push_back(event);
	return event;
}

TrackChunk* TrackChunk::setCurrentChannel(short channel)
{
	if (channel < 1 || channel > 16)
	{
		throw new IllegalChannelException;
	}

	this->currentChannel = channel;
	return this;
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

