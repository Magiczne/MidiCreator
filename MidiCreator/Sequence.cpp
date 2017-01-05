#include "Sequence.h"

#include "Note.h"
#include "SequenceFile.h"

#include "SMF/StandardMIDIFile.h"
#include "SMF/HeaderChunk.h"

using namespace SMF;
using namespace std;

Sequence::Sequence()
{
	this->_name = "New sequence";
	this->_format = FileFormat::SINGLE_TRACK;
	this->setMeasure(6, 8);

	this->_firstBarToShow = 1;
	this->_firstNoteToShow = NotePitch::C3;

	this->_currentChannel = MIDIChannel::CHANNEL_1;
	this->_currentBar = 0;
	this->_currentNotePitch = 0;
	this->_currentNoteInBar = 0;

	for(auto& map : this->_notes)
	{
		map.clear();
	}
}

Sequence::~Sequence()
{
	for (const auto& map : _notes)
	{
		for (const auto& pair : map)
		{
			for (auto& note : pair.second)
			{
				delete note;
			}
		}
	}
}

void Sequence::loadFromFile(const SequenceFile& file)
{
	this->name(file.name);
	this->format(static_cast<FileFormat>(file.fileFormat));
	this->numerator(file.numerator);
	this->denominator(file.denominator);

	if(this->hasNotes())
	{
		for (auto& map : this->_notes)
		{
			map.clear();
		}
	}

	for(const auto& note : file.notesData)
	{
		this->currentChannel(static_cast<MIDIChannel>(note.channel));
		this->addNote(
			{ static_cast<NotePitch>(note.notePitch), note.barNumber },
			note.barPosition,
			note.noteVolume,
			note.noteDuration,
			note.noteLigature == 0x00 ? false : true
		);
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
	if (this->_firstBarToShow < Sequence::MAX_BAR - (pianoRollWidth / this->_numerator) + 1)
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
	return this->_notes[static_cast<uint8_t>(this->_currentChannel)][coords];
}

#pragma region Note manipulation

Note* Sequence::getNote(pair<NotePitch, unsigned> coords, uint8_t index)
{
	uint8_t channel = static_cast<uint8_t>(this->_currentChannel);

	if (this->_notes[channel].find(coords) == this->_notes[channel].end())
	{
		return nullptr;
	}

	if (this->_notes[channel][coords].size() == 0)
	{
		return nullptr;
	}

	return this->_notes[channel][coords][index];
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

bool Sequence::isNotePositionEmpty(const std::pair<SMF::NotePitch, unsigned>& coords, const uint8_t index, const uint8_t channel)
{
	if (this->_notes[channel].find(coords) == this->_notes[channel].end())
	{
		this->_notes[channel][coords] = vector<Note*>(0);
	}

	//These things are in seperate loops, cause of
	//option to delete note
	if (this->_notes[channel][coords].size() == 0)
	{
		size_t newSize = static_cast<size_t>(pow(2, 5 - log2(this->_denominator)));
		this->_notes[channel][coords].resize(newSize);

		for (auto& a : this->_notes[channel][coords])
		{
			a = nullptr;
		}
	}

	if (this->_notes[channel][coords][index] != nullptr)
	{
		return false;
	}

	return true;
}

bool Sequence::addNote(std::pair<SMF::NotePitch, unsigned> coords, uint8_t index, uint8_t volume, uint16_t duration, bool ligature)
{
	uint8_t channel = static_cast<uint8_t>(this->_currentChannel);

	auto res = isNotePositionEmpty(coords, index, channel);

	if(res)
	{
		this->_notes[channel][coords][index] = new Note(coords.first, volume, duration, ligature);
		return true;
	}

	return res;
}

bool Sequence::addNote(pair<NotePitch, unsigned> coords, uint8_t index)
{
	uint8_t channel = static_cast<uint8_t>(this->_currentChannel);

	auto res = isNotePositionEmpty(coords, index, channel);

	if (res)
	{
		this->_notes[channel][coords][index] = new Note(coords.first);
		return true;
	}

	return res;
}

bool Sequence::addNoteAtCurrentPosition()
{
	auto coords = this->getCurrentNoteCoords();
	return this->addNote(coords, this->_currentNoteInBar);
}

bool Sequence::removeNote(pair<NotePitch, unsigned> coords, uint8_t index)
{
	uint8_t channel = static_cast<uint8_t>(this->_currentChannel);

	if(this->_notes[channel].find(coords) == this->_notes[channel].end())
	{
		return false;
	}

	if(this->_notes[channel][coords][index] == nullptr)
	{
		return false;
	}

	delete this->_notes[channel][coords][index];
	this->_notes[channel][coords][index] = nullptr;
	return true;
}

bool Sequence::removeNoteAtCurrentPosition()
{
	auto coords = this->getCurrentNoteCoords();
	return this->removeNote(coords, this->_currentNoteInBar);
}

#pragma endregion

void Sequence::setMeasure(const uint16_t& numerator, const uint16_t& denominator)
{
	this->_numerator = numerator;
	this->_denominator = denominator;
	this->_numOf32NotesInBar = static_cast<uint8_t>(pow(2, 5 - log2(this->_denominator)));
}

bool Sequence::hasMultipleTracks()
{
	int trackCounter = 0;
	for(const auto& map : this->_notes)
	{
		for(const auto& pair : map)
		{
			for(const auto& ptr : pair.second)
			{
				if(ptr != nullptr)
				{
					trackCounter++;
				}
			}
		}

		if(trackCounter > 1)
		{
			return true;
		}
	}

	return false;
}


StandardMIDIFile Sequence::toMidiFile()
{
	StandardMIDIFile smf;
	smf.setHeader(this->hasMultipleTracks() ? FileFormat::MULTIPLE_TRACK : FileFormat::SINGLE_TRACK);
	//TODO: Set tempo
	smf.setTimeSignature(this->numerator(), this->denominator());

	return smf;
}
