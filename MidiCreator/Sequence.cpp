#include "Sequence.h"

#include "SequenceNote.h"
#include "SequenceFile.h"

#include "SMF/StandardMIDIFile.h"
#include "SMF/HeaderChunk.h"
#include "SMF/Exceptions/NoTracksException.h"

using namespace SMF;
using namespace SMF::Exceptions;
using namespace std;

Sequence::Sequence()
{
	this->name("New Sequence");
	this->format(FileFormat::SINGLE_TRACK);
	this->tempo(130);
	this->setMeasure(6, 8);

	this->_firstBarToShow = 1;
	this->_firstPitchToShow = NotePitch::C3;

	this->_currentChannel = MIDIChannel::CHANNEL_1;
	this->_currentNote = 0;
	this->_currentNotePitch = 0;
	this->_current32NoteInBar = 0;

	for(uint8_t i = 0; i < 16; i++)
	{
		_channelPatches[static_cast<MIDIChannel>(i)] = GMPatch::ACOUSTIC_GRAND_PIANO;
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

bool Sequence::showPreviousBar()
{
	if (this->_firstBarToShow > 1)
	{
		this->_firstBarToShow--;
		return true;
	}

	return false;
}

bool Sequence::showNextBar(uint16_t pianoRollWidth)
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
	if (this->_firstPitchToShow > NotePitch::C_MINUS_1)
	{
		this->_firstPitchToShow = NotePitch(static_cast<uint8_t>(this->_firstPitchToShow) - 1);
		return true;
	}

	return false;
}

bool Sequence::showNextNote(uint16_t pianoRollHeight)
{
	if (static_cast<uint8_t>(this->_firstPitchToShow) < static_cast<uint8_t>(NotePitch::G9) - pianoRollHeight + 1)
	{
		this->_firstPitchToShow = NotePitch(static_cast<uint8_t>(this->_firstPitchToShow) + 1);
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
	if (this->_currentNote > 0)
	{
		this->_currentNote--;
		return true;
	}

	return false;
}

bool Sequence::moveIndicatorRight(uint16_t pianoRollWidth)
{
	if (this->_currentNote < pianoRollWidth - 1U)
	{
		this->_currentNote++;
		return true;
	}

	return false;
}

bool Sequence::moveCloseUpIndicatorLeft()
{
	if(this->_current32NoteInBar > 0)
	{
		this->_current32NoteInBar--;
		return true;
	}

	return false;
}

bool Sequence::moveCloseUpIndicatorRight()
{
	if(this->_current32NoteInBar < this->_numOf32NotesInBar -1)
	{
		this->_current32NoteInBar++;
		return true;
	}

	return false;
}

vector<shared_ptr<SequenceNote>>& Sequence::getBar(PianoRollCoords coords)
{
	return this->_notes[static_cast<uint8_t>(this->_currentChannel)][coords];
}

#pragma region Note manipulation

shared_ptr<SequenceNote> Sequence::getNote(PianoRollCoords coords, uint8_t index)
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

shared_ptr<SequenceNote> Sequence::getCurrentNote()
{
	return this->getNote(this->getCurrentNoteCoords(), this->_current32NoteInBar);
}

PianoRollCoords Sequence::getCurrentNoteCoords() const
{
	uint8_t pitch = static_cast<uint8_t>(this->_firstPitchToShow) + this->_currentNotePitch;
	unsigned note = (this->_firstBarToShow - 1) * this->_numerator + this->_currentNote;

	return { NotePitch(pitch), note };
}

bool Sequence::isNotePositionEmpty(const PianoRollCoords& coords, const uint8_t index, const uint8_t channel)
{
	//Theoretically can happen
	if (this->_notes[channel].find(coords) == this->_notes[channel].end())
	{
		this->_notes[channel][coords] = vector<shared_ptr<SequenceNote>>(0);
	}

	//No bar position data found in map. We need to create empty vector of notes
	//To represent that bar position, and fill them with nullptrs
	//Size is that many 32nd notes that can be held by denominator
	if (this->_notes[channel][coords].size() == 0)
	{
		size_t newSize = static_cast<size_t>(pow(2, 5 - log2(this->_denominator)));
		this->_notes[channel][coords].resize(newSize, nullptr);

		return true;
	}
	
	if (this->_notes[channel][coords][index] != nullptr)
	{
		return false;
	}

	return true;
}

bool Sequence::addNote(PianoRollCoords coords, uint8_t index, uint8_t volume, uint16_t duration, bool ligature)
{
	uint8_t channel = static_cast<uint8_t>(this->_currentChannel);

	auto res = isNotePositionEmpty(coords, index, channel);

	if(res)
	{
		this->_notes[channel][coords][index] = make_shared<SequenceNote>(coords.pitch(), volume, duration, ligature);
		return true;
	}

	return res;
}

bool Sequence::addNote(PianoRollCoords coords, uint8_t index)
{
	uint8_t channel = static_cast<uint8_t>(this->_currentChannel);

	auto res = isNotePositionEmpty(coords, index, channel);

	if (res)
	{
		this->_notes[channel][coords][index] = make_shared<SequenceNote>(coords.pitch());
		return true;
	}

	return res;
}

bool Sequence::addNoteAtCurrentPosition()
{
	auto coords = this->getCurrentNoteCoords();
	auto ret = this->addNote(coords, this->_current32NoteInBar);
	return ret;
}

bool Sequence::removeNote(PianoRollCoords coords, uint8_t index)
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

	this->_notes[channel][coords][index] = nullptr;
	return true;
}

bool Sequence::removeNoteAtCurrentPosition()
{
	auto coords = this->getCurrentNoteCoords();
	return this->removeNote(coords, this->_current32NoteInBar);
}

#pragma endregion

void Sequence::setMeasure(const uint16_t numerator, const uint16_t denominator)
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
				if (ptr != nullptr)
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
	bool multipleTracks = this->hasMultipleTracks();
	StandardMIDIFile smf;
	//HeaderChunk
	smf.setHeader(multipleTracks ? FileFormat::MULTIPLE_TRACK : FileFormat::SINGLE_TRACK);
	UI::Util::debug(multipleTracks ? "MULT\n" : "SING\n");
	try
	{
		smf.setTimeSignature(this->numerator(), this->denominator());
		smf.setTempo(this->tempo());
	}
	catch(NoTracksException)
	{
		smf.addTrack();
		smf.setTimeSignature(this->numerator(), this->denominator());
		smf.setTempo(this->tempo());
	}

	size_t repetitions = multipleTracks ? 16 : 1;
	for(size_t i = 0; i < repetitions; i++)
	{
		UI::Util::debug("Track " + to_string(i) + "\n");

		smf.setCurrentTrack(i + 1);

		//system("cls");

		for(const auto& pair : this->_notes[i])
		{
			//cout << "this->_notes[" << i << "][" << NotePitchMap[pair.first.pitch()] << ", " << pair.first.notePosition() << "]";

			for(size_t j = 0; j < pair.second.size(); j++)
			{
				//CRITICAL: Currently without support for ligatures(only 32nds), or even pauses XD

				//cout << "[" << j << "]";

				if(pair.second[j] != nullptr)
				{
					smf.addNote(
						pair.second[j]->pitch(),
						pair.second[j]->volume(),
						pair.second[j]->duration() * smf.get32NoteDuration()
					);
					//cout << " -> Data present ";
				}

				//cout << endl;
			}

			//system("pause");
		}
	}

	return smf;
}