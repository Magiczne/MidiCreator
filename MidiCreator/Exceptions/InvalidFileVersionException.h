#pragma once

#include "../stdafx.h"

namespace Exceptions
{
	class InvalidFileVersionException :
		public std::exception
	{
		const char* what() const noexcept override
		{
			return "Invalid file version!";
		}
	};
}