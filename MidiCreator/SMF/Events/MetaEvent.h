#pragma once

#include "../../stdafx.h"
#include "../../Abstract/IEvent.h"
#include "../../Abstract/IConvertibleToByteArray.h"
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
		virtual std::vector<byte> toByteVector();
	};
}

