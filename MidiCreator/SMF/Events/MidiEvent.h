#pragma once

#include "../../stdafx.h"
#include "../Abstract/IEvent.h"
#include "../Enums/MIDIChannel.h"
#include "../Enums/MidiEventType.h"

namespace SMF
{
	class MidiEvent final : public IEvent
	{
	private:
		MidiEventType type;
		MIDIChannel channel;

		std::array<bool, 2> initialized = { false };
		bool isInitialized();

	public:
		MidiEvent() {};
		MidiEvent(MidiEventType type, MIDIChannel channel);

		MidiEvent* setEventType(MidiEventType eventType);
		MidiEvent* setChannel(MIDIChannel channel);

		//IConvertibleToByteArray
		std::vector<uint8_t> toByteVector() override;
	};
}