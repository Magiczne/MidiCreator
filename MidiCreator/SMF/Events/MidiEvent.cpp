#include "MidiEvent.h"

#include "../Exceptions/EventNotInitializedException.h"

using namespace SMF;
using namespace SMF::Exceptions;


MidiEvent::MidiEvent(MidiEventType type, MIDIChannel channel) :
	_type(type), _channel(channel)
{
	this->_initialized = { true };
}

MidiEvent* MidiEvent::setEventType(MidiEventType eventType)
{
	this->_type = eventType;
	this->_initialized[0] = true;
	return this;
}

MidiEvent* MidiEvent::setChannel(MIDIChannel channel)
{
	this->_channel = channel;
	this->_initialized[1] = true;
	return this;
}

std::vector<uint8_t> MidiEvent::toByteVector() const
{
#ifdef METHOD_DEBUG
	printf("MidiEvent::toByteVector()\n");
#endif // METHOD_DEBUG

	if (!this->isInitialized())
	{
		throw EventNotInitializedException();
	}

	std::vector<uint8_t> a;

	a.push_back(static_cast<uint8_t>(this->_type) | static_cast<uint8_t>(this->_channel));

	a.insert(a.end(), this->params.begin(), this->params.end());

	return a;
}

bool MidiEvent::isInitialized() const
{
	for (const auto& i : this->_initialized)
	{
		if (!i)
		{
			return false;
		}
	}
	return true;
}