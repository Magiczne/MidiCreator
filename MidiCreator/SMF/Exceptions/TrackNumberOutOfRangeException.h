#pragma once

#include "../../stdafx.h"

namespace SMF
{
	namespace Exceptions
	{
		class TrackNumberOutOfRangeException :
			public std::exception
		{
			const char* what() const noexcept override
			{
				return "There are no tracks with that id!";
			}
		};
	}
}