#include "TrackEvent.h"

#include "MetaEvent.h"
#include "MidiEvent.h"
#include "SystemExclusiveEvent.h"

#include "../Exceptions/EventTypeNotSupportedException.h"

using namespace std;
using namespace SMF;
using namespace SMF::Exceptions;

TrackEvent::TrackEvent(EventType eventType)
{
	switch (eventType)
	{
		case EventType::META_EVENT: 
			this->_event = make_shared<MetaEvent>();
			break;
		case EventType::MIDI_EVENT:
			this->_event = make_shared<MidiEvent>();
			break;
		case EventType::SYSTEM_EXCLUSIVE_EVENT:
			this->_event = make_shared<SystemExclusiveEvent>();
			break;
		default:
			throw EventTypeNotSupportedException();
	}
}

TrackEvent& TrackEvent::setDeltaTime(int time)
{ 
	this->_deltaTime = make_unique<VLQ>(time);
	return *this;
}
std::vector<uint8_t> TrackEvent::toByteVector() const
{
#ifdef METHOD_DEBUG
	printf("TrackEvent::toByteVector()\n");
#endif // METHOD_DEBUG

	if (!this->isInitialized())
	{
		throw EventNotInitializedException();
	}
	
	std::vector<uint8_t> ret = this->_deltaTime->getVlq();

	std::vector<uint8_t> eventBytes = this->_event->toByteVector();

	ret.insert(ret.end(), eventBytes.begin(), eventBytes.end());

	return ret;
}

bool TrackEvent::isInitialized() const
{
	return !(this->_deltaTime == nullptr || this->_event == nullptr);
}