#pragma once

#include "stdafx.h"
#include "Util\Util.h"
#include "UI\UIManager.h"

enum MenuEventType
{
	NEW_SEQUENCE,
	OPEN_SEQUENCE,
	QUIT
};

class EventManager
{
private:
	UI::UIManager* uiManager;

public:
	EventManager() = delete;
	EventManager(UI::UIManager* ui) { this->uiManager = ui; }

	MenuEventType menuLoop();
	void sequenceScreenLoop(Sequence& seq);
};

