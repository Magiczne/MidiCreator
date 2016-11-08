#pragma once

#include "..\stdafx.h"
#include "..\Util\Util.h"

class Sequence;

namespace UI
{
	class UIManager
	{
	public:
		unsigned pianoRollWidth;
		const unsigned pianoRollHeight = 12;

		void drawMenu();
		void drawSequenceScreen(Sequence& seq);
	};
}

