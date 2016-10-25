#pragma once

#include "../../stdafx.h"
#include "../../Abstract/IEvent.h"
#include "../../Abstract/IConvertibleToByteCollection.h"

namespace SMF
{
	class TrackEvent :
		IEvent,
		IConvertibleToByteCollection
	{
	public:
		int vTime;
		IEvent* event;

		TrackEvent();
		~TrackEvent();

		//IConvertibleToByteCollection
		virtual std::vector<uint8_t> toByteVector();
	};
}

