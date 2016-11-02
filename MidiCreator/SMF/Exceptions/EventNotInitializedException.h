#pragma once

#include "../../stdafx.h"

namespace SMF
{
	namespace Exceptions
	{
		class EventNotInitializedException :
			public std::exception
		{
			virtual const char* what() const noexcept
			{
				return "Event is not initialized!";
			}
		};
	}
}