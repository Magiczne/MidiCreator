#pragma once

#include "../../stdafx.h"

namespace SMF
{
	namespace Exceptions
	{
		class TrackClosedException :
			public std::exception
		{
			virtual const char* what() const noexcept
			{
				return "Track is closed! Reopen it to make changes";
			}
		};
	}
}