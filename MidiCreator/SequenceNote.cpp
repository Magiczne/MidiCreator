#pragma once

#include "SequenceNote.h"

using namespace SMF;

SequenceNote::SequenceNote(NotePitch pitch)
	: SequenceNote(pitch, 1) {}

SequenceNote::SequenceNote(NotePitch pitch, uint16_t duration)
	: SequenceNote(pitch, MAX_VOLUME, duration) {}

SequenceNote::SequenceNote(NotePitch pitch, uint8_t volume, uint16_t duration)
	: SequenceNote(pitch, volume, duration, false) {}

SequenceNote::SequenceNote(NotePitch pitch, uint8_t volume, uint16_t duration, bool ligature) 
	: _pitch(pitch), _volume(volume), _duration(duration), _ligature(ligature) {}

void SequenceNote::volume(const uint8_t val)
{
	if(val > MAX_VOLUME)
	{
		this->_volume = MAX_VOLUME;
	}
	else
	{
		this->_volume = val;
	}	
}