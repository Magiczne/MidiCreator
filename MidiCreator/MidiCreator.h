#pragma once

#include "stdafx.h"

namespace UI
{
	class UIManager;
}

class EventManager;

class MidiCreator
{
private:
	EventManager* eventManager;
	UI::UIManager* uiManager;

public:
	MidiCreator();
	~MidiCreator();

	int exec();
};

