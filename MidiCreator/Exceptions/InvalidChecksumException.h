#pragma once

#include "../stdafx.h"
#include "SequenceFileException.h"

namespace Exceptions
{
	class InvalidChecksumException :
		public SequenceFileException
	{
		const char* what() const noexcept override
		{
			return "Invalid file header checksum!";
		}
	};
}
