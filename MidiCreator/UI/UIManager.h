#pragma once

#include "../stdafx.h"
#include "../Util/Util.h"
#include "Enums/Mode.h"
#include "Enums/Action.h"
#include "../Util/Nullable.h"

class Sequence;

namespace UI
{
	class UIManager
	{
	private:
		const uint8_t PIANO_ROLL_MARGIN = 30;

		Mode _mode = VIEW;
		Action _action = NONE;

		Sequence& _seq;
		ConsoleSize _size;

		std::string _lastMessage;

		//Sequence screen components
		uint8_t drawSequenceInfo() const;
		void drawPianoRoll() const;
		void drawBarCloseUp() const;
		void drawNoteProperties(uint8_t offsetTop) const;
		SHORT drawParamEditor(std::string msg, std::vector<std::string> additional = {}) const;

		void drawLastInfo() const;
		void drawViewMenu() const;
		void drawEditMenu() const;

	public:
		UIManager() = delete;
		explicit UIManager(Sequence& seq);

		uint16_t pianoRollWidth = 0;
		const uint16_t pianoRollHeight = 12;

		void drawMenu() const;
		Nullable<COORD> drawSequenceScreen();
		void drawOpenFileScreen();

		//Getters/setters

		void mode(const Mode& val) { this->_mode = val; }
		const Mode& mode() const { return this->_mode; }

		void action(const Action& val) { this->_action = val; }
		const Action& action() const { return this->_action; }

		void lastMessage(const std::string& val) { this->_lastMessage = val; }
		const std::string& lastMessage() const { return this->_lastMessage; }
	};
}