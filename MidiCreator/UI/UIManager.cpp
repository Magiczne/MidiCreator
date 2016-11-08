#include "UIManager.h"

using namespace UI;

void UIManager::drawMenu()
{
	Util::clearConsole();
	cout << endl << endl;
	Util::setColor(Color::Black, Color::DarkGreen);
	Util::writeCentered("MIDI Creator v0.0.41");
	cout << endl;

	Util::setColor(Color::Black, Color::Gray);
	Util::writeCentered("1. Start a new sequence");
	Util::writeCentered("2. Load a sequence");
	Util::writeCentered("3. Quit");
}

void UIManager::drawSequenceScreen(Sequence& seq)
{
	Util::clearConsole();

	//Sequence title + Sequence Type
	Util::setColor(Color::Black, Color::DarkGreen);
	Util::writeMulti(seq.name, seq.getFormat());
	Util::setColor(Color::Black, Color::White);
}