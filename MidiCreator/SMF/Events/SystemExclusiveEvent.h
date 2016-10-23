#pragma once

#include "../../stdafx.h"
#include "../../Interfaces/IEvent.h"
#include "../../Interfaces/IConvertibleToByteArray.h"

namespace SMF
{
	class SystemExclusiveEvent :
		IEvent,
		IConvertibleToByteArray
	{
	public:
		SystemExclusiveEvent();
		~SystemExclusiveEvent();
	};
}

