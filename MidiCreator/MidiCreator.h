#pragma once

#include "stdafx.h"
#include "UI\Util.h"

using namespace std;
using namespace UI;

class MidiCreator
{
public:
	void drawMenu();
	void menuEventLoop();

	int exec();
};

