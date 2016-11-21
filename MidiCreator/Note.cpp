#pragma once

#include "Note.h"

Note::Note(SMF::NotePitch pitch) 
	: Note(pitch, 1) {}

Note::Note(SMF::NotePitch pitch, uint16_t duration)
	: Note(pitch, MAX_VOLUME, duration) {}

Note::Note(SMF::NotePitch pitch, uint8_t volume, uint16_t duration)
{
	this->_pitch = pitch;
	this->_volume = volume;
	this->_duration = duration;
}

void Note::volume(const uint8_t& val)
{
	if(val > Note::MAX_VOLUME)
	{
		this->_volume = Note::MAX_VOLUME;
	}
	else
	{
		this->_volume = val;
	}	
}