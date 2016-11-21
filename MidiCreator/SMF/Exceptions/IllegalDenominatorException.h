#pragma once

#include "../../stdafx.h"

namespace SMF
{
	namespace Exceptions
	{
		class IllegalDenominatorException :
			public std::exception
		{
			const char* what() const noexcept override
			{
				return "Illegal denominator! Allowed denominators are: 2, 4, 8, 16, 32, 64";
			}
		};
	}
}