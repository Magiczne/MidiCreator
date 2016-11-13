#pragma once

#include "stdafx.h"
#include "UI/UIManager.h"

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

	void changeSequenceName() const;
	void changeMeasure(uint16_t vk) const;
public:
	EventManager() = delete;
	EventManager(UI::UIManager* ui, Sequence& seq);

	static MenuEventType menuLoop();
	void sequenceScreenLoop() const;
};