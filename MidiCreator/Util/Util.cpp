#include "Util.h"

using namespace UI;

ConsoleSize Util::getConsoleSize()
{
	ConsoleSize size;

	CONSOLE_SCREEN_BUFFER_INFO csbi;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	size.cols = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	size.rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

	return size;
}

void Util::setConsoleSize(int width, int height)
{
	COORD coord;
	coord.X = height;
	coord.Y = width;

	SMALL_RECT rect;
	rect.Top = 0;
	rect.Left = 0;
	rect.Bottom = height - 1;
	rect.Right = width - 1;

	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleScreenBufferSize(handle, coord);
	SetConsoleWindowInfo(handle, true, &rect);
}

void Util::setColor(Color background, Color text)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	uint8_t val = ((uint8_t)background << 4) + (uint8_t)text;

	SetConsoleTextAttribute(hConsole, val);
}

void Util::clearConsole()
{
	system("cls");
}

void Util::writeLeft(string msg)
{
	cout << msg << endl;
}

void Util::writeCentered(string msg)
{
	ConsoleSize size = Util::getConsoleSize();

	int width = (size.cols + msg.size()) / 2;
	cout << setw(width) << msg << endl;
}

void Util::writeRight(string msg)
{
	ConsoleSize size = Util::getConsoleSize();
	cout << setw(size.cols) << msg << endl;
}

void Util::writeMulti(string left, string right)
{
	ConsoleSize size = Util::getConsoleSize();
	cout << left;

	cout << setw(size.cols - left.size()) << right << endl;
}

char Util::getUnbufferedKey()
{
	DWORD events;
	INPUT_RECORD buffer;
	HANDLE handle = GetStdHandle(STD_INPUT_HANDLE);

	PeekConsoleInput(handle, &buffer, 1, &events);

	if (events > 0)
	{
		ReadConsoleInput(handle, &buffer, 1, &events);
		return (char)buffer.Event.KeyEvent.wVirtualKeyCode;
	}
	else
	{
		return 0;
	}
}