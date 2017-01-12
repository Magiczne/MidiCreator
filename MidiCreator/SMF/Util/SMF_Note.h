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

		void pitch(const NotePitch& val) { this->_pitch = val; }
		const NotePitch& pitch() const { return this->_pitch; }

		void volume(const uint8_t val) { this->_volume = val; }
		uint8_t volume() const { return this->_volume; }

		void duration(const int val) { this->_duration = val; }
		int duration() const { return this->_duration; }	
	};

	inline bool operator< (const Note& lhs, const Note& rhs) { return lhs.duration() < rhs.duration(); }
}