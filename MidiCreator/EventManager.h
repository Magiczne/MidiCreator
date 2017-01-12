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
	UI::UIManager& _uiManager;
	Sequence& _seq;

	void changeSequenceName() const;
	void changeMeasure(uint16_t vk) const;
	void changeNoteVolume() const;
	void toggleNoteLigature() const;
	void changeMidiChannel() const;
	void changeTempo() const;

	//Handling keys:
	void handleA() const;
	void handleB() const;
	void handleC() const;
	void handleD() const;
	void handleI() const;
	void handleL() const;
	void handleM() const;
	void handleN() const;
	void handleS() const;
	void handleT() const;
	void handleV() const;
	void handleW() const;
	
	void handleF5() const;
	void handleF6() const;

	void handleUpArrow() const;
	void handleDownArrow() const;
	void handleLeftArrow() const;
	void handleRightArrow() const;

public:
	EventManager() = delete;
	EventManager(UI::UIManager& ui, Sequence& seq);

	static MenuEventType menuLoop();

	static std::string readFilepathFromUser();

	void sequenceScreenLoop() const;
};