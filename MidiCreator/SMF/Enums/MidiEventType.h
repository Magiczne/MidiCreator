#pragma once

namespace SMF
{
	enum class MidiEventType : uint8_t
	{
		NOTE_OFF			= 0x80,	//2 params		Param1: key						Param2: velocity
		NOTE_ON				= 0x90,	//2 params		Param1: key						Param2: velocity
		KEY_AFTERTOUCH		= 0xA0,	//2 params		Param1: key						Param2: touch
		CONTROL_CHANGE		= 0xB0,	//2 params		Param1: controller number		Param2: controller value
		PROGRAM_CHANGE		= 0xC0,	//2 params		Param1: Instrument number		Param2: ?
		CHANNEL_PRESSURE	= 0xD0,	//1 param		Param1: pressure
		PITCH_WHEEL_CHANGE	= 0xE0,	//2 params		Param1: LSB(7bits)				Param2: MSB(7bits)

		COUNT
	};
}
