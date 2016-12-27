#pragma once

#include "../stdafx.h"

namespace Exceptions
{
	class InvalidHeaderPaddingException :
		public std::exception
	{
		const char* what() const noexcept override
		{
			return "Invalid header padding!";
		}
	};
}