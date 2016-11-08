#include "UIManager.h"

using namespace UI;

void UIManager::drawMenu()
{
	Util::clearConsole();
	cout << endl << endl;
	Util::setColor(Color::DarkGreen);
	Util::writeCentered("MIDI Creator v0.0.41");
	cout << endl;

	Util::setColor(Color::Gray);
	Util::writeCentered("1. Start a new sequence");
	Util::writeCentered("2. Load a sequence");
	Util::writeCentered("3. Quit");
}

void UIManager::drawSequenceScreen(Sequence& seq)
{
	ConsoleSize size = Util::getConsoleSize();
	const int pianoRollWidth = size.cols - 20;

	Util::clearConsole();

	//Sequence title + Sequence Type
	Util::setColor(Color::DarkGreen);
	Util::writeMulti(
		seq.name, seq.getFormat(), 
		Util::createColor(Color::DarkCyan)
	);
	
	//Measure
	Util::setColor(Color::DarkBlue);
	Util::writeRight("Measure: " +
		to_string(seq.numerator) + "/" 
		+ to_string(seq.denominator));
	cout << endl << endl;

	
	//Bars numbers
	Util::setColor(Color::Red);
	cout << "    ";
	for (int i = 0 + seq.currentMeasure;
		i < pianoRollWidth / seq.numerator + seq.currentMeasure;
		i++)
	{
		cout << i;

		for (int j = 0;
			j < seq.numerator - Util::getNumberOfDigits(i);
			j++)
		{
			cout << ' ';
		}
	}
	cout << endl;

	cout << "    ";
	Util::makeLine(pianoRollWidth, 
		Util::createColor(Color::DarkRed));

	for (int k = 0; k < 10; k++)
	{
		Util::setColor(Color::Red);
		NotePitch p = NotePitch((uint8_t)seq.firstNoteToShow + k);
		string text = SMF::NotePitchMap[p];
		cout << text;

		for (int i = 0; i < 4 - text.size(); i++)
		{
			cout << ' ';
		}

		for (int i = 0;
			i < pianoRollWidth / seq.numerator * seq.numerator; i++)
		{
			

			if (i % seq.numerator == 0)
			{
				Util::setColor(Color::DarkRed);
				cout << '|';
			}
			else
			{
				Util::setColor(Color::DarkGray);
				cout << '*';
			}
		}

		cout << endl;
	}
	cout << endl;
	cout << endl;
}