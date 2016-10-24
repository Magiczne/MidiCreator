#pragma once

#include "../Abstract/IConvertibleToByteArray.h"
#include "Events/TrackEvent.h"

namespace SMF 
{
	class TrackChunk : 
		IConvertibleToByteArray
	{
	public:
		const std::array<char, 4> chunkType = { 'M', 'T', 'r', 'k' };
		unsigned int length;
		TrackEvent* event;


		TrackChunk();
		~TrackChunk();

		//IConvertibleToByteArray
		virtual std::vector<byte> toByteVector();
	};
}

