#include "MidiEvent.h"

using namespace SMF;

MidiEvent::MidiEvent()
{
}

std::vector<uint8_t> MidiEvent::toByteVector()
{
	std::vector<uint8_t> a;

	a.push_back(this->type);
	a.insert(a.begin(), this->params.begin(), this->params.end());

	return a;
}


MidiEvent::~MidiEvent()
{
}
