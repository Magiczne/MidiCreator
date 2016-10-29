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
		bool closed = false;

		//TODO?
		//void calculateTracksLength();

	public:
		TrackChunk();
		~TrackChunk();

		TrackEvent* addTrackEvent(EventType eventType);
		TrackEvent* addTrackEvent(TrackEvent* event);

		TrackChunk* setCurrentChannel(short channel);

		TrackChunk* setVoiceProgram(short gmPatch);
		//TODO: Note as a enum?
		TrackChunk* addNote(short note, short duration);

		void closeTrack();
		void reopenTrack();

		//IConvertibleToByteCollection
		virtual std::vector<uint8_t> toByteVector();		
	};
}

