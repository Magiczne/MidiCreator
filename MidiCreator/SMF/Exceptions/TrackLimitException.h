#pragma once

#include "../../stdafx.h"

namespace SMF
{
	namespace Exceptions
	{
		class TrackLimitException :
			public std::exception
		{
			const char* what() const noexcept override
			{
				return "Track limit has been reached!";
			}
		};
	}
}