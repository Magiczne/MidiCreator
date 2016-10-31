#pragma once

#include "../../stdafx.h"

namespace SMF
{
	namespace Exceptions
	{
		class NoTracksException :
			public std::exception
		{
			virtual const char* what() const noexcept
			{
				return "There are no tracks in this file!";
			}
		};
	}
}