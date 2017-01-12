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

StandardMIDIFile::StandardMIDIFile() : headerChunk(FileFormat::SINGLE_TRACK)
{
	
}

void StandardMIDIFile::setHeader(FileFormat ff, short division)
{
	this->headerChunk.fileFormat(ff);
	this->headerChunk.division(division);
}

void StandardMIDIFile::addTrack()
{
	if(this->headerChunk.fileFormat() == FileFormat::SINGLE_TRACK && 
		trackChunks.size() == MAX_TRACK_COUNT_SINGLE)
	{
		throw TrackLimitException();
	}
	//TODO: Is there a limit for tracks in MultipleTrack SMF?
	//Probably Single_Track + 1, cause 1st track will contain seq info

	this->trackChunks.push_back(TrackChunk());
	this->headerChunk.addTrack();
}

void StandardMIDIFile::setCurrentTrack(size_t track)
{
	if (track > this->trackChunks.size())
	{
		this->trackChunks.resize(track);
	}

	this->currentTrack = track;
}

/*
throws IllegalDenominatorException
throws NoTrackException
*/
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

	if (this->headerChunk.fileFormat() == FileFormat::SINGLE_TRACK)
	{
		if (this->trackChunks.empty())
		{
			throw NoTracksException();
		}

		this->trackChunks.front()
			.addTrackEvent(EventType::META_EVENT)
			->setDeltaTime(0)
			->getInnerEvent<MetaEvent>()
			->setEventType(MetaEventType::TIME_SIGNATURE)
			->setLength(4)
			->addParam(static_cast<uint8_t>(numerator))
			->addParam(static_cast<uint8_t>(convertedDenominator))
			->addParam(midiClocksPerMetronomeClick)
			->addParam(numberOf32NotesInMidiQuarterNote);
	}
	else if(this->headerChunk.fileFormat() == FileFormat::MULTIPLE_TRACK)
	{
		//TODO
	}
	else
	{
		//Multiple Song. Find how to do that
	}
}

/*
throws SMF::BpmOutOfRangeException
throws SMF::NoTrackException
*/
void StandardMIDIFile::setTempo(short bpm)
{
	if (bpm < MIN_BPM || bpm > MAX_BPM) 
	{
		throw BpmOutOfRangeException();
	}

	int microSecoundsPerQuarterNote = 60000000 / bpm;

	if (this->headerChunk.fileFormat() == FileFormat::SINGLE_TRACK)
	{
		if (this->trackChunks.empty())
		{
			throw NoTracksException();
		}

		this->trackChunks.front()
			.addTrackEvent(EventType::META_EVENT)
			->setDeltaTime(0)
			->getInnerEvent<MetaEvent>()
			->setEventType(MetaEventType::TEMPO_SETTING)
			->setLength(3)
			->addParam((microSecoundsPerQuarterNote >> 16) & 0xFF)
			->addParam((microSecoundsPerQuarterNote >> 8) & 0xFF)
			->addParam(microSecoundsPerQuarterNote & 0xFF);
	}
	else if (this->headerChunk.fileFormat() == FileFormat::MULTIPLE_TRACK)
	{
		//TODO: Do that
	}
	else
	{
		//TODO: Multiple Song. Find how to do that
	}
}

void StandardMIDIFile::exportToFile(std::string filename)
{
	std::vector<uint8_t> ret = this->toByteVector();

	std::ofstream file(filename, std::ios::trunc | std::ios::binary);
	
	if (file.good())
	{
		for (auto &e : ret)
		{
			file << e;
		}

		file.close();
	}
}

void StandardMIDIFile::addNote(NotePitch pitch, uint8_t volume, int duration)
{
	auto note = new Note(pitch, volume, duration);
	this->trackChunks[this->currentTrack - 1].addNote(note);
}


std::vector<uint8_t> StandardMIDIFile::toByteVector() const
{
	if (this->trackChunks.empty())
	{
		throw NoTracksException();
	}

	std::vector<uint8_t> ret = this->headerChunk.toByteVector();

	std::vector<uint8_t> trackBytes;

	std::vector<uint8_t> tmpVector;
	for (auto &a : this->trackChunks)
	{
		tmpVector = a.toByteVector();
		trackBytes.insert(trackBytes.end(), tmpVector.begin(), tmpVector.end());
	}

	ret.insert(ret.end(), trackBytes.begin(), trackBytes.end());

	return ret;
}