#include "TrackChunk.h"

#include "Events/MidiEvent.h"
#include "Events/MetaEvent.h"
#include "Enums/MetaEventType.h"
#include "Enums/MidiEventType.h"
#include "Events/TrackEvent.h"
#include "Util/SMF_Note.h"

#include "Exceptions/TrackClosedException.h"
#include "Exceptions/TrackNotClosedException.h"
#include "Exceptions/TracksNotCalculatedException.h"

using namespace SMF;
using namespace SMF::Exceptions;

TrackChunk::~TrackChunk()
{
	for (auto &te : this->_trackEvents)
		delete te;
}

void TrackChunk::calculateTracksLength()
{
	#ifdef METHOD_DEBUG
		printf("TrackChunk::calculateTracksLength()\n");
	#endif // METHOD_DEBUG

	for (auto &te : this->_trackEvents)
	{
		//TODO: OPTIMIZE THAT.
		this->_tracksLength += te->toByteVector().size();
	}

	_tracksCalculated = true;
}

TrackEvent* TrackChunk::addTrackEvent(TrackEvent* event)
{
	if (this->_closed)
	{
		throw TrackClosedException();
	}

	_trackEvents.push_back(event);
	return event;
}

TrackEvent* TrackChunk::addTrackEvent(EventType eventType)
{
	if (this->_closed)
	{
		throw TrackClosedException();
	}

	auto event = new TrackEvent(eventType);
	_trackEvents.push_back(event);
	return event;
}

TrackChunk* TrackChunk::setCurrentChannel(MIDIChannel channel)
{
	if (this->_closed)
	{
		throw TrackClosedException();
	}

	this->_currentChannel = channel;
	return this;
}

TrackChunk* TrackChunk::setVoiceProgram(GMPatch patch)
{
	#ifdef METHOD_DEBUG
		printf("TrackChunk::setVoiceProgram()\n");
	#endif // METHOD_DEBUG

	if (this->_closed)
	{
		throw TrackClosedException();
	}

	this->addTrackEvent(EventType::MIDI_EVENT)
		->setDeltaTime(0)
		->getInnerEvent<MidiEvent>()
		->setEventType(MidiEventType::PROGRAM_CHANGE)
		->setChannel(this->_currentChannel)
		->addParam(static_cast<uint8_t>(patch) - 1);

	return this;
}

TrackChunk* TrackChunk::addNote(Note* note)
{
	#ifdef METHOD_DEBUG
		printf("TrackChunk::addNote()\n");
	#endif // METHOD_DEBUG

	if (this->_closed)
	{
		throw TrackClosedException();
	}

	//Note on
	this->addTrackEvent(EventType::MIDI_EVENT)
		->setDeltaTime(0)	//TODO: Delta sums, or something, duration etc.
		->getInnerEvent<MidiEvent>()
		->setEventType(MidiEventType::NOTE_ON)
		->setChannel(this->_currentChannel)
		->addParam(static_cast<uint8_t>(note->pitch()))
		->addParam(note->volume());

	//Note off
	this->addTrackEvent(EventType::MIDI_EVENT)
		->setDeltaTime(note->duration()) //TODO: Delta sums, or something, duration etc.	
		->getInnerEvent<MidiEvent>()
		->setEventType(MidiEventType::NOTE_OFF)
		->setChannel(this->_currentChannel)
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

	if (this->_closed)
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
			->setChannel(this->_currentChannel)
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
			->setChannel(this->_currentChannel)
			->addParam(static_cast<uint8_t>(note->pitch()))
			->addParam(note->volume());

		previousDuration = note->duration();
	}

	return this;
}

void TrackChunk::closeTrack()
{
	if (this->_closed)
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

	this->_closed = true;
}

void TrackChunk::reopenTrack()
{
	if (!this->_closed)
	{
		throw TrackNotClosedException();
	}

	this->_trackEvents.pop_back();
	this->_closed = false;
}

void TrackChunk::prepareToExport()
{
	if (!this->_closed)
	{
		this->closeTrack();
	}

	this->calculateTracksLength();
}


//IConvertibleToByteCollection
std::vector<uint8_t> TrackChunk::toByteVector() const
{
	#ifdef METHOD_DEBUG
		printf("TrackChunk::toByteVector()\n");
	#endif // METHOD_DEBUG

	if (!this->_closed)
	{
		throw TrackNotClosedException();
	}

	std::vector<uint8_t> ret;

	//chunkType
	for (const auto& c : this->_chunkType)
	{
		ret.push_back(c);
	}

	if(!this->_tracksCalculated)
	{
		throw TracksNotCalculatedException();
	}

	//tracksLength
	ret.push_back((this->_tracksLength >> 24) & 0xFF);
	ret.push_back((this->_tracksLength >> 16) & 0xFF);
	ret.push_back((this->_tracksLength >> 8) & 0xFF);
	ret.push_back(this->_tracksLength & 0xFF);

	//trackEvents
	std::vector<uint8_t> tmp;
	for (const auto& te : this->_trackEvents)
	{
		tmp = te->toByteVector();
		ret.insert(ret.end(), tmp.begin(), tmp.end());
	}

	return ret;
}