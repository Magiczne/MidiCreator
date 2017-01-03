#pragma once

#include "Note.h"

using namespace SMF;

Note::Note(NotePitch pitch) 
	: Note(pitch, 1) {}

Note::Note(NotePitch pitch, uint16_t duration)
	: Note(pitch, MAX_VOLUME, duration) {}

Note::Note(NotePitch pitch, uint8_t volume, uint16_t duration)
	: Note(pitch, volume, duration, false) {}

Note::Note(SMF::NotePitch pitch, uint8_t volume, uint16_t duration, bool ligature)
{
	this->pitch(pitch);
	this->volume(volume);
	this->duration(duration);
	this->ligature(ligature);
}

void Note::volume(const uint8_t& val)
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