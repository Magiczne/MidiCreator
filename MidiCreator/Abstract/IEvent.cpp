#pragma once

#include "IEvent.h"

using namespace SMF;

IEvent* IEvent::addParam(uint8_t param)
{
	this->params.push_back(param);
	return this;
}

IEvent* IEvent::addParam(VLQ param)
{
	std::vector<uint8_t> vlq = param.getVlq();
	this->params.insert(params.end(), vlq.begin(), vlq.end());
	return this;
}