#include "MidiEvent.h"

using namespace SMF;

MidiEvent::MidiEvent()
{
}

MidiEvent::~MidiEvent()
{
}

MidiEvent* MidiEvent::setEventType(MidiEventType eventType)
{
	this->type = eventType;
	return this;
}

MidiEvent* MidiEvent::setChannel(MIDIChannel channel)
{
	this->channel = channel;
	return this;
}

std::vector<uint8_t> MidiEvent::toByteVector()
{
	#ifdef DEBUG
		printf("MidiEvent::toByteVector()\n");
	#endif // DEBUG

	std::vector<uint8_t> a;

	a.push_back((uint8_t)this->type | (uint8_t)this->channel);

	a.insert(a.end(), this->params.begin(), this->params.end());

	return a;
}

