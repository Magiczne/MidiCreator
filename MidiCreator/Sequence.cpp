#include "Sequence.h"

bool Sequence::previousMeasure()
{
	if (this->currentMeasure > 1)
	{
		this->currentMeasure--;
		return true;
	}

	return false;
}

bool Sequence::nextMeasure(int pianoRollWidth)
{
	if (this->currentMeasure < Sequence::MAX_MEASURE - (pianoRollWidth / this->numerator) + 1)
	{
		this->currentMeasure++;
		return true;
	}

	return false;
}

bool Sequence::previousNote()
{
	if (this->firstNoteToShow > NotePitch::C_MINUS_1)
	{
		this->firstNoteToShow = NotePitch((uint8_t)this->firstNoteToShow - 1);
		return true;
	}

	return false;
}

bool Sequence::nextNote(int pianoRollHeight)
{
	//TODO: Fix for piano roll size
	if ((uint8_t)this->firstNoteToShow < (uint8_t)NotePitch::G9 - pianoRollHeight + 1)
	{
		this->firstNoteToShow = NotePitch((uint8_t)this->firstNoteToShow + 1);
		return true;
	}

	return false;
}