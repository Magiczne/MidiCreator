#pragma once

#include "../../stdafx.h"
#include "../../Interfaces/IEvent.h"
#include "../../Interfaces/IConvertibleToByteArray.h"

namespace SMF
{
	class MetaEvent :
		IEvent,
		IConvertibleToByteArray
	{
	public:
		MetaEvent();
		~MetaEvent();
	};
}

