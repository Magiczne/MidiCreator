#pragma once

#include "IEvent.h"

using namespace SMF;

IEvent* IEvent::addParam(uint8_t param)
{
	params.push_back(param);
	return this;
}