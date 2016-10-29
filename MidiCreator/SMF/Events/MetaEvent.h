#pragma once

#include "../../stdafx.h"
#include "../../Abstract/IEvent.h"
#include "../Enums/MetaEventType.h"

namespace SMF
{
	class MetaEvent :
		public IEvent
	{
	private:
		const uint8_t id = 0xFF;
		MetaEventType type;
		VLQ* vLength;

	public:
		~MetaEvent();

		MetaEvent* setEventType(MetaEventType eventType);
		MetaEvent* setLength(int length);

		//IConvertibleToByteCollection
		virtual std::vector<uint8_t> toByteVector();
	};
}

