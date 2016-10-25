#pragma once

namespace SMF
{
	enum MetaEventType
	{
		SEQUENCE_NUMBER = 0x00,
		TEXT_EVENT = 0x01,
		COPYRIGHT_NOTICE = 0x02,
		SEQUENCE_OR_TRACK_NAME = 0x03,
		INSTRUMENT_NAME = 0x04,
		LYRIC_TEXT = 0x05,
		MARKER_TEXT = 0x06,
		CUE_POINT = 0x07,
		MIDI_CHANNEL_PREFIX_ASSIGNMENT = 0x20,
		END_OF_TRACK = 0x2F,
		TEMPO_SETTING = 0x51,
		SMPTE_OFFSET = 0x54,
		//4params[2bytes]	1:numerator		2:denominator	3:MIDI Clocks in metronome click	4:how many 32nd-notes are in MIDI quarter-note
		TIME_SIGNATURE = 0x58,			
		KEY_SIGNATURE = 0x59,						//
		SEQUENCER_SPECIFIC_EVENT = 0x7F				//
	};
}