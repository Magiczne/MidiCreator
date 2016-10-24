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
		TrackChunk* trackChunk[];

		StandardMIDIFile();
		~StandardMIDIFile();

		//IConvertibleToByteArray
		byte* toByteArray();
	};
}