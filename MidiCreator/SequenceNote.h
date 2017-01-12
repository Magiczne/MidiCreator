#pragma once

#include "SMF/Enums/NotePitch.h"

class SequenceNote
{
	friend class SequenceFile;

private:

	SMF::NotePitch _pitch;
	uint8_t _volume;
	uint16_t _duration;
	bool _ligature = false;

public:
	static const uint8_t MAX_VOLUME = 127;

	explicit SequenceNote(SMF::NotePitch pitch);
	SequenceNote(SMF::NotePitch pitch, uint16_t duration);
	SequenceNote(SMF::NotePitch pitch, uint8_t volume, uint16_t duration);
	SequenceNote(SMF::NotePitch pitch, uint8_t volume, uint16_t duration, bool ligature);

	//Getters/setters

	void pitch(const SMF::NotePitch& val) { this->_pitch = val; }
	const SMF::NotePitch& pitch() const { return this->_pitch; }

	void volume(const uint8_t val);
	uint8_t volume() const { return this->_volume; }

	void duration(const uint16_t val) { this->_duration = val; }
	uint16_t duration() const { return this->_duration; }

	void ligature(const bool val) { this->_ligature = val; }
	bool ligature() const { return this->_ligature; }

	std::string ligatureToString() const { return this->_ligature ? "Yes" : "No"; }
};