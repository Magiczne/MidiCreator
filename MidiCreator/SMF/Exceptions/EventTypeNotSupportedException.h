#pragma once

#include "../../stdafx.h"

namespace SMF
{
	namespace Exceptions
	{
		class EventTypeNotSupportedException :
			public std::exception
		{
			virtual const char* what() const noexcept
			{
				return "Event type not supported!";
			}
		};
	}
}