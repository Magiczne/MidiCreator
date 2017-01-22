#include "MidiCreator.h"
#include "EventManager.h"
#include "UI/UIManager.h"
#include "Sequence.h"
#include "SequenceFile.h"
#include "Exceptions/SequenceFileException.h"

using namespace UI;

MidiCreator::MidiCreator() :
	_sequence(), _uiManager(this->_sequence), _eventManager(this->_uiManager, this->_sequence)
{}

int MidiCreator::exec()
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

	this->_uiManager.drawMenu();
	switch (EventManager::menuLoop())
	{
		case NEW_SEQUENCE:
		{
			this->_uiManager.drawSequenceScreen();
			this->_eventManager.sequenceScreenLoop();
			break;
		}

		case OPEN_SEQUENCE:
		{
			this->_uiManager.drawOpenFileScreen();
			auto filepath = EventManager::readFilepathFromUser();

			try
			{
				auto file = SequenceFile::open(filepath);
				this->_sequence.loadFromFile(file);
			}
			catch(std::ios_base::failure const&)
			{
				Util::writeLeft("File does not exists. Press any key to quit");
				std::cin.get();
				return 3;
			}
			catch(Exceptions::SequenceFileException const& ex)
			{
				Util::writeLeft(std::string(ex.what()) + "Press any key to quit");
				std::cin.get();
				return 4;
			}
			catch (std::logic_error const& ex)
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

			this->_uiManager.drawSequenceScreen();
			this->_eventManager.sequenceScreenLoop();

			break;
		}

		case QUIT:
			break;

		default: 
			break;
	}

	return 0;
}