#include "TrackChunk.h"

#include "Events/MidiEvent.h"
#include "Events/MetaEvent.h"
#include "Enums/MetaEventType.h"
#include "Enums/MidiEventType.h"
#include "Events/TrackEvent.h"
#include "Util/SMF_Note.h"

#include "Exceptions/TrackClosedException.h"
#include "Exceptions/TrackNotClosedException.h"

using namespace SMF;
using namespace SMF::Exceptions;

TrackChunk::~TrackChunk()
{
	for (auto &te : this->trackEvents)
		delete te;
}

void TrackChunk::calculateTracksLength()
{
	#ifdef METHOD_DEBUG
		printf("TrackChunk::calculateTracksLength()\n");
	#endif // METHOD_DEBUG

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
		throw TrackClosedException();
	}

	trackEvents.push_back(event);
	return event;
}

TrackEvent* TrackChunk::addTrackEvent(EventType eventType)
{
	if (this->closed)
	{
		throw TrackClosedException();
	}

	auto event = new TrackEvent(eventType);
	trackEvents.push_back(event);
	return event;
}

TrackChunk* TrackChunk::setCurrentChannel(MIDIChannel channel)
{
	if (this->closed)
	{
		throw TrackClosedException();
	}

	this->currentChannel = channel;
	return this;
}

TrackChunk* TrackChunk::setVoiceProgram(GMPatch patch)
{
	#ifdef METHOD_DEBUG
		printf("TrackChunk::setVoiceProgram()\n");
	#endif // METHOD_DEBUG

	if (this->closed)
	{
		throw TrackClosedException();
	}

	this->addTrackEvent(EventType::MIDI_EVENT)
		->setDeltaTime(0)
		->getInnerEvent<MidiEvent>()
		->setEventType(MidiEventType::PROGRAM_CHANGE)
		->setChannel(this->currentChannel)
		->addParam(static_cast<uint8_t>(patch) - 1);

	return this;
}

TrackChunk* TrackChunk::addNote(Note* note)
{
	#ifdef METHOD_DEBUG
		printf("TrackChunk::addNote()\n");
	#endif // METHOD_DEBUG

	if (this->closed)
	{
		throw TrackClosedException();
	}

	//Note on
	this->addTrackEvent(EventType::MIDI_EVENT)
		->setDeltaTime(0)	//TODO: Delta sums, or something, duration etc.
		->getInnerEvent<MidiEvent>()
		->setEventType(MidiEventType::NOTE_ON)
		->setChannel(this->currentChannel)
		->addParam(static_cast<uint8_t>(note->pitch()))
		->addParam(note->volume());

	//Note off
	this->addTrackEvent(EventType::MIDI_EVENT)
		->setDeltaTime(note->duration()) //TODO: Delta sums, or something, duration etc.	
		->getInnerEvent<MidiEvent>()
		->setEventType(MidiEventType::NOTE_OFF)
		->setChannel(this->currentChannel)
		->addParam(static_cast<uint8_t>(note->pitch()))
		->addParam(0);	//TODO: change that to 0?

	return this;
}

//Currently supports multiple notes starting at the same time
//But ending differently
//DOES NOT support notes starting differently
TrackChunk* TrackChunk::addNotes(std::vector<Note*> notes)
{
	#ifdef METHOD_DEBUG
		printf("TrackChunk::addNotes()\n");
	#endif // METHOD_DEBUG

	if (this->closed)
	{
		throw TrackClosedException();
	}

	std::sort(notes.begin(), notes.end(), [](Note* a, Note*b) {
		return *a < *b;
	});

	for (const auto& note : notes)
	{
		std::cout << note->duration() << std::endl;
	}

	for (const auto& note : notes)
	{
		this->addTrackEvent(EventType::MIDI_EVENT)
			->setDeltaTime(0)
			->getInnerEvent<MidiEvent>()
			->setEventType(MidiEventType::NOTE_ON)
			->setChannel(this->currentChannel)
			->addParam(static_cast<uint8_t>(note->pitch()))
			->addParam(note->volume());
	}

	int previousDuration = 0;
	for (const auto& note : notes)
	{
		this->addTrackEvent(EventType::MIDI_EVENT)
			->setDeltaTime(note->duration() - previousDuration)
			->getInnerEvent<MidiEvent>()
			->setEventType(MidiEventType::NOTE_OFF)
			->setChannel(this->currentChannel)
			->addParam(static_cast<uint8_t>(note->pitch()))
			->addParam(note->volume());

		previousDuration = note->duration();
	}

	return this;
}

void TrackChunk::closeTrack()
{
	if (this->closed)
	{
		throw TrackClosedException();
	}

	#ifdef METHOD_DEBUG
		printf("TrackChunk::closedTrack()\n");
	#endif // METHOD_DEBUG

	this->addTrackEvent(EventType::META_EVENT)
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
		throw TrackNotClosedException();
	}

	this->trackEvents.pop_back();
	this->closed = false;
}

//IConvertibleToByteCollection
std::vector<uint8_t> TrackChunk::toByteVector()
{
	#ifdef METHOD_DEBUG
		printf("TrackChunk::toByteVector()\n");
	#endif // METHOD_DEBUG

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