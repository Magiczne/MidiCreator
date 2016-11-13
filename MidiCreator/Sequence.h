#pragma once

#include "stdafx.h"
#include "SMF/Enums/NotePitch.h"
#include "SMF/Util/Maps.h"

class Sequence
{
private:
	std::string _name			= "New sequence";
	SMF::FileFormat _format		= SMF::FileFormat::SINGLE_TRACK;
	uint16_t _numerator			= 6;
	uint16_t _denominator		= 8;

public:
	static const unsigned MAX_MEASURE = 35;

	unsigned firstBarToShow = 1;
	SMF::NotePitch firstNoteToShow = SMF::NotePitch::C3;

	bool showPreviousMeasure();
	bool showNextMeasure(uint16_t pianoRollWidth);

	bool showPreviousNote();
	bool showNextNote(uint16_t pianoRollHeight);

	//Edit mode specific
	unsigned currentBar = 0;
	unsigned currentNote = 0;

	bool moveIndicatorUp();
	bool moveIndicatorDown(uint16_t pianoRollHeight);

	bool moveIndicatorLeft();
	bool moveIndicatorRight(uint16_t pianoRollWidth);

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