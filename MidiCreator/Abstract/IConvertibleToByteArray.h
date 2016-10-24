#pragma once

class IConvertibleToByteArray
{
protected:
	virtual std::vector<byte> toByteVector() = 0;

public:
	virtual byte* toByteArray() final;
};