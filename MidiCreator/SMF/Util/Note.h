#pragma once

#include "../../stdafx.h"
#include "../Enums/NotePitch.h"

namespace SMF
{
	class Note
	{
	private:
		NotePitch _pitch;
		uint8_t _volume;
		int _duration;

	public:
		Note(NotePitch pitch, uint8_t volume, int duration);

		//Getters/setters

		void pitch(const NotePitch& val) { this->_pitch = val; }
		const NotePitch& pitch() const { return this->_pitch; }

		void volume(const uint8_t& val) { this->_volume = val; }
		const uint8_t& volume() const { return this->_volume; }

		void duration(const int& val) { this->_duration = val; }
		const int& duration() const { return this->_duration; }

		//Operators
		bool operator< (const Note& rhs) const { return this->_duration < rhs._duration; }
		bool operator> (const Note& rhs) const { return rhs < *this; }
		bool operator<= (const Note& rhs) const { return !(*this > rhs); }
		bool operator>= (const Note& rhs) const { return !(*this < rhs); }

		bool operator== (const Note& rhs) const { 
			return this->_pitch == rhs._pitch && this->_volume == rhs._volume && this->_duration == rhs._duration; 
		}
		bool operator!= (const Note& rhs) const { return !(*this == rhs); }
	};
}