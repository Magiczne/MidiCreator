#pragma once

#include "../../stdafx.h"

namespace SMF
{
	namespace Exceptions
	{
		class TrackClosedException :
			public std::exception
		{
			const char* what() const noexcept override
			{
				return "Track is closed! Reopen it to make changes";
			}
		};
	}
}