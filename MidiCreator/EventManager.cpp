#include "EventManager.h"
#include "Sequence.h"

using namespace UI;
using namespace std;

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

void EventManager::sequenceScreenLoop(Sequence& seq)
{
	char c;

	do
	{
		c = Util::getUnbufferedKey();
		std::string a;

		switch (c)
		{
		case 0:
			break;

		case 78:	//N
			this->uiManager->mode(this->uiManager->mode() == Mode::EDIT ? Mode::VIEW : Mode::EDIT);
			this->uiManager->drawSequenceScreen(seq);
			break;

		case 83:	//S
			this->uiManager->action(Action::CHANGE_SEQ_NAME);
			this->uiManager->drawSequenceScreen(seq);
			this->changeSequenceName(seq);
			break;

		case VK_LEFT:
			if (seq.previousMeasure())
			{
				this->uiManager->drawSequenceScreen(seq);
			}
			break;

		case VK_UP:
			if (seq.previousNote())
				{
					this->uiManager->drawSequenceScreen(seq);
				}
			break;
			
		case VK_RIGHT:
			if (seq.nextMeasure(this->uiManager->pianoRollWidth))
			{
				this->uiManager->drawSequenceScreen(seq);
			}
			break;

		case VK_DOWN:
			if (seq.nextNote(this->uiManager->pianoRollHeight))
				{
					this->uiManager->drawSequenceScreen(seq);
				}
			break;

		default:
			break;
		}

	} while (true);
}

void EventManager::changeSequenceName(Sequence& seq)
{
	string newName;
	
	cin >> newName;

	seq.name(newName);
}