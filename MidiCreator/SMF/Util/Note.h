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
		short duration;

	public:
		Note(NotePitch pitch, uint8_t volume, short duration);

		inline const NotePitch& getPitch() { return this->pitch; }
		inline const uint8_t& getVolume() { return this->volume; }
		inline const short& getDuration() { return this->duration; }
	};
}