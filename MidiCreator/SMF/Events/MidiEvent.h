#pragma once

#include "../../stdafx.h"
#include "../../Abstract/IEvent.h"
#include "../Enums/MidiEventType.h"
#include "../Enums/MIDIChannel.h"

namespace SMF
{
	class MidiEvent :
		public IEvent
	{
	private:
		MidiEventType type;
		MIDIChannel channel;

	public:
		MidiEvent();
		~MidiEvent();

		MidiEvent* setEventType(MidiEventType eventType);
		MidiEvent* setChannel(MIDIChannel channel);

		virtual std::vector<uint8_t> toByteVector();
	};

}
