#pragma once

#include "stdafx.h"
#include "Util\Util.h"
#include "UI\UIManager.h"

using namespace UI;

enum MenuEventType
{
	NEW_SEQUENCE,
	OPEN_SEQUENCE,
	QUIT
};

class EventManager
{
private:
	UIManager* uiManager;

public:
	EventManager() = delete;
	EventManager(UIManager* ui) { this->uiManager = ui; }

	MenuEventType menuLoop();
};

