#include "Sequence.h"

#include "Note.h"

using namespace SMF;
using namespace std;

Sequence::~Sequence()
{
	for(auto& pair : _notes)
	{
		delete pair.second;
	}
}

bool Sequence::showPreviousMeasure()
{
	if (this->firstBarToShow > 1)
	{
		this->firstBarToShow--;
		return true;
	}

	return false;
}

bool Sequence::showNextMeasure(uint16_t pianoRollWidth)
{
	if (this->firstBarToShow < Sequence::MAX_MEASURE - (pianoRollWidth / this->_numerator) + 1)
	{
		this->firstBarToShow++;
		return true;
	}

	return false;
}

bool Sequence::showPreviousNote()
{
	if (this->firstNoteToShow > NotePitch::C_MINUS_1)
	{
		this->firstNoteToShow = NotePitch(static_cast<uint8_t>(this->firstNoteToShow) - 1);
		return true;
	}

	return false;
}

bool Sequence::showNextNote(uint16_t pianoRollHeight)
{
	if (static_cast<uint8_t>(this->firstNoteToShow) < static_cast<uint8_t>(NotePitch::G9) - pianoRollHeight + 1)
	{
		this->firstNoteToShow = NotePitch(static_cast<uint8_t>(this->firstNoteToShow) + 1);
		return true;
	}

	return false;
}

bool Sequence::moveIndicatorUp()
{
	if(this->currentNote > 0)
	{
		this->currentNote--;
		return true;
	}

	return false;
}

bool Sequence::moveIndicatorDown(uint16_t pianoRollHeight)
{
	if(this->currentNote < pianoRollHeight - 1)
	{
		this->currentNote++;
		return true;
	}

	return false;
}

bool Sequence::moveIndicatorLeft()
{
	if(this->currentBar > 0)
	{
		this->currentBar--;
		return true;
	}

	return false;
}

bool Sequence::moveIndicatorRight(uint16_t pianoRollWidth)
{
	if(this->currentBar < pianoRollWidth - 1)
	{
		this->currentBar++;
		return true;
	}

	return false;
}


Note* Sequence::getNote(pair<NotePitch, unsigned> coords)
{
	if(this->_notes.find(coords) == this->_notes.end())
	{
		return nullptr;
	}
	
	return this->_notes.at(coords);
}

bool Sequence::addNote(std::pair<SMF::NotePitch, unsigned> coords, uint16_t duration)
{
	if(this->_notes.find(coords) != this->_notes.end())
	{
		return false;
	}

	this->_notes[coords] = new Note(coords.first, duration);
	return true;
}



void Sequence::setMeasure(const uint16_t& numerator, const uint16_t& denominator)
{
	this->_numerator = numerator;
	this->_denominator = denominator;
}