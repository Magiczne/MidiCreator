#pragma once

#include "stdafx.h"

#include "EventManager.h"
#include "Sequence.h"
#include "UI/UIManager.h"

class MidiCreator
{
private:
	Sequence _sequence;
	UI::UIManager _uiManager;
	EventManager _eventManager;

public:
	MidiCreator();

	int exec();
};