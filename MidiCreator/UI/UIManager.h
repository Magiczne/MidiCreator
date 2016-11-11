#pragma once

#include "..\stdafx.h"
#include "..\Util\Util.h"
#include "Enums\Mode.h"
#include "Enums\Action.h"
#include "..\Util\Nullable.h"

class Sequence;

namespace UI
{
	class UIManager
	{
	private:
		Mode _mode = Mode::VIEW;
		Action _action = Action::NONE;

		void drawViewMenu(ConsoleSize& size);
		void drawEditMenu(ConsoleSize& size);

		SHORT drawSequenceNameEditor(ConsoleSize& size);

	public:
		unsigned pianoRollWidth;
		const unsigned pianoRollHeight = 12;

		void drawMenu();
		Nullable<COORD> drawSequenceScreen(Sequence& seq);

		//Getters/setters

		void mode(const Mode& val) { this->_mode = val; }
		const Mode& mode() { return this->_mode; }

		void action(const Action& val) { this->_action = val; }
		const Action& action() { return this->_action; }
	};
}

