#pragma once

#include "Abstract/IConvertibleToByteCollection.h"

namespace SMF
{
	enum class FileFormat : unsigned char;
	class HeaderChunk;
	class TrackChunk;

	class StandardMIDIFile : public IConvertibleToByteCollection
	{
	private:
		HeaderChunk* headerChunk = nullptr;
		std::vector<TrackChunk*> trackChunks;

		size_t currentTrack = 0;

	public:
		const static short MIN_BPM = 4;
		const static short MAX_BPM = 300;

		~StandardMIDIFile();

		void setHeader(FileFormat ff, short division = 96);
		void addTrackChunk(TrackChunk* tc) { this->trackChunks.push_back(tc); }

		void setCurrentTrack(size_t track);

		void setTimeSignature(uint8_t numerator, 
			uint8_t denominator, 
			uint8_t midiClocksPerMetronomeClick = 24, 
			uint8_t numberOf32NotesInMidiQuarterNote = 8);
		void setTempo(short bpm);

		void exportToFile(std::string filename);

		//IConvertibleToByteCollection
		std::vector<uint8_t> toByteVector() override;
	};
}