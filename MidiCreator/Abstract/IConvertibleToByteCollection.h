#pragma once

#include "../stdafx.h"

class IConvertibleToByteCollection
{
public:
	virtual std::vector<uint8_t> toByteVector() = 0;

	virtual ~IConvertibleToByteCollection() {}
};