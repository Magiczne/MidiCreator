#pragma once

#include "../stdafx.h"

namespace Exceptions
{
	class InvalidChecksumException :
		public std::exception
	{
		const char* what() const noexcept override
		{
			return "Invalid file header checksum!";
		}
	};
}