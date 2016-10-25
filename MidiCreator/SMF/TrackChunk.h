#pragma once

#include "../Abstract/IConvertibleToByteCollection.h"
#include "Events/TrackEvent.h"

namespace SMF 
{
	class TrackChunk : 
		IConvertibleToByteCollection
	{
	private:
		const std::array<char, 4> chunkType = { 'M', 'T', 'r', 'k' };
		uint32_t tracksLength = 0;
		std::vector<TrackEvent*> trackEvents;

		void calculateTracksLength();

	public:
		TrackChunk();
		~TrackChunk();

		TrackEvent* addTrackEvent(EventType);
		TrackEvent* addTrackEvent(TrackEvent*);

		//IConvertibleToByteCollection
		virtual std::vector<uint8_t> toByteVector();		
	};
}

