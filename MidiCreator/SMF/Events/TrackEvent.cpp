#include "TrackEvent.h"

using namespace SMF;

TrackEvent::TrackEvent()
{
}

byte* TrackEvent::toByteArray()
{
	return new byte[2];
}

TrackEvent::~TrackEvent()
{
}
