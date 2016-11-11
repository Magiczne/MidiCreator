#pragma once

#include "../../stdafx.h"
#include "../../Abstract/IConvertibleToByteCollection.h"
#include "../Abstract/IEvent.h"
#include "../Enums/EventType.h"
#include "../Exceptions/EventNotInitializedException.h"

namespace SMF
{
	class TrackEvent :
		IConvertibleToByteCollection
	{
	private:
		VLQ* deltaTime = nullptr;
		IEvent* event = nullptr;

		bool isInitialized();
	public:
		TrackEvent(EventType eventType);
		~TrackEvent();

		TrackEvent* setDeltaTime(int time);

		template<typename T>
		inline T* getInnerEvent();

		//IConvertibleToByteCollection
		virtual std::vector<uint8_t> toByteVector();
	};

	template<typename T>
	inline T* TrackEvent::getInnerEvent()
	{
		if (this->event == nullptr)
		{
			throw new EventNotInitializedException;
		}

		return dynamic_cast<T*>(this->event);
	}
}
