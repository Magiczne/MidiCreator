#pragma once

#include "../../stdafx.h"
#include "../../Abstract/IEvent.h"
#include "../../Abstract/IConvertibleToByteArray.h"

namespace SMF
{
	class TrackEvent :
		IEvent,
		IConvertibleToByteArray
	{
	public:
		int vTime;
		IEvent* event;

		TrackEvent();
		~TrackEvent();

		//IConvertibleToByteArray
		virtual std::vector<byte> toByteVector();
	};
}

