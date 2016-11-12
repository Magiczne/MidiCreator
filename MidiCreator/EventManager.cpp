#include "EventManager.h"
#include "Sequence.h"

using namespace UI;
using namespace std;

EventManager::EventManager(UIManager* ui, Sequence& seq) :
	uiManager(ui), seq(seq) {}

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

void EventManager::sequenceScreenLoop()
{
	char c;

	do
	{
		c = Util::getUnbufferedKey();

		switch (c)
		{
		case 0:
			break;

		case 77:	//M
		{
			this->uiManager->action(Action::CHANGE_MEASURE);

			Nullable<COORD> pos = this->uiManager->drawSequenceScreen();

			Util::setCursorPos(pos.Value);
			break;
		}

		case 78:	//N
			this->uiManager->mode(this->uiManager->mode() == Mode::EDIT ? Mode::VIEW : Mode::EDIT);
			this->uiManager->drawSequenceScreen();
			break;

		case 83:	//S
		{
			this->uiManager->action(Action::CHANGE_SEQ_NAME);

			Nullable<COORD> pos = this->uiManager->drawSequenceScreen();

			Util::setCursorPos(pos.Value);
			this->changeSequenceName();

			this->uiManager->action(Action::NONE);
			this->uiManager->drawSequenceScreen();
			break;
		}

		#pragma region Numbers

		case 49:	//1
		case 50:	//2
		case 51:	//3
		case 52:	//4
			if (this->uiManager->action() == Action::CHANGE_MEASURE)
			{
				this->changeMeasure(c);
				this->uiManager->action(Action::NONE);
				this->uiManager->drawSequenceScreen();
			}
			break;

		#pragma endregion

		#pragma region Arrows

		case VK_LEFT:
			if (this->seq.previousMeasure())
			{
				this->uiManager->drawSequenceScreen();
			}
			break;

		case VK_UP:
			if (this->seq.previousNote())
				{
					this->uiManager->drawSequenceScreen();
				}
			break;
			
		case VK_RIGHT:
			if (this->seq.nextMeasure(this->uiManager->pianoRollWidth))
			{
				this->uiManager->drawSequenceScreen();
			}
			break;

		case VK_DOWN:
			if (this->seq.nextNote(this->uiManager->pianoRollHeight))
				{
					this->uiManager->drawSequenceScreen();
				}
			break;

		#pragma endregion

		default:
			break;
		}

	} while (true);
}

void EventManager::changeSequenceName()
{
	string newName;
	
	getline(cin, newName);

	if (newName != "")
	{
		this->seq.name(newName);
	}
}

void EventManager::changeMeasure(uint16_t vk)
{
	if (vk == 49)
	{
		this->seq.setMeasure(2, 4);
	}
	else if (vk == 50)
	{
		this->seq.setMeasure(3, 4);
	}
	else if (vk == 51)
	{
		this->seq.setMeasure(4, 4);
	}
	else if (vk == 52)
	{
		this->seq.setMeasure(6, 8);
	}
}