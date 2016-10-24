#pragma once

#include "../stdafx.h"
#include "IConvertibleToByteArray.h"

byte* IConvertibleToByteArray::toByteArray()
{
	std::vector<byte>& a = this->toByteVector();
	//TODO: Not working :c
	return a.data();
}