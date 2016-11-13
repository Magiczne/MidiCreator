#pragma once

#include "../stdafx.h"

namespace UI
{
	struct ConsoleSize
	{
		int cols;
		int rows;
	};

	enum class Color : uint8_t
	{
		Black			= 0,
		DarkBlue		= 1,
		DarkGreen		= 2,
		DarkCyan		= 3,
		DarkRed	 		= 4,
		DarkMagenta		= 5,
		DarkYellow		= 6,
		Gray			= 7,
		DarkGray		= 8,
		Blue			= 9,
		Green			= 10,
		Cyan			= 11,
		Red				= 12,
		Magenta			= 13,
		Yellow			= 14,
		White			= 15
	};
	
	class Util
	{
	public:
		//Console util
		static int writtenLines;

		static ConsoleSize getConsoleSize();
		static void setConsoleSize(int width, int height);

		static uint8_t createColor(Color text, Color background = Color::Black);
		static void setColor(Color text, Color background = Color::Black);
		static void setColor(uint8_t combinedColor);
		

		static void clearConsole();

		static void setCursorPos(SHORT x, SHORT y);
		static void setCursorPos(COORD coord);

		static void writeLeft(std::string msg);
		static void writeCentered(std::string msg);
		static void writeRight(std::string msg);
		static void writeMulti(std::string left, std::string right, int8_t rightColor = -1);
		static void makeLine(int width, int8_t color = -1);
		static void newLine(int num = 1);

		//Keyboard util

		/*
		Returns keycode of pressed key or 0
		*/
		static char getUnbufferedKey();

		//Number util

		static unsigned short getNumberOfDigits(unsigned i);

		//Other util

		static void showLastSystemError();
	};
}
