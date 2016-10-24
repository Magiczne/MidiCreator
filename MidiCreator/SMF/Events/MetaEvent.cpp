#include "MetaEvent.h"

using namespace SMF;

MetaEvent::MetaEvent()
{
}

byte* MetaEvent::toByteArray()
{
	return new byte[2];
}


MetaEvent::~MetaEvent()
{
}