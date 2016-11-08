#pragma once

#include "..\stdafx.h"
#include "..\Util\Util.h"
#include "..\Sequence.h"

namespace UI
{
	class UIManager
	{
	public:
		void drawMenu();
		void drawSequenceScreen(Sequence& seq);
	};
}

