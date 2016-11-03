#include "MidiEvent.h"

using namespace SMF;
using namespace SMF::Exceptions;

MidiEvent::MidiEvent() {}

MidiEvent::MidiEvent(MidiEventType type, MIDIChannel channel) :
	type(type), channel(channel)
{
	this->initialized = { true };
}

MidiEvent* MidiEvent::setEventType(MidiEventType eventType)
{
	this->type = eventType;
	this->initialized[0] = true;
	return this;
}

MidiEvent* MidiEvent::setChannel(MIDIChannel channel)
{
	this->channel = channel;
	this->initialized[1] = true;
	return this;
}

std::vector<uint8_t> MidiEvent::toByteVector()
{
#ifdef METHOD_DEBUG
	printf("MidiEvent::toByteVector()\n");
#endif // METHOD_DEBUG

	if (!this->isInitialized())
	{
		throw new EventNotInitializedException;
	}

	std::vector<uint8_t> a;

	a.push_back((uint8_t)this->type | (uint8_t)this->channel);

	a.insert(a.end(), this->params.begin(), this->params.end());

	return a;
}

bool MidiEvent::isInitialized()
{
	for (auto &i : this->initialized)
	{
		if (!i)
		{
			return false;
		}
	}
	return true;
}

