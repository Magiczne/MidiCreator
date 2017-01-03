#include "MidiCreator.h"
#include "EventManager.h"
#include "UI/UIManager.h"
#include "Sequence.h"
#include "SequenceFile.h"
#include "Exceptions/SequenceFileException.h"

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

int MidiCreator::exec() const
{
	try 
	{
		Util::setConsoleSize(130, 35);
	}
	catch(std::logic_error const& ex)
	{
		std::cerr << ex.what() << '\n';
		return 1;
	}
	catch (std::exception const& ex)
	{
		std::cerr << ex.what() << '\n';
		Util::showLastSystemError();
		return 2;
	}

	this->uiManager->drawMenu();
	switch (EventManager::menuLoop())
	{
		case NEW_SEQUENCE:
			this->uiManager->drawSequenceScreen();
			this->eventManager->sequenceScreenLoop();
			break;

		case OPEN_SEQUENCE:
		{
			this->uiManager->drawOpenFileScreen();
			auto filepath = EventManager::readFilepathFromUser();

			try
			{
				auto file = SequenceFile::open(filepath);
				this->sequence->loadFromFile(file);
			}
			catch(std::ios_base::failure const&)
			{
				//TODO: File does not exists
				throw;
			}
			catch(Exceptions::SequenceFileException const& e)
			{
				//TODO: Error with sequence file
				throw e;
			}
			catch (...)
			{
				throw;
				//TODO: Other errors, probably just throw
			}

			this->uiManager->drawSequenceScreen();
			this->eventManager->sequenceScreenLoop();

			break;
		}

		case QUIT:
			break;

		default: 
			break;
	}

	return 0;
}