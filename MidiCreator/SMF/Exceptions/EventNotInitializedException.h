#pragma once

#include "../../stdafx.h"

namespace SMF
{
	namespace Exceptions
	{
		class EventNotInitializedException :
			public std::exception
		{
			const char* what() const noexcept override
			{
				return "Event is not initialized!";
			}
		};
	}
}