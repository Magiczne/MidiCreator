#pragma once

#include "stdafx.h"
#include "SMF\Util\Maps.h"

using namespace std;
using namespace SMF;

class Sequence
{
public:
	string name = "New sequence";
	FileFormat format = FileFormat::SINGLE_TRACK;

	Sequence();
	~Sequence();

	string getFormat() { return FileFormatMap[this->format]; }
};

