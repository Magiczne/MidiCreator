#pragma once

#include "../../stdafx.h"

namespace SMF
{
	class IllegalDenominatorException :
		public std::exception
	{
		virtual const char* what() const noexcept
		{
			return "Illegal denominator! Allowed denominators are: 2, 4, 8, 16, 32, 64";
		}
	};
}
