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

	public:
		const static short MIN_BPM = 4;
		const static short MAX_BPM = 300;

		StandardMIDIFile();
		~StandardMIDIFile();

		void setTimeSignature(uint8_t, uint8_t, uint8_t, uint8_t);
		void setTempo(short);

		//IConvertibleToByteCollection
		virtual std::vector<uint8_t> toByteVector();
	};
}