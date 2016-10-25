#pragma once

#include "HeaderChunk.h"
#include "TrackChunk.h"

namespace SMF
{
	class StandardMIDIFile
		: IConvertibleToByteCollection
	{
	public:
		HeaderChunk* headerChunk;
		std::vector<TrackChunk*> trackChunks;

		StandardMIDIFile();
		~StandardMIDIFile();

		void setTimeSignature(uint8_t, uint8_t, uint8_t, uint8_t);
		void setTempo();

		//IConvertibleToByteCollection
		virtual std::vector<uint8_t> toByteVector();
	};
}