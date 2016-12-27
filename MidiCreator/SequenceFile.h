#pragma once

#include "stdafx.h"
#include "Util/Util.h"

class Sequence;

class SequenceFile
{
	//File header
	//16B
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

	//+12 2B Sequence Name Length
	uint16_t nameLength;

	//+14 [nameLength]B	Name
	std::string name;

	//1B FileFormat
	uint8_t fileFormat;

	//2B Measure Numerator
	uint16_t numerator;

	//4B Measure Denominator
	uint16_t denominator;

	#pragma endregion

	#pragma region Notes

	//11B
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

	//4B Size of notes data vector
	uint32_t numberOfNotes;

	std::vector<NoteData> notesData;

	#pragma endregion 

	std::vector<uint8_t> byteSequence;

	SequenceFile();

	void calculateDataLength();
	void calculateDataOffset();
	void calculateCRC();

	void toByteVector();

	void add2ByteValueToByteVector(uint16_t);
	void add4ByteValueToByteVector(uint32_t);
	void addStringToByteVector(std::string);

	///Extraction
	static int currentOffset;

	template<typename T>
	static T extractFromByteVector(const std::vector<uint8_t>&);

	template<typename T>
	static T swapEndian(const T&);
public:
	static SequenceFile fromSequence(const Sequence& seq);
	static SequenceFile open(const std::string filepath);

	bool saveFile(std::string path);
};

template <typename T>
T SequenceFile::extractFromByteVector(const std::vector<uint8_t>& v)
{
	T value = *reinterpret_cast<const T*>(&v[currentOffset]);

	currentOffset += sizeof(T);

	UI::Util::debug(std::string(typeid(T).name()) + " -> " + std::to_string(sizeof(T)) + " (" + std::to_string(currentOffset) + ")\n");

	return sizeof(T) > 1 ? swapEndian<T>(value) : value;
}

template <typename T>
T SequenceFile::swapEndian(const T& num)
{
	static_assert(CHAR_BIT == 8, "CHAR_BIT != 8");

	union
	{
		T u;
		uint8_t u8[sizeof(T)];
	} source, dest;

	source.u = num;

	for(size_t i = 0; i < sizeof(T); i++)
	{
		dest.u8[i] = source.u8[sizeof(T) - i - 1];
	}

	return dest.u;
}