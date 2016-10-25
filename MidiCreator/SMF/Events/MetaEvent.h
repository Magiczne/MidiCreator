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
	private:
		const uint8_t id = 0xFF;
		MetaEventType type;
		int vLength;

	public:
		MetaEvent();
		~MetaEvent();

		MetaEvent* setEventType(MetaEventType);
		MetaEvent* setLength(int);

		//IConvertibleToByteCollection
		virtual std::vector<uint8_t> toByteVector();
	};
}

