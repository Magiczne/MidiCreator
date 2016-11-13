#pragma once

#include "../../stdafx.h"
#include "../StandardMIDIFile.h"

namespace SMF
{
	namespace Exceptions
	{
		class BpmOutOfRangeException :
			public std::exception
		{
			const char* what() const noexcept override
			{
				std::string msg = "BPM out of range! ("
					+ std::to_string(StandardMIDIFile::MIN_BPM)
					+ " - "
					+ std::to_string(StandardMIDIFile::MAX_BPM)
					+ ")";

				return msg.c_str();
			}
		};
	}
}