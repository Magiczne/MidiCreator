#pragma once

#include "../../stdafx.h"

namespace SMF
{
	namespace Exceptions
	{
		class TrackNumberOutOfRangeException :
			public std::exception
		{
			virtual const char* what() const noexcept
			{
				return "There are no tracks with that id!";
			}
		};
	}
}