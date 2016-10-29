#include "TrackChunk.h"

#include "Exceptions\IllegalChannelException.h"
#include "Exceptions\TrackClosedException.h"
#include "Exceptions\TrackNotClosedException.h"

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
	if (this->closed)
	{
		throw new TrackClosedException;
	}

	trackEvents.push_back(event);
	return event;
}

TrackEvent* TrackChunk::addTrackEvent(EventType eventType)
{
	if (this->closed)
	{
		throw new TrackClosedException;
	}

	auto event = new TrackEvent(eventType);
	trackEvents.push_back(event);
	return event;
}

TrackChunk* TrackChunk::setCurrentChannel(short channel)
{
	if (this->closed)
	{
		throw new TrackClosedException;
	}

	if (channel < 1 || channel > 16)
	{
		throw new IllegalChannelException;
	}

	this->currentChannel = channel;
	return this;
}

void TrackChunk::closeTrack()
{
	if (this->closed)
	{
		throw new TrackClosedException;
	}

	#ifdef DEBUG
		printf("TrackChunk::closedTrack()\n");
	#endif // DEBUG

	auto innerEvent = this->addTrackEvent(EventType::META_EVENT)
		->setDeltaTime(0)
		->getInnerEvent<MetaEvent>()
		->setEventType(MetaEventType::END_OF_TRACK)
		->setLength(0);

	this->closed = true;
}

void TrackChunk::reopenTrack()
{
	if (!this->closed)
	{
		throw new TrackNotClosedException;
	}

	this->trackEvents.pop_back();
	this->closed = false;
}

void TrackChunk::calculateTracksLength()
{
	#ifdef DEBUG
		printf("TrackChunk::calculateTracksLength()\n");
	#endif // DEBUG

	for (auto &te : this->trackEvents)
	{
		//TODO: OPTIMIZE THAT.
		this->tracksLength += te->toByteVector().size();
	}
}

//IConvertibleToByteCollection
std::vector<uint8_t> TrackChunk::toByteVector()
{
	#ifdef DEBUG
		printf("TrackChunk::toByteVector()\n");
	#endif // DEBUG

	if (!this->closed)
	{
		this->closeTrack();
	}

	std::vector<uint8_t> ret;

	//chunkType
	for (auto &c : this->chunkType)
		ret.push_back(c);

	this->calculateTracksLength();

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

