#pragma once

#include "..\..\stdafx.h"
#include "..\Enums\Mode.h"

namespace UI
{
	static std::map<Mode, std::string> ModeMap =
	{
		{ Mode::VIEW, "View" },
		{ Mode::EDIT, "Edit" }
	};
}