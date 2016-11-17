#include "Sequence.h"

#include "Note.h"
#include "Util/Util.h"

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
	if (this->_firstBarToShow > 1)
	{
		this->_firstBarToShow--;
		return true;
	}

	return false;
}

bool Sequence::showNextMeasure(uint16_t pianoRollWidth)
{
	if (this->_firstBarToShow < Sequence::MAX_MEASURE - (pianoRollWidth / this->_numerator) + 1)
	{
		this->_firstBarToShow++;
		return true;
	}

	return false;
}

bool Sequence::showPreviousNote()
{
	if (this->_firstNoteToShow > NotePitch::C_MINUS_1)
	{
		this->_firstNoteToShow = NotePitch(static_cast<uint8_t>(this->_firstNoteToShow) - 1);
		return true;
	}

	return false;
}

bool Sequence::showNextNote(uint16_t pianoRollHeight)
{
	if (static_cast<uint8_t>(this->_firstNoteToShow) < static_cast<uint8_t>(NotePitch::G9) - pianoRollHeight + 1)
	{
		this->_firstNoteToShow = NotePitch(static_cast<uint8_t>(this->_firstNoteToShow) + 1);
		return true;
	}

	return false;
}

bool Sequence::moveIndicatorUp()
{
	if (this->_currentNotePitch > 0)
	{
		this->_currentNotePitch--;
		return true;
	}

	return false;
}

bool Sequence::moveIndicatorDown(uint16_t pianoRollHeight)
{
	if (this->_currentNotePitch < pianoRollHeight - 1U)
	{
		this->_currentNotePitch++;
		return true;
	}

	return false;
}

bool Sequence::moveIndicatorLeft()
{
	if (this->_currentBar > 0)
	{
		this->_currentBar--;
		return true;
	}

	return false;
}

bool Sequence::moveIndicatorRight(uint16_t pianoRollWidth)
{
	if (this->_currentBar < pianoRollWidth - 1U)
	{
		this->_currentBar++;
		return true;
	}

	return false;
}

bool Sequence::moveCloseUpIndicatorLeft()
{
	if(this->_currentNoteInBar > 0)
	{
		this->_currentNoteInBar--;
		return true;
	}

	return false;
}

bool Sequence::moveCloseUpIndicatorRight()
{
	if(this->_currentNoteInBar < this->_numOf32NotesInBar -1)
	{
		this->_currentNoteInBar++;
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
	if(this->_notes.find(coords) == this->_notes.end())
	{
		return nullptr;
	}

	if(this->_notes[coords].size() == 0)
	{
		return nullptr;
	}

	return this->_notes[coords][index];
}

Note* Sequence::getCurrentNote()
{
	auto coords = this->getCurrentNoteCoords();
	auto note = this->getNote({ coords.first, coords.second }, this->_currentNoteInBar);

	return note;
}

pair<NotePitch, unsigned> Sequence::getCurrentNoteCoords() const
{
	uint8_t pitch = static_cast<uint8_t>(this->_firstNoteToShow) + this->_currentNotePitch;
	unsigned bar = (this->_firstBarToShow - 1) * this->_numerator + this->_currentBar;

	return{ NotePitch(pitch), bar };
}

bool Sequence::addNote(pair<NotePitch, unsigned> coords, uint8_t index)
{
	if(this->_notes.find(coords) == this->_notes.end())
	{
		this->_notes[coords] = vector<Note*>(0);
	}
	
	//These things are in seperate loops, cause of
	//option to delete note
	if (this->_notes[coords].size() == 0)
	{
		size_t newSize = static_cast<size_t>(pow(2, 5 - log2(this->_denominator)));
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

	this->_notes[coords][index] = new Note(coords.first);
	return true;
}

bool Sequence::addNoteAtCurrentPosition()
{
	auto coords = this->getCurrentNoteCoords();
	return this->addNote(coords, this->_currentNoteInBar);
}


void Sequence::setMeasure(const uint16_t& numerator, const uint16_t& denominator)
{
	this->_numerator = numerator;
	this->_denominator = denominator;
	this->_numOf32NotesInBar = static_cast<uint8_t>(pow(2, 5 - log2(this->_denominator)));
}
