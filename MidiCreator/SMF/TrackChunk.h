#pragma once

#include "../Interfaces/IConvertibleToByteArray.h"
#include "Events/TrackEvent.h"

namespace SMF 
{
	class TrackChunk : 
		IConvertibleToByteArray
	{
	public:
		const std::array<char, 4> chunkType = { 'M', 'T', 'r', 'k' };
		unsigned int length;
		int deltaTime;
		TrackEvent* event;


		TrackChunk();
		~TrackChunk();

		//IConvertibleToByteArray
		byte* toByteArray();
	};
}

