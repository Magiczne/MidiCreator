#include "SystemExclusiveEvent.h"

using namespace SMF;

SystemExclusiveEvent::SystemExclusiveEvent()
{
}

byte* SystemExclusiveEvent::toByteArray()
{
	return new byte[2];
}

SystemExclusiveEvent::~SystemExclusiveEvent()
{
}
