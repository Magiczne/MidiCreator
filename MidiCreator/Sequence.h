#pragma once

#include "stdafx.h"
#include "SMF\Enums\NotePitch.h"
#include "SMF\Util\Maps.h"

class Sequence
{
public:
	static const unsigned MAX_MEASURE = 35;

	std::string name		= "New sequence";
	SMF::FileFormat format	= SMF::FileFormat::SINGLE_TRACK;
	int numerator			= 6;
	int denominator			= 8;

	unsigned currentMeasure = 1;
	SMF::NotePitch firstNoteToShow = SMF::NotePitch::C3;

	std::string getFormat() { return SMF::FileFormatMap[this->format]; }

	bool previousMeasure();
	bool nextMeasure(int pianoRollWidth);

	bool previousNote();
	bool nextNote(int pianoRollHeight);
};

