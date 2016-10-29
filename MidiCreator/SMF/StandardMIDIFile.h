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

		void setCurrentTrack(size_t track);

		void setTimeSignature(uint8_t numerator, 
			uint8_t denominator, 
			uint8_t midiClocksPerMetronomeClick, 
			uint8_t numberOf32NotesInMidiQuarterNote);
		void setTempo(short bpm);


		void exportToFile(string filename);

		//IConvertibleToByteCollection
		virtual std::vector<uint8_t> toByteVector();
	};
}