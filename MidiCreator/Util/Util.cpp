#include "Util.h"

using namespace UI;
using namespace std;

ConsoleSize Util::getConsoleSize()
{
	ConsoleSize size;

	CONSOLE_SCREEN_BUFFER_INFO csbi;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	size.cols = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	size.rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

	return size;
}

void Util::setConsoleSize(int x, int y)
{
	//http://www.cplusplus.com/forum/windows/121444/#msg661553

	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

	if (h == INVALID_HANDLE_VALUE)
		throw std::runtime_error("Unable to get stdout handle.");

	// If either dimension is greater than the largest console window we can have,
	// there is no point in attempting the change.
	{
		COORD largestSize = GetLargestConsoleWindowSize(h);
		if (x > largestSize.X)
		{
			throw std::invalid_argument("The x dimension is too large.");
		}

		if (y > largestSize.Y)
		{
			throw std::invalid_argument("The y dimension is too large.");
		}
	}


	CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
	if (!GetConsoleScreenBufferInfo(h, &bufferInfo))
	{
		throw std::runtime_error("Unable to retrieve screen buffer info.");
	}

	SMALL_RECT& winInfo = bufferInfo.srWindow;
	COORD windowSize = { winInfo.Right - winInfo.Left + 1, winInfo.Bottom - winInfo.Top + 1 };

	if (windowSize.X > x || windowSize.Y > y)
	{
		// window size needs to be adjusted before the buffer size can be reduced.
		SMALL_RECT info =
		{
			0,
			0,
			x < windowSize.X ? x - 1 : windowSize.X - 1,
			y < windowSize.Y ? y - 1 : windowSize.Y - 1
		};

		if (!SetConsoleWindowInfo(h, TRUE, &info))
		{
			throw std::runtime_error("Unable to resize window before resizing buffer.");
		}
	}

	COORD size = { x, y };
	if (!SetConsoleScreenBufferSize(h, size))
	{
		throw std::runtime_error("Unable to resize screen buffer.");
	}


	SMALL_RECT info = { 0, 0, x - 1, y - 1 };
	if (!SetConsoleWindowInfo(h, TRUE, &info))
	{
		throw std::runtime_error("Unable to resize window after resizing buffer.");
	}
}

void Util::setColor(uint8_t combinedColor)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, combinedColor);
}

void Util::setColor(Color text, Color background)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, Util::createColor(text, background));
}

uint8_t Util::createColor(Color text, Color background)
{
	return ((uint8_t)background << 4) + (uint8_t)text;
}

void Util::clearConsole()
{
	Util::writtenLines = 0;
	system("cls");
}

void Util::setCursorPos(SHORT x, SHORT y)
{
	COORD pos = { x, y };
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(output, pos);
}

void Util::setCursorPos(COORD coord)
{
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(output, coord);
}

void Util::writeLeft(string msg)
{
	Util::writtenLines++;
	cout << msg << endl;
}

void Util::writeCentered(string msg)
{
	Util::writtenLines++;
	ConsoleSize size = Util::getConsoleSize();

	int width = (size.cols + msg.size()) / 2;
	cout << setw(width) << msg << endl;
}

void Util::writeRight(string msg)
{
	Util::writtenLines++;
	ConsoleSize size = Util::getConsoleSize();
	cout << setw(size.cols) << msg << endl;
}

void Util::writeMulti(string left, string right, int8_t rightColor)
{
	Util::writtenLines++;
	ConsoleSize size = Util::getConsoleSize();
	cout << left;

	if (rightColor != -1)
	{
		Util::setColor(rightColor);
	}

	cout << setw(size.cols - left.size()) << right << endl;
}

void Util::makeLine(int width, int8_t color)
{
	Util::writtenLines++;
	if (color != -1)
	{
		Util::setColor(color);
	}

	for (int i = 0; i < width; i++)
	{
		cout << '-';
	}
	
	cout << endl;
}

void Util::newLine(int num)
{
	Util::writtenLines += num;
	for (int i = 0; i < num; i++)
	{
		cout << endl;
	}
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

		if (buffer.Event.KeyEvent.bKeyDown)
		{
			return (char)buffer.Event.KeyEvent.wVirtualKeyCode;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		return 0;
	}
}

unsigned short Util::getNumberOfDigits(unsigned i)
{
	int digits = 0;
	while (i != 0)
	{
		i /= 10;
		digits++;
	}
	return digits;
}

void Util::showLastSystemError()
{
	LPSTR messageBuffer;
	FormatMessageA(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		0,          // source
		GetLastError(),
		0,          // lang
		(LPSTR)&messageBuffer,
		0,
		NULL);

	std::cerr << messageBuffer << '\n';
	LocalFree(messageBuffer);
}