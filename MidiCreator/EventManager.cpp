#include "EventManager.h"
#include "Sequence.h"
#include "SequenceNote.h"
#include "SequenceFile.h"
#include "SMF/StandardMIDIFile.h"

using namespace UI;
using namespace SMF;
using namespace std;

EventManager::EventManager(UIManager* ui, Sequence& seq) :
	_uiManager(ui), _seq(seq) {}

MenuEventType EventManager::menuLoop()
{
	char c;

	do
	{
		c = Util::getUnbufferedKey();

		switch (c)
		{
		case 0:
			break;
		case '1':
			return NEW_SEQUENCE;
		case '2':
			return OPEN_SEQUENCE;
		default:
			break;
		}
	} while (c != '3');

	return QUIT;
}

string EventManager::readFilepathFromUser()
{
	string filepath;

	cin >> filepath;

	return filepath;
}

void EventManager::sequenceScreenLoop() const
{
	char c;

	do
	{
		c = Util::getUnbufferedKey();

		switch (c)
		{
		case 0:
			break;

		case 65:	//A
			this->handleA();
			break;

		case 66:	//B
			this->handleB();
			break;

		case 67:	//C
			this->handleC();
			break;

		case 68:	//D
			this->handleD();
			break;

		case 73:	//I
			this->handleI();
			break;

		case 76:	//L
			this->handleL();
			break;

		case 77:	//M
			this->handleM();
			break;

		case 78:	//N
			this->handleN();
			break;

		case 83:	//S
			this->handleS();
			break;

		case 84:	//T
			this->handleT();
			break;

		case 86:	//V
			this->handleV();
			break;

		case 87:	//W
			this->handleW();
			break;

		#pragma region Numbers

		case 49:	//1
		case 50:	//2
		case 51:	//3
		case 52:	//4
			if (this->_uiManager->action() == Action::CHANGE_MEASURE)
			{
				this->changeMeasure(c);
				this->_uiManager->action(Action::NONE);
				this->_uiManager->drawSequenceScreen();
			}
			break;

		#pragma endregion

		#pragma region Arrows

		case VK_LEFT:
			this->handleLeftArrow();
			break;

		case VK_UP:
			this->handleUpArrow();
			break;
			
		case VK_RIGHT:
			this->handleRightArrow();
			break;

		case VK_DOWN:
			this->handleDownArrow();
			break;

		#pragma endregion

		#pragma region Function Keys

		case VK_F5:
			this->handleF5();
			break;

		case VK_F6:
			this->handleF6();
			break;

		#pragma endregion

		default:
			break;
		}

	} while (true);
}

#pragma region Key Handlers

void EventManager::handleA() const
{
	if (this->_uiManager->mode() == EDIT)
	{
		if(this->_uiManager->action() == BAR_EDIT)
		{
			if(this->_seq.moveCloseUpIndicatorLeft())
			{
				this->_uiManager->drawSequenceScreen();
			}
		}
		else
		{
			if (this->_seq.moveIndicatorLeft())
			{
				this->_uiManager->drawSequenceScreen();
			}
		}
	}
}

void EventManager::handleB() const
{
	if (this->_uiManager->mode() == EDIT)
	{
		Action action = this->_uiManager->action() == BAR_EDIT ? NONE : BAR_EDIT;
		this->_uiManager->action(action);
		this->_uiManager->drawSequenceScreen();
	}
}

void EventManager::handleC() const
{
	if(this->_uiManager->mode() == VIEW && this->_uiManager->action() == NONE)
	{
		this->_uiManager->action(CHANGE_MIDI_CHANNEL);
		Nullable<COORD> pos = this->_uiManager->drawSequenceScreen();

		Util::setCursorPos(pos.Value);
		this->changeMidiChannel();

		this->_uiManager->action(NONE);
		this->_uiManager->drawSequenceScreen();
	}
}

void EventManager::handleD() const
{
	if (this->_uiManager->mode() == EDIT)
	{
		if(this->_uiManager->action() == BAR_EDIT)
		{
			if(this->_seq.moveCloseUpIndicatorRight())
			{
				this->_uiManager->drawSequenceScreen();
			}
		}
		else
		{
			if (this->_seq.moveIndicatorRight(this->_uiManager->pianoRollWidth))
			{
				this->_uiManager->drawSequenceScreen();
			}
		}
	}
}

void EventManager::handleI() const
{
	if (this->_uiManager->mode() == EDIT && this->_uiManager->action() == BAR_EDIT)
	{
		if(this->_seq.getCurrentNote() == nullptr)
		{
			if (this->_seq.addNoteAtCurrentPosition())
			{
				this->_uiManager->drawSequenceScreen();
			}
		}
		else
		{
			if(this->_seq.removeNoteAtCurrentPosition())
			{
				this->_uiManager->drawSequenceScreen();
			}
		}
	}
}

void EventManager::handleL() const
{
	if(
		this->_uiManager->action() == BAR_EDIT &&
		this->_uiManager->mode() == EDIT &&
		this->_seq.getCurrentNote() != nullptr)
	{
		this->toggleNoteLigature();
		this->_uiManager->drawSequenceScreen();
	}
}

void EventManager::handleM() const
{
	if (this->_uiManager->action() == NONE && this->_uiManager->mode() == VIEW)
	{
		//CRITICAL: Throws an exception when notes are in the roll. FIX
		//TODO: changing measure when notes are in the roll
		try
		{
			this->_uiManager->action(CHANGE_MEASURE);

			Nullable<COORD> pos = this->_uiManager->drawSequenceScreen();
			Util::setCursorPos(pos.Value);
		}
		catch (...){}
	}
}

void EventManager::handleN() const
{
	if (this->_uiManager->action() == NONE)
	{
		this->_uiManager->mode(this->_uiManager->mode() == EDIT ? VIEW : EDIT);
		this->_uiManager->drawSequenceScreen();
	}
}

void EventManager::handleS() const
{
	if (this->_uiManager->action() == NONE)
	{
		if(this->_uiManager->mode() == VIEW)
		{
			this->_uiManager->action(CHANGE_SEQ_NAME);
			Nullable<COORD> pos = this->_uiManager->drawSequenceScreen();

			Util::setCursorPos(pos.Value);
			this->changeSequenceName();

			this->_uiManager->action(NONE);
			this->_uiManager->drawSequenceScreen();
		}
		else
		{
			if (this->_seq.moveIndicatorDown(this->_uiManager->pianoRollHeight))
			{
				this->_uiManager->drawSequenceScreen();
			}
		}
	}
}

void EventManager::handleT() const
{
	if(this->_uiManager->action() == NONE && this->_uiManager->mode() == VIEW)
	{
		this->_uiManager->action(CHANGE_TEMPO);
		Nullable<COORD> pos = this->_uiManager->drawSequenceScreen();

		Util::setCursorPos(pos.Value);
		this->changeTempo();

		this->_uiManager->action(NONE);
		this->_uiManager->drawSequenceScreen();
	}
}

void EventManager::handleV() const
{
	if(
		this->_uiManager->action() == BAR_EDIT && 
		this->_uiManager->mode() == EDIT &&
		this->_seq.getCurrentNote() != nullptr)
	{
		this->_uiManager->action(CHANGE_NOTE_VOLUME);
		Nullable<COORD> pos = this->_uiManager->drawSequenceScreen();

		Util::setCursorPos(pos.Value);
		this->changeNoteVolume();

		this->_uiManager->action(BAR_EDIT);
		this->_uiManager->drawSequenceScreen();
	}
}

void EventManager::handleW() const
{
	if (this->_uiManager->mode() == EDIT && this->_uiManager->action() == NONE)
	{
		if (this->_seq.moveIndicatorUp())
		{
			this->_uiManager->drawSequenceScreen();
		}
	}
}

#pragma endregion

#pragma region Function Key Handlers

void EventManager::handleF5() const
{
	if (this->_uiManager->mode() == VIEW && this->_uiManager->action() == NONE)
	{
		auto seqFile = SequenceFile::fromSequence(this->_seq);
		seqFile.saveFile("magicznyplik.msq");
		this->_uiManager->lastMessage("Sequence was saved to magicznyplik.msq");
		this->_uiManager->drawSequenceScreen();
		//TODO: Ask user for filename and place
	}
}

void EventManager::handleF6() const
{
	if(this->_uiManager->mode() == VIEW && this->_uiManager->action() == NONE)
	{
		auto smf = this->_seq.toMidiFile();
		smf.exportToFile("magicznyplik.midi");
		this->_uiManager->lastMessage("Sequence was saved to magicznyplik.midi");
		this->_uiManager->drawSequenceScreen();
		//TODO: Ask user for filename and place
	}
}

#pragma endregion

#pragma region Arrow Handlers

void EventManager::handleUpArrow() const
{
	if (this->_seq.showPreviousNote())
	{
		this->_uiManager->drawSequenceScreen();
	}
}

void EventManager::handleDownArrow() const
{
	if (this->_seq.showNextNote(this->_uiManager->pianoRollHeight))
	{
		this->_uiManager->drawSequenceScreen();
	}
}

void EventManager::handleLeftArrow() const
{
	if (this->_seq.showPreviousBar())
	{
		this->_uiManager->drawSequenceScreen();
	}
}

void EventManager::handleRightArrow() const
{
	if (this->_seq.showNextBar(this->_uiManager->pianoRollWidth))
	{
		this->_uiManager->drawSequenceScreen();
	}
}

#pragma endregion

void EventManager::changeNoteVolume() const
{
	string vol;
	cin >> vol;

	if(vol != "")
	{
		try
		{
			int val = stoi(vol);
			this->_seq.getCurrentNote()->volume(val);
		}
		catch (invalid_argument const&)
		{
			this->_uiManager->lastMessage("Volume has to be a number(0-127)");
		}
	}
}

void EventManager::changeSequenceName() const
{
	string newName;
	
	getline(cin, newName);

	if (newName != "")
	{
		this->_seq.name(newName);
	}
}

void EventManager::changeMeasure(uint16_t vk) const
{
	if (vk == 49)
	{
		this->_seq.setMeasure(2, 4);
	}
	else if (vk == 50)
	{
		this->_seq.setMeasure(3, 4);
	}
	else if (vk == 51)
	{
		this->_seq.setMeasure(4, 4);
	}
	else if (vk == 52)
	{
		this->_seq.setMeasure(6, 8);
	}
}

void EventManager::toggleNoteLigature() const
{
	auto currentNote = this->_seq.getCurrentNote();
	currentNote->ligature(!currentNote->ligature());
}

void EventManager::changeMidiChannel() const
{
	string channel;
	cin >> channel;

	if(channel != "")
	{
		int val;

		try
		{
			val = stoi(channel);
		}
		catch(invalid_argument const&)
		{
			this->_uiManager->lastMessage("MIDI Channel has to be a number!");
			return;
		}

		if(val >= 1 && val <= 16)
		{
			this->_seq.currentChannel(MIDIChannel(val - 1));
		}
		else
		{
			this->_uiManager->lastMessage("MIDI Channel has to be betwwen 1 and 16");
		}
	}
}

void EventManager::changeTempo() const
{
	string tempo;
	cin >> tempo;

	if(tempo != "")
	{
		int val;

		try
		{
			val = stoi(tempo);
		}
		catch(invalid_argument const&)
		{
			this->_uiManager->lastMessage("Tempo has to be a number!");
			return;
		}

		if(val >= 1 && val <= 255)
		{
			this->_seq.tempo(val);
		}
		else
		{
			this->_uiManager->lastMessage("Tempo has to be between 1 and 255");
		}
	}
}
