#include "SequenceFile.h"
#include "Sequence.h"
#include "Note.h"
#include "Util/CRC32.h"
#include "Util/Util.h"

SequenceFile::SequenceFile()
{
	this->crc32 = 0;
	this->dataLength = 0;
	this->dataOffset = 0;
	this->nameLength = 0;
	this->name = "";
	this->fileFormat = 0;
	this->numerator = 0;
	this->denominator = 0;

	this->numberOfNotes = 0;
}

SequenceFile SequenceFile::fromSequence(const Sequence& seq)
{
	SequenceFile file;

	#pragma region Basic Sequence Data

	file.name = seq._name;;
	file.nameLength = static_cast<uint8_t>(file.name.length());
	file.fileFormat = static_cast<uint8_t>(seq._format);
	file.numerator = seq._numerator;
	file.denominator = seq._denominator;
	
	#pragma endregion

	uint8_t track = 0;
	uint8_t barPosition;
	for(const auto& map : seq._notes)
	{
		for(const auto& pair : map)
		{
			barPosition = 0;
			for(const auto& note : pair.second)
			{
				if(note != nullptr)
				{
					file.notesData.push_back({
						track,										//Track number
						static_cast<uint8_t>(note->_pitch),			//Note pitch
						static_cast<uint16_t>(pair.first.second),	//Bar number
						barPosition,
						note->_volume,
						note->_duration,
						note->_ligature == true ? static_cast<uint8_t>(0x01) : static_cast<uint8_t>(0x00)
					});
				}
				barPosition++;
			}
		}
		track++;
	}

	file.numberOfNotes = file.notesData.size();

	//Header calculation
	file.calculateDataLength();
	file.calculateDataOffset();
	file.calculateCRC();

	//Creating data vector
	file.toByteVector();

	return file;
}

void SequenceFile::calculateDataLength()
{
	uint32_t len = 16 +						//Header length
		2 + this->nameLength +				//Name
		1 + 2 + 4 + 						//Rest of basic sequence data
		4 +									//Number of notes
		this->numberOfNotes * (1 + 1 + 4 + 1 + 1 + 2 + 1);

	this->dataLength = len;
}

void SequenceFile::calculateDataOffset()
{
	uint16_t offset = 2 + this->nameLength + 1 + 2 + 4;
	this->dataOffset = offset;
}

void SequenceFile::calculateCRC()
{
	CRC32<> crc;
	std::vector<uint8_t> header = {
		static_cast<uint8_t>(this->magicNumber[0]), 
		static_cast<uint8_t>(this->magicNumber[1]),
		static_cast<uint8_t>(this->magicNumber[2]),
		static_cast<uint8_t>(this->magicNumber[3]),
		this->versionNumber, this->pad
	};
	this->crc32 = crc.update(header);
}

void SequenceFile::toByteVector()
{
	this->byteSequence.clear();

	#pragma region FileHeader

	this->addStringToByteVector(this->magicNumber);

	this->byteSequence.push_back(this->versionNumber);
	this->byteSequence.push_back(this->pad);

	this->add4ByteValueToByteVector(this->crc32);
	this->add4ByteValueToByteVector(this->dataLength);
	this->add2ByteValueToByteVector(this->dataOffset);

	#pragma endregion 

	#pragma region Basic Sequence Data

	this->add2ByteValueToByteVector(this->nameLength);
	this->addStringToByteVector(this->name);
	this->byteSequence.push_back(this->fileFormat);
	this->add2ByteValueToByteVector(this->numerator);
	this->add2ByteValueToByteVector(this->denominator);

	#pragma endregion 

	#pragma region Notes

	this->add4ByteValueToByteVector(numberOfNotes);

	for(const auto& noteData : this->notesData)
	{
		this->byteSequence.push_back(noteData.track);
		this->byteSequence.push_back(noteData.notePitch);
		this->add4ByteValueToByteVector(noteData.barNumber);
		this->byteSequence.push_back(noteData.barPosition);
		this->byteSequence.push_back(noteData.noteVolume);
		this->add2ByteValueToByteVector(noteData.noteDuration);
		this->byteSequence.push_back(noteData.noteLigature);
	}

	#pragma endregion
}

void SequenceFile::add2ByteValueToByteVector(uint16_t val)
{
	for (int8_t i = 8; i >= 0; i -= 8)
	{
		this->byteSequence.push_back((val >> i) & 0xFF);
	}
}
void SequenceFile::add4ByteValueToByteVector(uint32_t val)
{
	for(int8_t i = 24; i >= 0; i -= 8)
	{
		this->byteSequence.push_back((val >> i) & 0xFF);
	}
}
void SequenceFile::addStringToByteVector(std::string val)
{
	for (auto& ch : val)
	{
		this->byteSequence.push_back(ch);
	}
}

bool SequenceFile::saveFile(std::string path)
{
	std::ofstream file(path, std::ios::trunc | std::ios::binary);

	UI::Util::debug(this->byteSequence.size());

	if (file.good())
	{
		for (auto &e : this->byteSequence)
		{
			file << e;
		}

		file.close();
		return true;
	}

	return false;
}