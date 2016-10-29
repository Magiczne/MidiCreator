#pragma once

#include "..\Abstract\IConvertibleToByteCollection.h"
#include "Enums\GMPatch.h"
#include "Enums\MIDIChannel.h"
#include "Events\TrackEvent.h"

namespace SMF 
{
	class TrackChunk : 
		IConvertibleToByteCollection
	{
	private:
		const std::array<char, 4> chunkType = { 'M', 'T', 'r', 'k' };
		uint32_t tracksLength = 0;
		std::vector<TrackEvent*> trackEvents;

		MIDIChannel currentChannel = MIDIChannel::CHANNEL_1;
		bool closed = false;

		void calculateTracksLength();

	public:
		TrackChunk();
		~TrackChunk();

		TrackEvent* addTrackEvent(EventType eventType);
		TrackEvent* addTrackEvent(TrackEvent* event);

		TrackChunk* setCurrentChannel(MIDIChannel channel);

		TrackChunk* setVoiceProgram(GMPatch patch);
		//TODO: Note as a enum?
		TrackChunk* addNote(short note, unsigned short volume, short duration);

		void closeTrack();
		void reopenTrack();

		//IConvertibleToByteCollection
		virtual std::vector<uint8_t> toByteVector();		
	};
}

