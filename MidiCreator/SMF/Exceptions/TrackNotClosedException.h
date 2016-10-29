#pragma once

#include "../../stdafx.h"

namespace SMF
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