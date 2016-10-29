#pragma once

#include "../../stdafx.h"

namespace SMF
{
	class IllegalChannelException :
		public std::exception
	{
		virtual const char* what() const noexcept
		{
			return "Illegal channel! Allowed channels are between 1-16";
		}
	};
}
