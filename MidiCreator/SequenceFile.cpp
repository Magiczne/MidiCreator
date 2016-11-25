#include "SequenceFile.h"
#include "Sequence.h"
#include "Note.h"

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
}

SequenceFile SequenceFile::fromSequence(Sequence& seq)
{
	SequenceFile file;

	#pragma region Basic Sequence Data

	file.name = seq._name;;
	file.nameLength = file.name.length();
	file.fileFormat = static_cast<uint8_t>(seq._format);
	file.numerator = seq._numerator;
	file.denominator = seq._denominator;
	
	#pragma endregion

	uint8_t track = 0;
	uint8_t barPosition;
	for(auto& map : seq._notes)
	{
		for(auto& pair : map)
		{
			barPosition = 0;
			for(auto& note : pair.second)
			{
				if(note != nullptr)
				{
					file.notesData.push_back({
						track,									//Track number
						static_cast<uint8_t>(note->_pitch),		//Note pitch
						pair.first.second,						//Bar number
						barPosition,
						note->_volume,
						note->_duration,
						note->_ligature == true ? 0x01 : 0x00
					});
				}
				barPosition++;
			}
		}
		track++;
	}

	file.notesDataLength = file.notesData.size();

	//TODO: Calculate dataLength
	//TODO: Calculate dataOffset
	//TODO: Calculate CRC For header

	return file;
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

	this->add4ByteValueToByteVector(notesDataLength);

	for(auto& noteData : this->notesData)
	{
		this->byteSequence.push_back(noteData.track);
		this->byteSequence.push_back(noteData.notePitch);
		this->add2ByteValueToByteVector(noteData.barNumber);
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
void SequenceFile::add4ByteValueToByteVector(uint16_t val)
{
	for(int8_t i = 24; i >= 0; i++)
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