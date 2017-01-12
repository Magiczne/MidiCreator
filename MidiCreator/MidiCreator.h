#pragma once

#include "stdafx.h"

namespace UI
{
	class UIManager;
}

class EventManager;
class Sequence;

class MidiCreator
{
private:
	Sequence* _sequence;
	EventManager* _eventManager;
	UI::UIManager* _uiManager;

public:
	MidiCreator();
	~MidiCreator();

	int exec() const;
};