#pragma once

#include "../../stdafx.h"

namespace SMF
{
	namespace Exceptions
	{
		class TrackNotClosedException :
			public std::exception
		{
			virtual const char* what() const noexcept
			{
				return "Track is not closed!";
			}
		};
	}
}