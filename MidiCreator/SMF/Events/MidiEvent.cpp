#include "MidiEvent.h"

using namespace SMF;

MidiEvent::MidiEvent()
{
}

std::vector<uint8_t> MidiEvent::toByteVector()
{
	std::vector<uint8_t> a;

	a.push_back(this->type);

	return a;
}


MidiEvent::~MidiEvent()
{
}
