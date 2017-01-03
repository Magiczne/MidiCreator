#pragma once

#include "../stdafx.h"
#include "SequenceFileException.h"

namespace Exceptions
{
	class InvalidHeaderPaddingException :
		public SequenceFileException
	{
		const char* what() const noexcept override
		{
			return "Invalid header padding!";
		}
	};
}