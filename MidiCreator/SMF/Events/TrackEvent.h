#pragma once

#include "../../stdafx.h"
#include "../../Interfaces/IEvent.h"
#include "../../Interfaces/IConvertibleToByteArray.h"

namespace SMF
{
	class TrackEvent :
		IEvent,
		IConvertibleToByteArray
	{
	public:
		TrackEvent();
		~TrackEvent();
	};
}

