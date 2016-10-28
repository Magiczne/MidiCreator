#pragma once

#include "../../stdafx.h"

namespace SMF
{
	class TrackNumberOutOfRangeException :
		public std::exception
	{
		virtual const char* what() const throw()
		{
			return "There are no tracks with that id!";
		}
	};
}