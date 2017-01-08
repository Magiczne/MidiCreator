#pragma once

#include "stdafx.h"
#include "SMF/Enums/NotePitch.h"
#include "SMF/Enums/MIDIChannel.h"
#include "SMF/Util/Maps.h"

namespace SMF
{
	class StandardMIDIFile;
}

class SequenceNote;

class Sequence
{
	friend class SequenceFile;

private:
	std::string _name;
	SMF::FileFormat _format;
	uint8_t _tempo;
	uint16_t _numerator;
	uint16_t _denominator;

	unsigned _firstBarToShow;
	SMF::NotePitch _firstPitchToShow;

	SMF::MIDIChannel _currentChannel;
	unsigned _currentNote;
	unsigned _currentNotePitch;
	uint8_t _current32NoteInBar;
	
	uint8_t _numOf32NotesInBar;

	/*
		Array of Tracks(16):
			Map that maps coords(NotePitch and Note) to vector of 32nd notes
				Vector that contains 32nd notes
	*/
	std::array< 
		std::map< 
			std::pair<SMF::NotePitch, unsigned>, 
			std::vector<SequenceNote*>
		>, 
	16> _notes;

public:
	static const unsigned MAX_BAR = 500;
	
	Sequence();
	~Sequence();

	void loadFromFile(const SequenceFile& file);

	bool showPreviousBar();
	bool showNextBar(uint16_t pianoRollWidth);

	bool showPreviousNote();
	bool showNextNote(uint16_t pianoRollHeight);

	bool moveIndicatorUp();
	bool moveIndicatorDown(uint16_t pianoRollHeight);

	bool moveIndicatorLeft();
	bool moveIndicatorRight(uint16_t pianoRollWidth);

	bool moveCloseUpIndicatorLeft();
	bool moveCloseUpIndicatorRight();

	std::vector<SequenceNote*>& getBar(std::pair<SMF::NotePitch, unsigned> coords);
	SequenceNote* getNote(std::pair<SMF::NotePitch, unsigned> coords, uint8_t index);

	SequenceNote* getCurrentNote();
	std::pair<SMF::NotePitch, unsigned> getCurrentNoteCoords() const;

	bool addNoteAtCurrentPosition();
	bool removeNoteAtCurrentPosition();

	SMF::StandardMIDIFile toMidiFile();

	#pragma region Getters/setters

	#pragma region Sequence properties

	void setMeasure(const uint16_t& numerator, const uint16_t& denominator);
	std::string getFormatString() const { return SMF::FileFormatMap[this->_format]; }

	void name(const std::string& val) { this->_name = val; }
	const std::string& name() const { return this->_name; }

	void format(const SMF::FileFormat& val) { this->_format = val; }
	const SMF::FileFormat& format() const { return this->_format; }

	void tempo(const uint8_t& val) { this->_tempo = val; }
	const uint8_t& tempo() const { return this->_tempo; }

	void numerator(const uint16_t& val) { this->_numerator = val; }
	const uint16_t& numerator() const { return this->_numerator; }

	void denominator(const uint16_t& val) { this->_denominator = val; }
	const uint16_t& denominator() const { return this->_denominator; }

	#pragma endregion

	#pragma region Other properties

	void firstBarToShow(const unsigned& val) { this->_firstBarToShow = val; }
	const unsigned& firstBarToShow() const { return this->_firstBarToShow; }

	void firstNoteToShow(const SMF::NotePitch& val) { this->_firstPitchToShow = val; }
	const SMF::NotePitch& firstNoteToShow() const { return this->_firstPitchToShow; }

	void currentChannel(const SMF::MIDIChannel& val) { this->_currentChannel = val; }
	const SMF::MIDIChannel& currentChannel() const { return this->_currentChannel; }

	void currentBar(const unsigned& val) { this->_currentNote = val; }
	const unsigned& currentBar() const { return this->_currentNote; }

	void currentNotePitch(const unsigned& val) { this->_currentNotePitch = val; }
	const unsigned& currentNotePitch() const { return this->_currentNotePitch; }

	void currentNoteInBar(const uint8_t& val) { this->_current32NoteInBar = val; }
	const uint8_t& currentNoteInBar() const { return this->_current32NoteInBar; }

	void numOf32NotesInBar(const uint8_t& val) { this->_numOf32NotesInBar = val; }
	const uint8_t& numOf32NotesInBar() const { return this->_numOf32NotesInBar; }

	#pragma endregion

	#pragma endregion

private:
	bool addNote(std::pair<SMF::NotePitch, unsigned> coords, uint8_t index);
	bool addNote(std::pair<SMF::NotePitch, unsigned> coords, uint8_t index, uint8_t volume, uint16_t duration, bool ligature);

	bool removeNote(std::pair<SMF::NotePitch, unsigned> coords, uint8_t index);
	bool isNotePositionEmpty(const std::pair<SMF::NotePitch, unsigned>& coords, const uint8_t index, const uint8_t channel);

	bool hasNotes() const { return !this->_notes.empty(); }

	bool hasMultipleTracks();
};