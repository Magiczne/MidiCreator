#pragma once

#include "../../stdafx.h"
#include "../../Abstract/IEvent.h"
#include "../../Abstract/IConvertibleToByteCollection.h"
#include "../Enums/MetaEventType.h"

namespace SMF
{
	class MetaEvent :
		public IEvent,
		public IConvertibleToByteCollection
	{
	public:
		const uint8_t id = 0xFF;
		MetaEventType type;
		int vLength;
		std::vector<uint8_t> eventData;

		MetaEvent();
		~MetaEvent();

		//IConvertibleToByteCollection
		virtual std::vector<uint8_t> toByteVector();
	};
}

