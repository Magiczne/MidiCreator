#pragma once

#include "..\stdafx.h"
#include "Enums\Mode.h"

class Sequence;

namespace UI
{
	class UIManager
	{
	private:
		Mode _mode = Mode::EDIT;

	public:
		unsigned pianoRollWidth;
		const unsigned pianoRollHeight = 12;

		void drawMenu();
		void drawSequenceScreen(Sequence& seq);

		//Getters/setters

		void mode(const Mode& val) { this->_mode = val; }
		const Mode& mode() { return this->_mode; }
	};
}

