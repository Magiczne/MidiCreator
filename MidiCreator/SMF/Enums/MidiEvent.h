#pragma once

namespace SMF
{
	enum MidiEvent
	{
		NOTE_OFF = 0x8,				//2 params		Param1: key						Param2: velocity
		NOTE_ON = 0x9,				//2 params		Param1: key						Param2: velocity
		KEY_AFTERTOUCH = 0xA,		//2 params		Param1: key						Param2: touch
		CONTROL_CHANGE = 0xB,		//2 params		Param1: controller number		Param2: controller value
		PROGRAM_CHANGE = 0xC,		//2 params		Param1: Instrument number		Param2: ?
		CHANNEL_PRESSURE = 0xD,		//1 param		Param1: pressure
		PITCH_WHEEL_CHANGE = 0xE	//2 params		Param1: LSB(7bits)				Param2: MSB(7bits)
	};
}
