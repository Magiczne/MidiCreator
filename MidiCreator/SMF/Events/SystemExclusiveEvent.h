#pragma once

#include "../../stdafx.h"
#include "../../Abstract/IEvent.h"

namespace SMF
{
	class SystemExclusiveEvent :
		public IEvent
	{
	public:
		uint8_t head;					//0xF0 or 0xF7
		const uint8_t tail = 0xF7;
		
		SystemExclusiveEvent();
		~SystemExclusiveEvent();

		//IConvertibleToByteCollection
		virtual std::vector<uint8_t> toByteVector();
	};
}

