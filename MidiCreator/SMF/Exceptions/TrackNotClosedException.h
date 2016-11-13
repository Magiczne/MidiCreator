#pragma once

#include "../../stdafx.h"

namespace SMF
{
	namespace Exceptions
	{
		class TrackNotClosedException :
			public std::exception
		{
			const char* what() const noexcept override
			{
				return "Track is not closed!";
			}
		};
	}
}