#pragma once

#include "stdafx.h"
#include "SMF/Enums/NotePitch.h"
#include "SMF/Util/Maps.h"

class Note;

class Sequence
{
private:
	std::string _name			= "New sequence";
	SMF::FileFormat _format		= SMF::FileFormat::SINGLE_TRACK;
	uint16_t _numerator;
	uint16_t _denominator;

	//TODO: Maybe switch to unordered map
	/**
	 * Pair:
	 *	NotePitch
	 *	bar
	 */
	std::map< std::pair<SMF::NotePitch, unsigned>, std::vector<Note*> > _notes;

public:
	static const unsigned MAX_MEASURE = 35;

	unsigned firstBarToShow = 1;
	SMF::NotePitch firstNoteToShow = SMF::NotePitch::C3;

	//Edit mode specific
	unsigned currentBar = 0;
	unsigned currentNote = 0;

	uint8_t currentNoteInBar = 0;

	Sequence();
	~Sequence();

	bool showPreviousMeasure();
	bool showNextMeasure(uint16_t pianoRollWidth);

	bool showPreviousNote();
	bool showNextNote(uint16_t pianoRollHeight);

	bool moveIndicatorUp();
	bool moveIndicatorDown(uint16_t pianoRollHeight);

	bool moveIndicatorLeft();
	bool moveIndicatorRight(uint16_t pianoRollWidth);

	bool moveCloseUpIndicatorLeft();
	bool moveCloseUpIndicatorRight();

	std::vector<Note*>& getBar(std::pair<SMF::NotePitch, unsigned> coords);
	Note* getNote(std::pair<SMF::NotePitch, unsigned> coords, uint8_t index);
	bool addNote(std::pair<SMF::NotePitch, unsigned> coords, uint8_t index, uint16_t duration);
	bool hasNotes() const { return !this->_notes.empty(); }
	//Getters/setters

	void setMeasure(const uint16_t& numerator, const uint16_t& denominator);
	std::string getFormatString() const { return SMF::FileFormatMap[this->_format]; }

	void name(const std::string& val) { this->_name = val; }
	const std::string& name() const { return this->_name; }

	void format(const SMF::FileFormat& val) { this->_format = val; }
	const SMF::FileFormat& format() const { return this->_format; }

	void numerator(const uint16_t& val) { this->_numerator = val; }
	const uint16_t& numerator() const { return this->_numerator; };

	void denominator(const uint16_t& val) { this->_denominator = val; }
	const uint16_t& denominator() const { return this->_denominator; }

};
