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
	Sequence& seq;

	void changeSequenceName();
	void changeMeasure(uint16_t vk);
public:
	EventManager() = delete;
	EventManager(UI::UIManager* ui, Sequence& seq);

	MenuEventType menuLoop();
	void sequenceScreenLoop();
};

