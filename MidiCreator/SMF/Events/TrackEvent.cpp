#include "TrackEvent.h"

using namespace SMF;

TrackEvent::TrackEvent(EventType eventType)
{
	switch (eventType)
	{
	case EventType::META_EVENT: 
		this->event = new MetaEvent();
		break;
	case EventType::MIDI_EVENT:
		this->event = new MidiEvent();
		break;
	case EventType::SYSTEM_EXCLUSIVE_EVENT:
		this->event = new SystemExclusiveEvent();
		break;
	default:
		//TODO: Throw some exception
	}
}

std::vector<uint8_t> TrackEvent::toByteVector()
{
	std::vector<uint8_t> ret;

	//TODO: Conversion

	return ret;
}

TrackEvent::~TrackEvent()
{
	delete this->event;
}
