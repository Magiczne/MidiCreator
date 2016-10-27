#pragma once

#include "../stdafx.h"
#include "../Util/VLQ.h"

namespace SMF
{
	class IEvent 
	{
	protected:
		std::vector<uint8_t> params;

	public:
		virtual IEvent* addParam(uint8_t);
		virtual IEvent* addParam(VLQ);
	};
}