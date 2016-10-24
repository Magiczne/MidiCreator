#pragma once

#include "../../stdafx.h"
#include "../../Abstract/IEvent.h"
#include "../../Abstract/IConvertibleToByteArray.h"

namespace SMF
{
	class SystemExclusiveEvent :
		IEvent,
		IConvertibleToByteArray
	{
	public:
		byte head;					//0xF0 or 0xF7
		std::vector<byte> dataBytes;
		const byte tail = 0xF7;
		
		SystemExclusiveEvent();
		~SystemExclusiveEvent();

		//IConvertibleToByteArray
		virtual std::vector<byte> toByteVector();
	};
}

