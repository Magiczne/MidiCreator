#pragma once

#include "../../stdafx.h"

namespace SMF
{
	class NoTracksException :
		public std::exception
	{
		virtual const char* what() const throw()
		{
			return "There are no tracks in this file!";
		}
	};
}