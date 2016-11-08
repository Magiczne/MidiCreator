#include "EventManager.h"

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

		switch (c)
		{
		case 0:
			break;

		case 37:			//Left arrow
			if (seq.previousMeasure())
			{
				this->uiManager->drawSequenceScreen(seq);
			}
			break;

		case 38:			//Up arrow
			if (seq.previousNote())
			{
				this->uiManager->drawSequenceScreen(seq);
			}
			break;

		case 39:			//Right arrow
			if (seq.nextMeasure())
			{
				this->uiManager->drawSequenceScreen(seq);
			}		
			break;

		case 40:			//Down arrow
			if (seq.nextNote())
			{
				this->uiManager->drawSequenceScreen(seq);
			}
			break;

		default:
			break;
		}
	} while (true);
}