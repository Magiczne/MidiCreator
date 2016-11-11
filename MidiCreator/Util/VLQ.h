#pragma once

#include "../stdafx.h"

class VLQ final
{
private:
	unsigned long intVal;
	std::vector<uint8_t> vlqVal;

	void toInt();
	void toVlq();
	
public:
	VLQ(unsigned long);
	VLQ(std::vector<uint8_t>);

	inline const unsigned long& getInt() { return this->intVal; }
	inline const std::vector<uint8_t>& getVlq() { return this->vlqVal; }
};