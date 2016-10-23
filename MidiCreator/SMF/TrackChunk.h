#pragma once

#include "../stdafx.h"
#include "../Interfaces/IConvertibleToByteArray.h"
#include "Events/TrackEvent.h"

namespace SMF 
{
	class TrackChunk : 
		IConvertibleToByteArray
	{
	public:
		const char chunkType[4] = { 'M', 'T', 'r', 'k' };
		unsigned int length;
		int deltaTime;
		TrackEvent* event;


		TrackChunk();
		~TrackChunk();
	};
}

