#pragma once

#include "../stdafx.h"

namespace Exceptions
{
	class InvalidFileFormatException :
		public std::exception
	{
		const char* what() const noexcept override
		{
			return "Invalid file format!";
		}
	};
}