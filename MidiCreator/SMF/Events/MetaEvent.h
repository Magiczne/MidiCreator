#pragma once

#include "../../stdafx.h"
#include "../Abstract/IEvent.h"
#include "../Enums/MetaEventType.h"

namespace SMF
{
	class MetaEvent final : public IEvent
	{
	private:
		const uint8_t _id = 0xFF;
		MetaEventType _type;
		VLQ* _vLength = nullptr;

		std::array<bool, 2> _initialized = { false };
		bool isInitialized() const;

	public:
		MetaEvent() {};
		explicit MetaEvent(MetaEventType eventType);
		~MetaEvent();

		MetaEvent* setEventType(MetaEventType eventType);
		MetaEvent* setLength(int length);

		//IConvertibleToByteCollection
		std::vector<uint8_t> toByteVector() const override;
	};
}