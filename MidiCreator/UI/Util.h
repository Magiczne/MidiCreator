#pragma once

#include "../stdafx.h"

namespace UI
{
	struct ConsoleSize
	{
		int cols;
		int rows;
	};

	
	static class Util
	{
	public:
		static ConsoleSize getConsoleSize();
		static void setConsoleSize(int width, int height);
	};
}
