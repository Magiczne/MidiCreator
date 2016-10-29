#pragma once

#include "../../stdafx.h"
#include "../Enums/NotePitch.h"

namespace SMF
{
	class Note
	{
	public:
		NotePitch pitch;
		uint8_t volume;
		short duration;

		Note(NotePitch pitch, uint8_t volume, short duration);
	};
}