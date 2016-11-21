#pragma once

#include "../../stdafx.h"

namespace SMF
{
	class IConvertibleToByteCollection
	{
	public:
		virtual std::vector<uint8_t> toByteVector() = 0;

		virtual ~IConvertibleToByteCollection() {}
	};
}