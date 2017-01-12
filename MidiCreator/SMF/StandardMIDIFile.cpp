#include "StandardMIDIFile.h"

#include "HeaderChunk.h"
#include "TrackChunk.h"
#include "Events/TrackEvent.h"
#include "Events/MidiEvent.h"
#include "Events/MetaEvent.h"
#include "Exceptions/BpmOutOfRangeException.h"
#include "Exceptions/IllegalDenominatorException.h"
#include "Exceptions/NoTracksException.h"
#include "Exceptions/TrackLimitException.h"
#include "Util/SMF_Note.h"

using namespace SMF;
using namespace Exceptions;

StandardMIDIFile::StandardMIDIFile() : _headerChunk(FileFormat::SINGLE_TRACK) { }

void StandardMIDIFile::setHeader(FileFormat ff, short division)
{
	this->_headerChunk.fileFormat(ff);
	this->_headerChunk.division(division);
}

void StandardMIDIFile::addTrack()
{
	if(this->_headerChunk.fileFormat() == FileFormat::SINGLE_TRACK && 
		_trackChunks.size() == MAX_TRACK_COUNT_SINGLE)
	{
		throw TrackLimitException();
	}
	//TODO: Is there a limit for tracks in MultipleTrack SMF?
	//Probably Single_Track + 1, cause 1st track will contain seq info

	this->_trackChunks.push_back(TrackChunk());
	this->_headerChunk.addTrack();
}

void StandardMIDIFile::setCurrentTrack(size_t track)
{
	if (track > this->_trackChunks.size())
	{
		this->_trackChunks.resize(track);
	}

	this->_currentTrack = track;
}

//TODO: Be sure that sime signature is always first, and tempo is always second if prsent
void StandardMIDIFile::setTimeSignature(
	uint16_t numerator,
	uint16_t denominator,
	uint8_t midiClocksPerMetronomeClick,
	uint8_t numberOf32NotesInMidiQuarterNote)
{
	double convertedDenominator = log2(denominator);
	if (floor(convertedDenominator) != convertedDenominator)
	{
		throw IllegalDenominatorException();
	}

	if (this->_headerChunk.fileFormat() == FileFormat::SINGLE_TRACK)
	{
		if (this->_trackChunks.empty())
		{
			throw NoTracksException();
		}

		this->_trackChunks.front()
			.addTrackEvent(EventType::META_EVENT)
			->setDeltaTime(0)
			.getInnerEvent<MetaEvent>()
			->setEventType(MetaEventType::TIME_SIGNATURE)
			->setLength(4)
			->addParam(static_cast<uint8_t>(numerator))
			->addParam(static_cast<uint8_t>(convertedDenominator))
			->addParam(midiClocksPerMetronomeClick)
			->addParam(numberOf32NotesInMidiQuarterNote);
	}
	else if(this->_headerChunk.fileFormat() == FileFormat::MULTIPLE_TRACK)
	{
		//TODO
	}
	else
	{
		//Multiple Song. Find how to do that
	}
}

void StandardMIDIFile::setTempo(short bpm)
{
	if (bpm < MIN_BPM || bpm > MAX_BPM) 
	{
		throw BpmOutOfRangeException();
	}

	int microSecoundsPerQuarterNote = 60000000 / bpm;

	if (this->_headerChunk.fileFormat() == FileFormat::SINGLE_TRACK)
	{
		if (this->_trackChunks.empty())
		{
			throw NoTracksException();
		}

		this->_trackChunks.front()
			.addTrackEvent(EventType::META_EVENT)
			->setDeltaTime(0)
			.getInnerEvent<MetaEvent>()
			->setEventType(MetaEventType::TEMPO_SETTING)
			->setLength(3)
			->addParam((microSecoundsPerQuarterNote >> 16) & 0xFF)
			->addParam((microSecoundsPerQuarterNote >> 8) & 0xFF)
			->addParam(microSecoundsPerQuarterNote & 0xFF);
	}
	else if (this->_headerChunk.fileFormat() == FileFormat::MULTIPLE_TRACK)
	{
		//TODO: Do that
	}
	else
	{
		//TODO: Multiple Song. Find how to do that
	}
}

void StandardMIDIFile::exportToFile(std::string filename) const
{
	const std::vector<uint8_t> ret = this->toByteVector();

	std::ofstream file(filename, std::ios::trunc | std::ios::binary);
	
	if (file.good())
	{
		for (const auto& byte : ret)
		{
			file << byte;
		}

		file.close();
	}
}

void StandardMIDIFile::addNote(NotePitch pitch, uint8_t volume, int duration)
{
	auto note = Note(pitch, volume, duration);
	this->_trackChunks[this->_currentTrack - 1].addNote(note);
}

void StandardMIDIFile::prepareToExport()
{
	for(auto& tc : this->_trackChunks)
	{
		tc.prepareToExport();
	}
}

std::vector<uint8_t> StandardMIDIFile::toByteVector() const
{
	if (this->_trackChunks.empty())
	{
		throw NoTracksException();
	}

	std::vector<uint8_t> ret = this->_headerChunk.toByteVector();

	std::vector<uint8_t> trackBytes;

	std::vector<uint8_t> tmpVector;
	for (auto& tc : this->_trackChunks)
	{
		tmpVector = tc.toByteVector();
		trackBytes.insert(trackBytes.end(), tmpVector.begin(), tmpVector.end());
	}

	ret.insert(ret.end(), trackBytes.begin(), trackBytes.end());

	return ret;
}