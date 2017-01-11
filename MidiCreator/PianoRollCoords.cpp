#include "stdafx.h"
#include "PianoRollCoords.h"

using namespace SMF;

PianoRollCoords::PianoRollCoords(NotePitch p, unsigned n)
	: _pitch{ p }, _nominalNotePosition{ n } {};

PianoRollCoords::PianoRollCoords(uint8_t p, unsigned n)
	: _pitch{ NotePitch(p) }, _nominalNotePosition{ n } {};

bool operator<(const PianoRollCoords& lhs, const PianoRollCoords& rhs)
{
	///http://en.cppreference.com/w/cpp/utility/pair/operator_cmp
	//If lhs.first<rhs.first, returns true. 
	//Otherwise, if rhs.first<lhs.first, returns false. 
	//Otherwise, if lhs.second<rhs.second, returns true. 
	//Otherwise, returns false.

	if (lhs.pitch() < rhs.pitch())
	{
		return true;
	}

	if (rhs.pitch() < lhs.pitch())
	{
		return false;
	}

	if (lhs.notePosition() < rhs.notePosition())
	{
		return true;
	}

	return false;
}

bool operator==(const PianoRollCoords& lhs, const PianoRollCoords& rhs)
{
	return lhs.pitch() == rhs.pitch() && lhs.notePosition() == rhs.notePosition();
}