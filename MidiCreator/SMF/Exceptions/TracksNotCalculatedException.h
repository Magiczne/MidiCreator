#pragma once

#include "../../stdafx.h"

namespace SMF
{
	namespace Exceptions
	{
		class TracksNotCalculatedException :
			public std::exception
		{
			const char* what() const noexcept override
			{
				return "Tracks length was not calculated!";
			}
		};
	}
}