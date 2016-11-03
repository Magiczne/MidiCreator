#pragma once

#include "../../stdafx.h"
#include "../Abstract/IEvent.h"
#include "../Enums/MetaEventType.h"
#include "../Exceptions/EventNotInitializedException.h"

namespace SMF
{
	class MetaEvent :
		public IEvent
	{
	private:
		const uint8_t id = 0xFF;
		MetaEventType type;
		VLQ* vLength = nullptr;

		std::array<bool, 2> initialized = { false };
		bool isInitialized();

	public:
		MetaEvent();
		MetaEvent(MetaEventType eventType);
		~MetaEvent();

		MetaEvent* setEventType(MetaEventType eventType);
		MetaEvent* setLength(int length);

		//IConvertibleToByteCollection
		virtual std::vector<uint8_t> toByteVector();
	};
}

