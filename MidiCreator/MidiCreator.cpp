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
	try 
	{
		Util::setConsoleSize(130, 35);
	}
	catch(std::logic_error& ex)
	{
		std::cerr << ex.what() << '\n';
		return 1;
	}
	catch (std::exception& ex)
	{
		std::cerr << ex.what() << '\n';
		Util::showLastSystemError();
		return 2;
	}

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

	std::cin.get();
	return 0;
}