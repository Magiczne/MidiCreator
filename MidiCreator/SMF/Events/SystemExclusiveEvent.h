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
		byte head;				//0xF0 or 0xF7
		byte* dataBytes;		
		const byte tail = 0xF7;
		
		SystemExclusiveEvent();
		~SystemExclusiveEvent();

		//IConvertibleToByteArray
		byte* toByteArray();
	};
}

