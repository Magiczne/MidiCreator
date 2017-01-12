#include "MidiCreator.h"
#include "EventManager.h"
#include "UI/UIManager.h"
#include "Sequence.h"
#include "SequenceFile.h"
#include "Exceptions/SequenceFileException.h"

using namespace UI;

MidiCreator::MidiCreator()
{
	this->_sequence = new Sequence();
	this->_uiManager = new UIManager(*this->_sequence);
	this->_eventManager = new EventManager(this->_uiManager, *this->_sequence);
}

MidiCreator::~MidiCreator()
{
	delete this->_eventManager;
	delete this->_uiManager;
	delete this->_sequence;
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

	this->_uiManager->drawMenu();
	switch (EventManager::menuLoop())
	{
		case NEW_SEQUENCE:
			this->_uiManager->drawSequenceScreen();
			this->_eventManager->sequenceScreenLoop();
			break;

		case OPEN_SEQUENCE:
		{
			this->_uiManager->drawOpenFileScreen();
			auto filepath = EventManager::readFilepathFromUser();

			try
			{
				auto file = SequenceFile::open(filepath);
				this->_sequence->loadFromFile(file);
			}
			catch(std::ios_base::failure const&)
			{
				//TODO: File does not exists
				throw;
			}
			catch(Exceptions::SequenceFileException const&)
			{
				//TODO: Error with sequence file
				throw;
			}
			catch (...)
			{
				throw;
				//TODO: Other errors, probably just throw
			}

			this->_uiManager->drawSequenceScreen();
			this->_eventManager->sequenceScreenLoop();

			break;
		}

		case QUIT:
			break;

		default: 
			break;
	}

	return 0;
}