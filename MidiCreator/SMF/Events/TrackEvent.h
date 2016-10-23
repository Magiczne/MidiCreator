#pragma once

#include "../../stdafx.h"
#include "../../Interfaces/IEvent.h"
#include "../../Interfaces/IConvertibleToByteArray.h"

namespace SMF
{
	enum MidiEvent
	{
		NOTE_OFF			= 0x8,
		NOTE_ON				= 0x9,
		KEY_AFTERTOUCH		= 0xA,
		CONTROL_CHANGE		= 0xB,
		PROGRAM_CHANGE		= 0xC,
		CHANNEL_AFTERTOUCH	= 0xD,
		PITCH_WHEEL_CHANGE	= 0xE
	};

	class TrackEvent :
		IEvent,
		IConvertibleToByteArray
	{
	public:
		int vTime;
		IEvent* event;

		TrackEvent();
		~TrackEvent();
	};
}

