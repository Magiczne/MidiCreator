#pragma once

#include "../../stdafx.h"
#include "../Abstract/IConvertibleToByteCollection.h"
#include "../Abstract/IEvent.h"
#include "../Enums/EventType.h"
#include "../Exceptions/EventNotInitializedException.h"

namespace SMF
{
	class TrackEvent final : public IConvertibleToByteCollection
	{
	private:
		VLQ* _deltaTime = nullptr;
		IEvent* _event = nullptr;

		bool isInitialized() const;
	public:
		TrackEvent() = delete;
		explicit TrackEvent(EventType eventType);
		~TrackEvent();

		TrackEvent* setDeltaTime(int time);

		template<typename T>
		T* getInnerEvent();

		//IConvertibleToByteCollection
		std::vector<uint8_t> toByteVector() const override;
	};

	template<typename T>
	T* TrackEvent::getInnerEvent()
	{
		if (this->_event == nullptr)
		{
			throw Exceptions::EventNotInitializedException();
		}

		return dynamic_cast<T*>(this->_event);
	}
}