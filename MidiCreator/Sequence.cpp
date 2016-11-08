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

bool Sequence::nextMeasure()
{
	//TODO: Fix for piano roll size
	if (this->currentMeasure < Sequence::MAX_MEASURE)
	{
		this->currentMeasure++;
		return true;
	}

	return false;
}

bool Sequence::previousNote()
{
	if ((uint8_t)this->firstNoteToShow > (uint8_t)NotePitch::C_MINUS_1)
	{
		this->firstNoteToShow = NotePitch((uint8_t)this->firstNoteToShow + 1);
		return true;
	}

	return false;
}

bool Sequence::nextNote()
{
	//TODO: Fix for piano roll size
	if (this->firstNoteToShow < NotePitch::G9)
	{
		this->firstNoteToShow = NotePitch((uint8_t)this->firstNoteToShow - 1);
		return true;
	}

	return false;
}