#include "MidiCreator.h"
#include "EventManager.h"
#include "UI\UIManager.h"
#include "Sequence.h"

using namespace UI;

MidiCreator::MidiCreator()
{
	this->sequence = new Sequence();
	this->uiManager = new UIManager(*this->sequence);
	this->eventManager = new EventManager(this->uiManager, *this->sequence);
}

MidiCreator::~MidiCreator()
{
	delete this->eventManager;
	delete this->uiManager;
	delete this->sequence;
}

int MidiCreator::exec()
{
	this->uiManager->drawMenu();
	switch (this->eventManager->menuLoop())
	{
		case MenuEventType::NEW_SEQUENCE:
		{
			this->uiManager->drawSequenceScreen();
			this->eventManager->sequenceScreenLoop();
			break;
		}
		case MenuEventType::OPEN_SEQUENCE:
			break;
		case MenuEventType::QUIT:
			break;
	}
	
	return 0;
}