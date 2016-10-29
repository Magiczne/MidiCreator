#include "TrackChunk.h"

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

TrackChunk* TrackChunk::setCurrentChannel(MIDIChannel channel)
{
	if (this->closed)
	{
		throw new TrackClosedException;
	}

	this->currentChannel = channel;
	return this;
}

TrackChunk* TrackChunk::setVoiceProgram(GMPatch patch)
{
	#ifdef DEBUG
		printf("TrackChunk::setVoiceProgram()\n");
	#endif // DEBUG

	if (this->closed)
	{
		throw new TrackClosedException;
	}

	this->addTrackEvent(EventType::MIDI_EVENT)
		->setDeltaTime(0)
		->getInnerEvent<MidiEvent>()
		->setEventType(MidiEventType::PROGRAM_CHANGE)
		->setChannel(this->currentChannel)
		->addParam((uint8_t)patch - 1);

	return this;
}

TrackChunk* TrackChunk::addNote(Note* note)
{
	#ifdef DEBUG
		printf("TrackChunk::addNote()\n");
	#endif // DEBUG

	if (this->closed)
	{
		throw new TrackClosedException;
	}

	//Note on
	this->addTrackEvent(EventType::MIDI_EVENT)
		->setDeltaTime(0)	//TODO: Delta sums, or something, duration etc.
		->getInnerEvent<MidiEvent>()
		->setEventType(MidiEventType::NOTE_ON)
		->setChannel(this->currentChannel)
		->addParam((uint8_t)note->getPitch())
		->addParam(note->getVolume());

	//Note off
	this->addTrackEvent(EventType::MIDI_EVENT)
		->setDeltaTime(0) //TODO: Delta sums, or something, duration etc.	
		->getInnerEvent<MidiEvent>()
		->setEventType(MidiEventType::NOTE_OFF)
		->setChannel(this->currentChannel)
		->addParam((uint8_t)note->getPitch())
		->addParam(note->getVolume());	//TODO: change that to 0?

	return this;
}

TrackChunk* TrackChunk::addNotes(std::vector<Note*> notes)
{
	#ifdef DEBUG
		printf("TrackChunk::addNotes()\n");
	#endif // DEBUG

	if (this->closed)
	{
		throw new TrackClosedException;
	}

	for (auto& note : notes)
	{
		//TODO
	}
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

