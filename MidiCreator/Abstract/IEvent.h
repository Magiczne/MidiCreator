#pragma once

#include "../stdafx.h"
#include "IConvertibleToByteCollection.h"
#include "../Util/VLQ.h"

namespace SMF
{
	class IEvent : 
		public IConvertibleToByteCollection
	{
	protected:
		std::vector<uint8_t> params;

	public:
		virtual IEvent* addParam(uint8_t param);
		virtual IEvent* addParam(VLQ param);
	};
}