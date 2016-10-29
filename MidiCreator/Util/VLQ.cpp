#include "VLQ.h"

VLQ::VLQ(unsigned long intVal)
{
	this->intVal = intVal;
	this->toVlq();
}

VLQ::VLQ(std::vector<uint8_t> vqlVal)
{
	this->vlqVal = vqlVal;
	this->toInt();
}

void VLQ::toInt()
{
	uint8_t* arr = this->vlqVal.data();

	int ret = 0;

	do
	{
		ret = (ret << 7) | (int)(*arr & 127);
	} while (*arr++ & 128);

	this->intVal = ret;
}

void VLQ::toVlq()
{
	std::vector<uint8_t> ret;

	unsigned long buffer;
	buffer = this->intVal & 0x7F;

	while (this->intVal >>= 7)
	{
		buffer <<= 8;
		buffer |= ((this->intVal & 0x7F) | 0x80);
	}

	for (;;)
	{
		ret.push_back((uint8_t)buffer);
		if (buffer & 0x80)
			buffer >>= 8;
		else
			break;
	}

	this->vlqVal = ret;
}

