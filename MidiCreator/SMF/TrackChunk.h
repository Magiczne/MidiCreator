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

		short currentChannel = 1;

		//TODO?
		//void calculateTracksLength();

	public:
		TrackChunk();
		~TrackChunk();

		TrackEvent* addTrackEvent(EventType);
		TrackEvent* addTrackEvent(TrackEvent*);

		TrackChunk* setCurrentChannel(short);

		//IConvertibleToByteCollection
		virtual std::vector<uint8_t> toByteVector();		
	};
}

