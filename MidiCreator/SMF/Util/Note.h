#pragma once

#include "../../stdafx.h"
#include "../Enums/NotePitch.h"

namespace SMF
{
	class Note
	{
	private:
		NotePitch pitch;
		uint8_t volume;
		int duration;

	public:
		Note(NotePitch pitch, uint8_t volume, int duration);

		inline const NotePitch& getPitch() { return this->pitch; }
		inline const uint8_t& getVolume() { return this->volume; }
		inline const int& getDuration() { return this->duration; }
	};
}