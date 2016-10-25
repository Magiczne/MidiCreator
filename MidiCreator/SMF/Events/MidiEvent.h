#pragma once

#include "../../stdafx.h"
#include "../../Abstract/IEvent.h"
#include "../Enums/MidiEventType.h"

namespace SMF
{
	class MidiEvent :
		public IEvent
	{
	private:
		MidiEventType type;

	public:
		MidiEvent();
		~MidiEvent();
	};

}
