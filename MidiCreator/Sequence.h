#pragma once

#include "stdafx.h"
#include "SMF\Enums\NotePitch.h"
#include "SMF\Util\Maps.h"

using namespace std;
using namespace SMF;

class Sequence
{
public:
	static const int MAX_MEASURE = 35;

	string name			= "New sequence";
	FileFormat format	= FileFormat::SINGLE_TRACK;
	int numerator		= 6;
	int denominator		= 8;

	unsigned currentMeasure = 1;
	NotePitch firstNoteToShow = NotePitch::C3;

	string getFormat() { return FileFormatMap[this->format]; }

	bool previousMeasure();
	bool nextMeasure(int pianoRollWidth);

	bool previousNote();
	bool nextNote(int pianoRollHeight);
};

