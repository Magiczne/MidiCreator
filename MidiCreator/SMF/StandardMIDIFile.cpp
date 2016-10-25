#include "StandardMIDIFile.h"

using namespace SMF;

StandardMIDIFile::StandardMIDIFile()
{
}

std::vector<uint8_t> StandardMIDIFile::toByteVector()
{
	std::vector<uint8_t> ret = this->headerChunk->toByteVector();

	std::vector<uint8_t> trackBytes;

	std::vector<uint8_t> tmpVector;
	for (auto &a : this->trackChunks)
	{
		tmpVector = a->toByteVector();
		trackBytes.insert(trackBytes.end(), tmpVector.begin(), tmpVector.end());
	}

	ret.insert(ret.end(), trackBytes.begin(), trackBytes.end());

	return ret;
}

void StandardMIDIFile::setTimeSignature(
	uint8_t numerator,
	uint8_t denominator,
	uint8_t midiClocksPerMetronomeClick,
	uint8_t numerOf32NotesInMidiQuarterNote)
{
	double convertedDenominator = log2(denominator);
	if (floor(convertedDenominator) != convertedDenominator)
	{
		//TODO: Throw some exception
	}

	if (this->headerChunk->getFileFormat() == FileFormat::SINGLE_TRACK)
	{
		if (trackChunks.empty())
		{
			trackChunks.push_back(new TrackChunk());
		}

		auto innerEvent = trackChunks.front()
			->addTrackEvent(EventType::META_EVENT)
			->getInnerEvent();

		MetaEvent* e = dynamic_cast<MetaEvent*>(innerEvent);
		e->setEventType(MetaEventType::TIME_SIGNATURE)
			->setLength(4)
			->addParam(numerator)
			->addParam(static_cast<uint8_t>(convertedDenominator))
			->addParam(midiClocksPerMetronomeClick)
			->addParam(numerOf32NotesInMidiQuarterNote);
	}
	else if(this->headerChunk->getFileFormat() == FileFormat::MULTIPLE_TRACK)
	{
		//TODO
	}
	else
	{
		//Multiple Song. Find how to do that
	}
}

void StandardMIDIFile::setTempo()
{

}

StandardMIDIFile::~StandardMIDIFile()
{
	for (auto &tc : this->trackChunks)
		delete tc;
}
