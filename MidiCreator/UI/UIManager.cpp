﻿#include "UIManager.h"

#include "..\Sequence.h"
#include "Util\Maps.h"

using namespace std;
using namespace SMF;
using namespace UI;

//Forward declarations
int Util::writtenLines;

void UIManager::drawMenu()
{
	Util::clearConsole();
	Util::newLine(2);
	Util::setColor(Color::DarkGreen);
	Util::writeCentered("MIDI Creator v0.0.41");
	Util::newLine();

	Util::setColor(Color::Gray);
	Util::writeCentered("1. Start a new sequence");
	Util::writeCentered("2. Load a sequence");
	Util::writeCentered("3. Quit");
}

void UIManager::drawSequenceScreen(Sequence& seq)
{
	ConsoleSize size = Util::getConsoleSize();

	this->pianoRollWidth = size.cols - 20;

	Util::clearConsole();

	//Sequence title + Sequence Type
	Util::setColor(Color::DarkGreen);
	Util::writeMulti(
		seq.name(), seq.getFormat(), 
		Util::createColor(Color::DarkCyan)
	);
	
	//Measure
	Util::setColor(Color::DarkCyan);
	Util::writeMulti(
		"Mode: " + ModeMap[this->_mode],
		"Measure: " + to_string(seq.numerator()) + "/" + to_string(seq.denominator())
	);
	Util::newLine(2);

	//Bars numbers
	Util::setColor(Color::Red);
	cout << "    ";
	for (unsigned i = 0 + seq.currentMeasure;
		i < this->pianoRollWidth / seq.numerator() + seq.currentMeasure;
		i++)
	{
		cout << i;

		for (int j = 0;
			j < seq.numerator() - Util::getNumberOfDigits(i);
			j++)
		{
			cout << ' ';
		}
	}
	Util::newLine();

	cout << "    ";
	Util::makeLine(this->pianoRollWidth,
		Util::createColor(Color::DarkRed));

	for (unsigned k = 0; k < this->pianoRollHeight; k++)
	{
		Util::setColor(Color::Red);
		NotePitch p = NotePitch((uint8_t)seq.firstNoteToShow + k);
		string text = SMF::NotePitchMap[p];
		cout << text;

		for (size_t i = 0; i < 4 - text.size(); i++)
		{
			cout << ' ';
		}

		for (unsigned i = 0;
			i < this->pianoRollWidth / seq.numerator() * seq.numerator(); i++)
		{
			if (i % seq.numerator() == 0)
			{
				Util::setColor(Color::DarkGreen);
			}
			else
			{
				Util::setColor(Color::DarkGray);
			}

			cout << '*';
		}
		Util::newLine();
	}
	Util::newLine();

	if (this->_action == Action::CHANGE_SEQ_NAME)
	{
		this->drawSequenceNameEditor(size, seq);
	}

	if (this->_mode == Mode::VIEW)
	{
		this->drawViewMenu(size);
	}
	else
	{
		this->drawEditMenu(size);
	}
}

void UIManager::drawViewMenu(ConsoleSize& size)
{
	Util::newLine(size.rows - Util::writtenLines - 2);

	vector<string> cmds = { 
		"UP", "DN", "LT", "RT", 
		" N", " S" };
	vector<string> names = { 
		"Roll up", "Roll down", "Roll left", "Roll right", 
		"Edit mode", "Seq name" };

	for (size_t i = 0; i < names.size(); i++)
	{
		Util::setColor(Color::Black, Color::Gray);
		cout << cmds[i];
		Util::setColor(Color::DarkGray);
		cout << ' ' << names[i] << '\t';
	}
}

void UIManager::drawEditMenu(ConsoleSize& size)
{
	Util::newLine(size.rows - Util::writtenLines - 2);

	vector<string> cmds = { 
		"UP", "DN", "LT", "RT", 
		" N", " S" };
	vector<string> names = { 
		"Roll up", "Roll down", "Roll left", "Roll right", 
		"View mode", "Seq name" };

	for (size_t i = 0; i < names.size(); i++)
	{
		Util::setColor(Color::Black, Color::Gray);
		cout << cmds[i];
		Util::setColor(Color::DarkGray);
		cout << ' ' << names[i] << '\t';
	}
}

void UIManager::drawSequenceNameEditor(ConsoleSize& size, Sequence& seq)
{
	int tmp = Util::writtenLines;

	Util::setColor(Color::DarkRed, Color::Gray);
	Util::makeLine(size.cols);

	Util::setColor(Color::Red);
	Util::writeLeft("Enter new sequence name: (" + seq.name() + ")");
	Util::newLine();

	Util::setColor(Color::DarkRed, Color::Gray);
	Util::makeLine(size.cols);

	Util::setCursorPos(0, tmp + 2);
}