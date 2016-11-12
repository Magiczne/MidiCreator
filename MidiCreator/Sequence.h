#pragma once

#include "stdafx.h"
#include "SMF\Enums\NotePitch.h"
#include "SMF\Util\Maps.h"

class Sequence
{
private:
	std::string _name			= "New sequence";
	SMF::FileFormat _format		= SMF::FileFormat::SINGLE_TRACK;
	uint16_t _numerator			= 6;
	uint16_t _denominator		= 8;

public:
	static const unsigned MAX_MEASURE = 35;

	unsigned currentMeasure = 1;
	SMF::NotePitch firstNoteToShow = SMF::NotePitch::C3;

	std::string getFormat() { return SMF::FileFormatMap[this->_format]; }

	bool previousMeasure();
	bool nextMeasure(int pianoRollWidth);

	bool previousNote();
	bool nextNote(int pianoRollHeight);

	//Getters/setters

	void name(const std::string& val) { this->_name = val; }
	const std::string& name() { return this->_name; }

	void format(const SMF::FileFormat& val) { this->_format = val; }
	const SMF::FileFormat& format() { return this->_format; }

	void numerator(const uint16_t& val) { this->_numerator = val; }
	const uint16_t& numerator() { return this->_numerator; };

	void denominator(const uint16_t& val) { this->_denominator = val; }
	const uint16_t& denominator() { return this->_denominator; }

	void setMeasure(const uint16_t& numerator, const uint16_t& denominator);
};

