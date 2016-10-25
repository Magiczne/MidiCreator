#pragma once

#include "../../stdafx.h"
#include "../Enums/MidiEventType.h"

namespace SMF
{
	class MidiEvent :
		public IEvent
	{
	private:
		MidiEventType type;
		std::vector<uint8_t> params;

	public:
		MidiEvent();
		~MidiEvent();
	};

}
