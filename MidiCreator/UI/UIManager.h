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
		Sequence& seq;

		Mode _mode = Mode::VIEW;
		Action _action = Action::NONE;

		void drawViewMenu(ConsoleSize& size) const;
		void drawEditMenu(ConsoleSize& size) const;

		SHORT drawParamEditor(ConsoleSize& size, std::string msg, std::vector<std::string> = {}) const;

	public:
		UIManager() = delete;
		explicit UIManager(Sequence& seq);

		uint16_t pianoRollWidth = 0;
		const uint16_t pianoRollHeight = 12;

		void drawMenu() const;
		Nullable<COORD> drawSequenceScreen();

		//Getters/setters

		void mode(const Mode& val) { this->_mode = val; }
		const Mode& mode() const { return this->_mode; }

		void action(const Action& val) { this->_action = val; }
		const Action& action() const { return this->_action; }
	};
}

