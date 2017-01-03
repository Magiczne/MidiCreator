#include "SequenceFile.h"
#include "Sequence.h"
#include "Note.h"
#include "Util/CRC32.h"
#include "Exceptions/InvalidFileFormatException.h"
#include "Exceptions/InvalidChecksumException.h"
#include "Exceptions/InvalidFileVersionException.h"
#include "Exceptions/InvalidHeaderPaddingException.h"

using namespace std;

int SequenceFile::currentOffset = 0;

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

SequenceFile SequenceFile::open(const string filepath)
{
	ifstream input;
	input.exceptions(ifstream::failbit);

	input.open(filepath, ios_base::binary);

	vector<uint8_t> buffer {
		istreambuf_iterator<char>(input),
		istreambuf_iterator<char>()
	};

	SequenceFile file;

	currentOffset = 0x4;

	#pragma region Header

	//Magic number
	vector<uint8_t> magicNumber(buffer.begin(), buffer.begin() + currentOffset);

	if(string(magicNumber.begin(), magicNumber.end()) != file.magicNumber)
	{
		throw new Exceptions::InvalidFileFormatException;
	}

	//Version number
	
	if(extractFromByteVector<uint8_t>(buffer) != file.versionNumber)
	{
		throw new Exceptions::InvalidFileVersionException;
	}

	//Padding byte
	if(extractFromByteVector<uint8_t>(buffer) != file.pad)
	{
		throw new Exceptions::InvalidHeaderPaddingException;
	}

	//CRC 32
	auto header = vector<uint8_t>(buffer.begin(), buffer.begin() + currentOffset);
	CRC32<> crc;
	uint32_t expectedCRC = crc.update(header);

	uint32_t crc32 = extractFromByteVector<uint32_t>(buffer);

	if(expectedCRC != crc32)
	{
		throw new Exceptions::InvalidChecksumException;
	}

	file.crc32 = crc32;

	//Data length and data offset
	file.dataLength = extractFromByteVector<uint32_t>(buffer);

	file.dataOffset = extractFromByteVector<uint16_t>(buffer);

	#pragma endregion 

	#pragma region Basic data

	//Name length and name
	file.nameLength = extractFromByteVector<uint8_t>(buffer);
	file.nameLength = extractFromByteVector<uint8_t>(buffer);

	vector<uint8_t> sequenceName;
	for(int i = 0; i < file.nameLength; i++)
	{
		sequenceName.push_back(buffer[currentOffset + i]);
	}
	file.name = string(sequenceName.begin(), sequenceName.end());
	currentOffset += file.nameLength;

	//File format
	file.fileFormat = extractFromByteVector<uint8_t>(buffer);

	//Numerator
	file.numerator = extractFromByteVector<uint16_t>(buffer);

	file.denominator = extractFromByteVector<uint16_t>(buffer);

	#pragma endregion

	#pragma region Notes

	file.numberOfNotes = extractFromByteVector<uint32_t>(buffer);

	for(int i = 0; i < file.numberOfNotes; i++)
	{
		file.notesData.push_back({
			extractFromByteVector<uint8_t>(buffer),		//Track number
			extractFromByteVector<uint8_t>(buffer),		//Note pitch
			extractFromByteVector<uint16_t>(buffer),	//Bar numer
			extractFromByteVector<uint8_t>(buffer),		//Bar position
			extractFromByteVector<uint8_t>(buffer),		//Volume
			extractFromByteVector<uint16_t>(buffer),	//Duration
			extractFromByteVector<uint8_t>(buffer)		//Ligature
		});
	}

	#pragma endregion

	return file;
}

bool SequenceFile::saveFile(string path)
{
	ofstream file(path, ios::trunc | ios::binary);

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

#pragma region Private

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
	vector<uint8_t> header = {
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
		this->byteSequence.push_back(noteData.channel);
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
void SequenceFile::add4ByteValueToByteVector(uint32_t val)
{
	for(int8_t i = 24; i >= 0; i -= 8)
	{
		this->byteSequence.push_back((val >> i) & 0xFF);
	}
}
void SequenceFile::addStringToByteVector(string val)
{
	for (auto& ch : val)
	{
		this->byteSequence.push_back(ch);
	}
}

#pragma endregion