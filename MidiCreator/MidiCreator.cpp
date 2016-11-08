#include "MidiCreator.h"
#include "Sequence.h"

MidiCreator::MidiCreator()
{
	this->uiManager = new UIManager();
	this->eventManager = new EventManager(this->uiManager);
}

MidiCreator::~MidiCreator()
{
	delete this->eventManager;
	delete this->uiManager;
}

int MidiCreator::exec()
{
	this->uiManager->drawMenu();
	switch (this->eventManager->menuLoop())
	{
		case MenuEventType::NEW_SEQUENCE:
		{
			Sequence seq;
			this->uiManager->drawSequenceScreen(seq);
			this->eventManager->sequenceScreenLoop(seq);
			break;
		}
		case MenuEventType::OPEN_SEQUENCE:
			break;
		case MenuEventType::QUIT:
			break;
	}
	
	system("pause");
	return 0;
}