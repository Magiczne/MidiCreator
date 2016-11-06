#include "MidiCreator.h"

void MidiCreator::drawMenu()
{
	Util::clearConsole();
	cout << endl << endl;
	Util::setColor(Color::Black, Color::DarkGreen);
	Util::writeCentered("MIDI Creator v0.0.4");
	cout << endl;

	Util::setColor(Color::Black, Color::Gray);
	Util::writeCentered("1. Start a new sequence");
	Util::writeCentered("2. Load a sequence");
	Util::writeCentered("3. Quit");
}

void MidiCreator::menuEventLoop()
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
			return;
		case '2':
			return;
		default:
			this->drawMenu();
		}
	} while (c != '3');
}

int MidiCreator::exec()
{
	this->drawMenu();
	this->menuEventLoop();
	
	system("pause");
	return 0;
}