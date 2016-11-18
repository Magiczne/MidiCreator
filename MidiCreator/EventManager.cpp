#include "EventManager.h"
#include "Sequence.h"
#include "Note.h"
#include "SMF/Enums/NotePitch.h"

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
			return MenuEventType::NEW_SEQUENCE;
		case '2':
			return MenuEventType::OPEN_SEQUENCE;
		default:
			break;
		}
	} while (c != '3');

	return MenuEventType::QUIT;
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
			this->handleKeyA();
			break;

		case 66:	//B
			this->handleKeyB();
			break;

		case 67:	//C
			this->handleKeyC();
			break;

		case 68:	//D
			this->handleKeyD();
			break;

		case 73:	//I
			this->handleKeyI();
			break;

		case 76:	//L
			this->handleKeyL();
			break;

		case 77:	//M
			this->handleKeyM();
			break;

		case 78:	//N
			this->handleKeyN();
			break;

		case 83:	//S
			this->handleKeyS();
			break;

		case 86:	//V
			this->handleKeyV();
			break;

		case 87:	//W
			this->handleKeyW();
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

		default:
			break;
		}

	} while (true);
}

#pragma region Key Handlers

void EventManager::handleKeyA() const
{
	if (this->_uiManager->mode() == Mode::EDIT)
	{
		if(this->_uiManager->action() == Action::BAR_EDIT)
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

void EventManager::handleKeyB() const
{
	if (this->_uiManager->mode() == Mode::EDIT)
	{
		Action action = this->_uiManager->action() == Action::BAR_EDIT ? Action::NONE : Action::BAR_EDIT;
		this->_uiManager->action(action);
		this->_uiManager->drawSequenceScreen();
	}
}

void EventManager::handleKeyC() const
{
	if(this->_uiManager->mode() == Mode::VIEW && this->_uiManager->action() == Action::NONE)
	{
		this->_uiManager->action(Action::CHANGE_MIDI_CHANNEL);
		Nullable<COORD> pos = this->_uiManager->drawSequenceScreen();

		Util::setCursorPos(pos.Value);
		this->changeMidiChannel();

		this->_uiManager->action(Action::NONE);
		this->_uiManager->drawSequenceScreen();
	}
}

void EventManager::handleKeyD() const
{
	if (this->_uiManager->mode() == Mode::EDIT)
	{
		if(this->_uiManager->action() == Action::BAR_EDIT)
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

void EventManager::handleKeyI() const
{
	if (this->_uiManager->mode() == Mode::EDIT && this->_uiManager->action() == Action::BAR_EDIT)
	{
		if (this->_seq.addNoteAtCurrentPosition())
		{
			this->_uiManager->drawSequenceScreen();
		}
	}
}

void EventManager::handleKeyL() const
{
	if(
		this->_uiManager->action() == Action::BAR_EDIT &&
		this->_uiManager->mode() == Mode::EDIT &&
		this->_seq.getCurrentNote()  != nullptr)
	{
		this->toggleNoteLigature();
		this->_uiManager->drawSequenceScreen();
	}
}

void EventManager::handleKeyM() const
{
	if (this->_uiManager->action() == Action::NONE && this->_uiManager->mode() == Mode::VIEW)
	{
		//CRITICAL: Throws an exception when notes are in the roll. FIX
		//TODO: changing measure when notes are in the roll
		try
		{
			this->_uiManager->action(Action::CHANGE_MEASURE);

			Nullable<COORD> pos = this->_uiManager->drawSequenceScreen();
			Util::setCursorPos(pos.Value);
		}
		catch (...){}
	}
}

void EventManager::handleKeyN() const
{
	if (this->_uiManager->action() == Action::NONE)
	{
		this->_uiManager->mode(this->_uiManager->mode() == Mode::EDIT ? Mode::VIEW : Mode::EDIT);
		this->_uiManager->drawSequenceScreen();
	}
}

void EventManager::handleKeyS() const
{
	if (this->_uiManager->action() == Action::NONE && this->_uiManager->mode() == Mode::VIEW)
	{
		this->_uiManager->action(Action::CHANGE_SEQ_NAME);
		Nullable<COORD> pos = this->_uiManager->drawSequenceScreen();

		Util::setCursorPos(pos.Value);
		this->changeSequenceName();

		this->_uiManager->action(Action::NONE);
		this->_uiManager->drawSequenceScreen();
	}
	else if(this->_uiManager->action() == Action::NONE && this->_uiManager->mode() == Mode::EDIT)
	{
		if (this->_seq.moveIndicatorDown(this->_uiManager->pianoRollHeight))
		{
			this->_uiManager->drawSequenceScreen();
		}
	}
}

void EventManager::handleKeyV() const
{
	//TODO: Check if note is present
	if(
		this->_uiManager->action() == Action::BAR_EDIT && 
		this->_uiManager->mode() == Mode::EDIT &&
		this->_seq.getCurrentNote() != nullptr)
	{
		this->_uiManager->action(Action::CHANGE_NOTE_VOLUME);
		Nullable<COORD> pos = this->_uiManager->drawSequenceScreen();

		Util::setCursorPos(pos.Value);
		this->changeNoteVolume();

		this->_uiManager->action(Action::BAR_EDIT);
		this->_uiManager->drawSequenceScreen();
	}
}

void EventManager::handleKeyW() const
{
	if (this->_uiManager->mode() == Mode::EDIT && this->_uiManager->action() == Action::NONE)
	{
		if (this->_seq.moveIndicatorUp())
		{
			this->_uiManager->drawSequenceScreen();
		}
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
	if (this->_seq.showPreviousMeasure())
	{
		this->_uiManager->drawSequenceScreen();
	}
}

void EventManager::handleRightArrow() const
{
	if (this->_seq.showNextMeasure(this->_uiManager->pianoRollWidth))
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
		catch (invalid_argument)
		{
			//TODO: Some error message
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
		catch(invalid_argument)
		{
			//TODO: Some error message
			return;
		}

		if(val >= 1 && val <= 16)
		{
			this->_seq.currentChannel(MIDIChannel(val - 1));
		}
		else
		{
			//TODO: Some error message
		}
	}
}