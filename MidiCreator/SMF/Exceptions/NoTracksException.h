#pragma once

#include "../../stdafx.h"

namespace SMF
{
	namespace Exceptions
	{
		class NoTracksException :
			public std::exception
		{
			const char* what() const noexcept override
			{
				return "There are no tracks in this file!";
			}
		};
	}
}