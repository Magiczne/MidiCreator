#pragma once

class IConvertibleToByteArray
{
public:
	virtual byte* toByteArray() = 0;
};