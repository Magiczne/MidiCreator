#pragma once

#include "../stdafx.h"

class IConvertibleToByteArray
{
public:
	virtual byte* toByteArray() = 0;
};