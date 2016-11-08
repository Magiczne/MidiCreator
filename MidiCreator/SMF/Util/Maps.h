#pragma once

#include "..\..\stdafx.h"
#include "..\Enums\FileFormat.h"

using namespace std;

namespace SMF
{
	static map<FileFormat, string> FileFormatMap = 
	{
		{ FileFormat::SINGLE_TRACK, "Single track" },
		{ FileFormat::MULTIPLE_TRACK, "Multiple tracks" },
		{ FileFormat::MULTIPLE_SONG, "Multiple songs" }
	};
}
