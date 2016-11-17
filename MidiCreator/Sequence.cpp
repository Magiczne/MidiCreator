#include "Sequence.h"

#include "Note.h"

using namespace SMF;
using namespace std;

Sequence::Sequence()
{
	this->setMeasure(6, 8);
	this->_notes.clear();
}

Sequence::~Sequence()
{
	for (auto& pair : _notes)
	{
		for(auto& note : pair.second)
		{
			delete note;
		}
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
	if (this->currentNote > 0)
	{
		this->currentNote--;
		return true;
	}

	return false;
}

bool Sequence::moveIndicatorDown(uint16_t pianoRollHeight)
{
	if (this->currentNote < pianoRollHeight - 1)
	{
		this->currentNote++;
		return true;
	}

	return false;
}

bool Sequence::moveIndicatorLeft()
{
	if (this->currentBar > 0)
	{
		this->currentBar--;
		return true;
	}

	return false;
}

bool Sequence::moveIndicatorRight(uint16_t pianoRollWidth)
{
	if (this->currentBar < pianoRollWidth - 1)
	{
		this->currentBar++;
		return true;
	}

	return false;
}

bool Sequence::moveCloseUpIndicatorLeft()
{
	if(this->currentNoteInBar > 0)
	{
		this->currentNoteInBar--;
		return true;
	}

	return false;
}

bool Sequence::moveCloseUpIndicatorRight()
{
	//TODO: Maybe move to a member var
	uint8_t numOfNotes = static_cast<uint8_t>(pow(2, 5 - log2(this->_denominator))) - 1;
	
	if(this->currentNoteInBar < numOfNotes)
	{
		this->currentNoteInBar++;
		return true;
	}

	return false;
}



vector<Note*>& Sequence::getBar(pair<NotePitch, unsigned> coords)
{
	return this->_notes[coords];
}

Note* Sequence::getNote(pair<NotePitch, unsigned> coords, uint8_t index)
{
	if(this->_notes[coords].size() == 0)
	{
		return nullptr;
	}

	return this->_notes[coords][index];
}

bool Sequence::addNote(pair<NotePitch, unsigned> coords, 
	uint8_t index, uint16_t duration)
{
	if(this->_notes.find(coords) == this->_notes.end())
	{
		this->_notes[coords] = vector<Note*>(0);
	}

	if (this->_notes[coords].size() == 0)
	{
		size_t newSize = pow(2, 5 - log2(this->_denominator));
		this->_notes[coords].resize(newSize);

		for(auto& a : this->_notes[coords])
		{
			a = nullptr;
		}
	}

	if(this->_notes[coords][index] != nullptr)
	{
		return false;
	}

	this->_notes[coords][index] = new Note(coords.first, duration);
	return true;
}

void Sequence::setMeasure(const uint16_t& numerator, const uint16_t& denominator)
{
	this->_numerator = numerator;
	this->_denominator = denominator;
}
