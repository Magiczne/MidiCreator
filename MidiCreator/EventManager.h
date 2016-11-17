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
	UI::UIManager* _uiManager;
	Sequence& _seq;

	void changeSequenceName() const;
	void changeMeasure(uint16_t vk) const;

	//Handling keys:
	void handleKeyA() const;
	void handleKeyB() const;
	void handleKeyD() const;
	void handleKeyI() const;
	void handleKeyM() const;
	void handleKeyN() const;
	void handleKeyS() const;
	void handleKeyW() const;

	void handleUpArrow() const;
	void handleDownArrow() const;
	void handleLeftArrow() const;
	void handleRightArrow() const;

public:
	EventManager() = delete;
	EventManager(UI::UIManager* ui, Sequence& seq);

	static MenuEventType menuLoop();
	void sequenceScreenLoop() const;
};