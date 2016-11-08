#pragma once

#include "../stdafx.h"

using namespace std;

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

		static ConsoleSize getConsoleSize();
		static void setConsoleSize(int width, int height);
		static void setColor(Color background, Color text);

		static void clearConsole();

		static void writeLeft(string msg);
		static void writeCentered(string msg);
		static void writeRight(string msg);
		static void writeMulti(string left, string right);

		//Keyboard util

		/*
		Returns keycode of pressed key or 0
		*/
		static char getUnbufferedKey();
	};
}
