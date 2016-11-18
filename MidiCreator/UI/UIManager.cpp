#include "UIManager.h"

#include "../Sequence.h"
#include "Util/Maps.h"
#include "../Note.h"

using namespace std;
using namespace SMF;
using namespace UI;

//Forward declarations
int Util::writtenLines;

UIManager::UIManager(Sequence& seq) : _seq(seq) {}

void UIManager::drawMenu() const
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

Nullable<COORD> UIManager::drawSequenceScreen()
{
	Nullable<COORD> ret;

	this->_size = Util::getConsoleSize();
	this->pianoRollWidth = this->_size.cols - PIANO_ROLL_MARGIN;

	Util::clearConsole();

	uint8_t infoOffset = this->drawSequenceInfo();

	this->drawPianoRoll();

	if(this->_mode == Mode::EDIT)
	{
		this->drawBarCloseUp();
	}

	//Param Editor
	switch (this->_action)
	{
	case Action::CHANGE_SEQ_NAME:
		ret = COORD{ 0, this->drawParamEditor("Enter sequence name:") };
		break;

	case Action::CHANGE_MEASURE:
		ret = COORD
		{
			0, this->drawParamEditor("Choose measure: ", {
				"1. 2/4",
				"2. 3/4",
				"3. 4/4",
				"4. 6/8"
			})
		};
		break;

	case Action::CHANGE_NOTE_VOLUME:
		ret = COORD{ 0, this->drawParamEditor("Enter note volume(0 - 127):") }; 
		break;
		

	default:
		break;
	}

	//Menu
	if (this->_mode == Mode::VIEW)
	{
		this->drawViewMenu();
	}
	else
	{
		this->drawEditMenu();
	}

	//Note properites, last cause we're setting
	//Cursor position here
	if (this->_mode == Mode::EDIT)
	{
		this->drawNoteProperties(infoOffset);
	}

	Util::setCursorPos(0, this->_size.rows - 3);

	return ret;
}

#pragma region Components

uint8_t UIManager::drawSequenceInfo() const
{
	Util::setColor(Color::DarkGreen);
	Util::writeMulti(
		this->_seq.name(), this->_seq.getFormatString(),
		Util::createColor(Color::DarkCyan)
	);

	Util::setColor(Color::DarkCyan);
	Util::writeMulti(
		"Mode: " + ModeMap[this->_mode],
		"Measure: " + to_string(this->_seq.numerator()) + "/" + to_string(this->_seq.denominator())
	);

	Util::writeLeft("Current channel: " + MIDIChannelMap[this->_seq.currentChannel()]);
	Util::newLine(2);

	return Util::writtenLines;
}

void UIManager::drawPianoRoll() const
{
	//Bars numbers
	Util::setColor(Color::Red);
	cout << "    ";
	for (unsigned i = 0 + this->_seq.firstBarToShow();
		i < this->pianoRollWidth / this->_seq.numerator() + this->_seq.firstBarToShow();
		i++)
	{
		cout << i;

		for (int j = 0;
			j < this->_seq.numerator() - Util::getNumberOfDigits(i);
			j++)
		{
			cout << ' ';
		}
	}
	Util::newLine();

	cout << "    ";
	Util::makeLine(this->pianoRollWidth, Util::createColor(Color::DarkRed));

	for (unsigned k = 0; k < this->pianoRollHeight; k++)
	{
		Util::setColor(Color::Red);
		NotePitch p = NotePitch(static_cast<uint8_t>(this->_seq.firstNoteToShow()) + k);
		string text = SMF::NotePitchMap[p];
		cout << text;

		for (size_t i = 0; i < 4 - text.size(); i++)
		{
			cout << ' ';
		}

		for (uint16_t i = 0;
			i < this->pianoRollWidth / this->_seq.numerator() * this->_seq.numerator(); i++)
		{
			Color c = Color::Black;

			//Bar has notes
			if(this->_seq.getBar({
				p,
				(this->_seq.firstBarToShow() - 1) * this->_seq.numerator() + i
			}).size() > 0)
			{
				c = Color::DarkBlue;
			}

			//Selected note indicator
			if (this->_mode == Mode::EDIT)
			{
				if (i == this->_seq.currentBar() && k == this->_seq.currentNotePitch())
				{
					c = Color::DarkRed;
				}
			}

			if (i % this->_seq.numerator() == 0)
			{
				Util::setColor(Color::DarkGreen, c);
			}
			else
			{
				Util::setColor(Color::DarkGray, c);
			}

			cout << '*';
		}
		Util::newLine();
	}
	Util::newLine();
}

void UIManager::drawBarCloseUp() const
{
	Color c;

	Util::writeLeft("Bar close-up: (32nd notes)");

	Note* currentNote;
	for (uint8_t i = 0; i < this->_seq.numOf32NotesInBar(); i++)
	{
		c = Color::Black;

		//Note present
		currentNote = this->_seq.getNote(this->_seq.getCurrentNoteCoords(), i);
		if(currentNote != nullptr)
		{
			c = Color::DarkBlue;
			if(currentNote->ligature())
			{
				c = Color::DarkMagenta;
			}
		}

		//Indicator
		if (this->_action == Action::BAR_EDIT && i == this->_seq.currentNoteInBar())
		{
			c = Color::DarkRed;
		}

		Util::setColor(Color::Gray, c);
		cout << (i == this->_seq.numOf32NotesInBar() - 1 ? "*" : "* ");
	}

	Util::newLine(2);
}

void UIManager::drawNoteProperties(uint8_t offsetTop)  const
{
	array<string, 4> properties = { "Pitch:", "Volume:", "Duration:", "Ligature:" };

	auto note = this->_seq.getCurrentNote();

	array<string, 4> values;

	if(note != nullptr)
	{
		values = {
			SMF::NotePitchMap[note->pitch()],
			to_string(note->volume()),
			to_string(note->duration()),
			note->ligatureToString()
		};
	}

	uint8_t offsetLeft = this->_size.cols - PIANO_ROLL_MARGIN + 10;

	Util::setColor(Color::Cyan);
	Util::setCursorPos(offsetLeft, offsetTop);
	cout << "Note properties: " << endl;

	Util::setColor(Color::Gray);
	for(size_t i = 0; i < properties.size(); i++)
	{
		Util::setCursorPos(offsetLeft, offsetTop + static_cast<SHORT>(i) + 1);
		cout << properties[i] << "\t";

		if(note != nullptr)
		{
			cout << values[i];
		}

		cout << endl;
	}
}

SHORT UIManager::drawParamEditor(string msg, vector<string> additional) const
{
	SHORT tmp = Util::writtenLines;

	Util::setColor(Color::DarkRed, Color::Gray);
	Util::makeLine(this->_size.cols);

	Util::setColor(Color::Red);
	Util::writeLeft(msg);

	for (auto& m : additional)
	{
		Util::writeLeft(m);
	}

	Util::newLine();	//Here will be cursor

	Util::setColor(Color::DarkRed, Color::Gray);
	Util::makeLine(this->_size.cols);

	return tmp + 2 + static_cast<SHORT>(additional.size());
}

#pragma endregion

#pragma region Menu

void UIManager::drawViewMenu() const
{
	Util::newLine(this->_size.rows - Util::writtenLines - 2);

	vector<string> cmds = { 
		"UP", "DN", "LT", "RT", 
		" N", " S", " M" };
	vector<string> names = { 
		"Roll up", "Roll down", "Roll left", "Roll right", 
		"Edit mode", "Seq name", "Set measure" };

	for (size_t i = 0; i < names.size(); i++)
	{
		Util::setColor(Color::Black, Color::Gray);
		cout << cmds[i];
		Util::setColor(Color::DarkGray);
		cout << ' ' << names[i];
	
		//TODO: Fix for consoleSize
		if ((i + 1) % 8 == 0)
		{
			cout << endl;
		}
		else
		{
			cout << '\t';
		}
	}
}

void UIManager::drawEditMenu() const
{
	Util::newLine(this->_size.rows - Util::writtenLines - 2);

	vector<string> cmds = { 
		"UP", "DN", "LT", "RT", 
		" N", 
		" W", " S", " A", " D",
		" B", " I", " V", " L" };
	vector<string> names = { 
		"Roll up", "Roll down", "Roll left", "Roll right", 
		"View mode",
		"Note up", "Note down", "Note left", "Note right",
		"Bar Edit", "Ins note", "Chg vol", "Ligature" };

	for (size_t i = 0; i < names.size(); i++)
	{
		Util::setColor(Color::Black, Color::Gray);
		cout << cmds[i];
		Util::setColor(Color::DarkGray);
		cout << ' ' << names[i];

		//TODO: Fix for consoleSize
		if((i+1) % 8 == 0)
		{
			cout << endl;
		}
		else
		{
			cout << '\t';
		}
	}
}

#pragma endregion