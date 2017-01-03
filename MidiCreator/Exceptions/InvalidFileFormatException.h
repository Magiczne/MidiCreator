#pragma once

#include "../stdafx.h"
#include "SequenceFileException.h"

namespace Exceptions
{
	class InvalidFileFormatException :
		public SequenceFileException
	{
		const char* what() const noexcept override
		{
			return "Invalid file format!";
		}
	};
}
