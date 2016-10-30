#pragma once

#include "HeaderChunk.h"
#include "TrackChunk.h"

namespace SMF
{
	class StandardMIDIFile
		: IConvertibleToByteCollection
	{
	private:
		HeaderChunk* headerChunk;
		std::vector<TrackChunk*> trackChunks;

		size_t currentTrack;

	public:
		const static short MIN_BPM = 4;
		const static short MAX_BPM = 300;

		StandardMIDIFile();
		~StandardMIDIFile();

		void setHeader(HeaderChunk* hc) { this->headerChunk = hc; }
		void addTrackChunk(TrackChunk* tc) { this->trackChunks.push_back(tc); }

		void setCurrentTrack(size_t track);

		void setTimeSignature(uint8_t numerator, 
			uint8_t denominator, 
			uint8_t midiClocksPerMetronomeClick = 24, 
			uint8_t numberOf32NotesInMidiQuarterNote = 8);
		void setTempo(short bpm);

		void exportToFile(std::string filename);

		//IConvertibleToByteCollection
		virtual std::vector<uint8_t> toByteVector();
	};
}