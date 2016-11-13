#pragma once

#include "../../stdafx.h"

namespace SMF
{
	namespace Exceptions
	{
		class EventTypeNotSupportedException :
			public std::exception
		{
			const char* what() const noexcept override
			{
				return "Event type not supported!";
			}
		};
	}
}