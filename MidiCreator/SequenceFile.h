#pragma once

#include "stdafx.h"

class Sequence;

class SequenceFile
{
	#pragma region FileHeader

	//+00 4B Magic number
	std::string magicNumber = "MCFF";

	//+04 1B Version number
	uint8_t versionNumber = 0x01;

	//+05 1B [Padding byte]
	uint8_t pad = 0x00;

	//+06 4B CRC-32
	uint32_t crc32;

	//+0A 4B Length of data
	uint32_t dataLength;

	//+10 2B Data offset
	uint16_t dataOffset;

	#pragma endregion

	#pragma region Basic Sequence Data

	//2B Sequence Name Length
	uint16_t nameLength;

	//[nameLength]B	Name
	std::string name;

	//1B FileFormat
	uint8_t fileFormat;

	//2B Measure Numerator
	uint16_t numerator;

	//4B Measure Denominator
	uint16_t denominator;

	#pragma endregion

	#pragma region Notes

	struct NoteData {
		//1B Track Number [0-15]
		uint8_t track;

		//1B Note Pitch [0-127]
		uint8_t notePitch;

		//4B Bar Number
		uint16_t barNumber;

		//1B 32nd note in bar
		uint8_t barPosition;

		//1B Note Volume
		uint8_t noteVolume;
		
		//2B Note Duration
		uint16_t noteDuration;

		//1B Note Ligature
		uint8_t noteLigature;
	};

	std::vector<NoteData> notesData;

	#pragma endregion 

	SequenceFile() {};

public:
	SequenceFile fromSequence(Sequence& seq);
};
