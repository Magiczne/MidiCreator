#pragma once

#include "stdafx.h"
#include "EventManager.h"
#include "UI\UIManager.h"

using namespace std;
using namespace UI;

class MidiCreator
{
private:
	EventManager* eventManager;
	UIManager* uiManager;

public:
	MidiCreator();
	~MidiCreator();

	int exec();
};

