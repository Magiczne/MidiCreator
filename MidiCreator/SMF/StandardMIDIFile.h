#pragma once

#include "Abstract/IConvertibleToByteCollection.h"
#include "HeaderChunk.h"
#include "TrackChunk.h"

namespace SMF
{
	enum class NotePitch : unsigned char;
	enum class FileFormat : unsigned char;

	class StandardMIDIFile : public IConvertibleToByteCollection
	{
	private:
		const short MAX_TRACK_COUNT_SINGLE = 16;

		HeaderChunk _headerChunk;
		std::vector<TrackChunk> _trackChunks;

		size_t _currentTrack = 0;

	public:
		const static short MIN_BPM = 4;
		const static short MAX_BPM = 300;

		StandardMIDIFile();

		void setHeader(FileFormat ff, short division = 96);
		void addTrack();

		void setCurrentTrack(size_t track);

		void setTimeSignature(uint16_t numerator, 
			uint16_t denominator, 
			uint8_t midiClocksPerMetronomeClick = 24, 
			uint8_t numberOf32NotesInMidiQuarterNote = 8);
		void setTempo(short bpm);

		void setVoiceProgram(GMPatch patch);

		void addNote(NotePitch pitch, uint8_t volume, int duration);

		void exportToFile(std::string filename) const;

		short get32NoteDuration() const { return this->_headerChunk.division() / 8; }
		
		void prepareToExport();
		//IConvertibleToByteCollection
		std::vector<uint8_t> toByteVector() const override;
	};
}
