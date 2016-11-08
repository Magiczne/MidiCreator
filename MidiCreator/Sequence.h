#pragma once

#include "stdafx.h"
#include "SMF\Enums\NotePitch.h"
#include "SMF\Util\Maps.h"

using namespace std;
using namespace SMF;

class Sequence
{
public:
	static const int MAX_MEASURE = 50;

	string name			= "New sequence";
	FileFormat format	= FileFormat::SINGLE_TRACK;
	int numerator		= 4;
	int denominator		= 4;

	unsigned currentMeasure = 1;
	NotePitch firstNoteToShow = NotePitch::C3;

	string getFormat() { return FileFormatMap[this->format]; }

	bool previousMeasure();
	bool nextMeasure();

	bool previousNote();
	bool nextNote();
};

