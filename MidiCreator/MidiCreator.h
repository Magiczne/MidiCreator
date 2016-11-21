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
	Sequence* sequence;
	EventManager* eventManager;
	UI::UIManager* uiManager;

public:
	MidiCreator();
	~MidiCreator();

	int exec() const;
};