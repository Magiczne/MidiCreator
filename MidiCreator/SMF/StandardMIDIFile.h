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
		std::vector<TrackChunk> trackChunks;

		StandardMIDIFile();
		~StandardMIDIFile();

		//IConvertibleToByteCollection
		virtual std::vector<uint8_t> toByteVector();
	};
}