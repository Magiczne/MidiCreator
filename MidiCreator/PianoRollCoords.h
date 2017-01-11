#pragma once

#include "SMF/Enums/NotePitch.h"

class PianoRollCoords
{
private:
	SMF::NotePitch _pitch;
	unsigned _nominalNotePosition;

public:
	PianoRollCoords(SMF::NotePitch p, unsigned n);
	PianoRollCoords(uint8_t p, unsigned n);

	void pitch(const SMF::NotePitch& val) { this->_pitch = val; }
	const SMF::NotePitch& pitch() const { return this->_pitch; }

	void notePosition(const unsigned val) { this->_nominalNotePosition = val; }
	unsigned notePosition() const { return this->_nominalNotePosition; }
};

bool operator<(const PianoRollCoords& lhs, const PianoRollCoords& rhs);
bool operator==(const PianoRollCoords& lhs, const PianoRollCoords& rhs);