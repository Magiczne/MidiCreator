#pragma once

#include "HeaderChunk.h"
#include "TrackChunk.h"

namespace SMF
{
	class StandardMIDIFile
		: IConvertibleToByteArray
	{
	public:
		HeaderChunk* headerChunk;
		std::vector<TrackChunk> trackChunks;

		StandardMIDIFile();
		~StandardMIDIFile();

		//IConvertibleToByteArray
		byte* toByteArray();
	};
}