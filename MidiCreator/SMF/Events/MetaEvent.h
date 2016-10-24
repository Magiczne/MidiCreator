#pragma once

#include "../../stdafx.h"
#include "../../Interfaces/IEvent.h"
#include "../../Interfaces/IConvertibleToByteArray.h"
#include "../Enums/MetaEventType.h"

namespace SMF
{
	class MetaEvent :
		IEvent,
		IConvertibleToByteArray
	{
	public:
		const byte id = 0xFF;
		MetaEventType type;
		int vLength;
		std::vector<byte> eventData;

		MetaEvent();
		~MetaEvent();

		//IConvertibleToByteArray
		byte* toByteArray();
	};
}

