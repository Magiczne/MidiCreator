#pragma once

#include "../../stdafx.h"
#include "../Abstract/IEvent.h"

namespace SMF
{
	class SystemExclusiveEvent final : public IEvent
	{
	public:
		uint8_t head;					//0xF0 or 0xF7
		const uint8_t tail = 0xF7;

		//IConvertibleToByteCollection
		std::vector<uint8_t> toByteVector() const override;
	};
}