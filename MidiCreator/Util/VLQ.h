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
	explicit VLQ(unsigned long);
	explicit VLQ(std::vector<uint8_t>);

	const unsigned long& getInt() const { return this->intVal; }
	const std::vector<uint8_t>& getVlq() const { return this->vlqVal; }
};