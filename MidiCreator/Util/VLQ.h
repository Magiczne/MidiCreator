#pragma once

#include "../stdafx.h"

class VLQ
{
private:
	unsigned long intVal;
	std::vector<uint8_t> vlqVal;

	void toInt();
	void toVlq();
	
public:
	VLQ(unsigned long);
	VLQ(std::vector<uint8_t>);

	inline unsigned long getInt() { return this->intVal; }
	inline std::vector<uint8_t> getVlq() { return this->vlqVal; }
};

