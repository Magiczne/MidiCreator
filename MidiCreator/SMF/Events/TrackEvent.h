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
		std::unique_ptr<VLQ> _deltaTime;
		std::shared_ptr<IEvent> _event;

		bool isInitialized() const;
	public:
		TrackEvent() = delete;
		explicit TrackEvent(EventType eventType);

		TrackEvent& setDeltaTime(int time);

		template<typename T>
		std::shared_ptr<T> getInnerEvent();

		//IConvertibleToByteCollection
		std::vector<uint8_t> toByteVector() const override;
	};

	template<typename T>
	std::shared_ptr<T> TrackEvent::getInnerEvent()
	{
		if (this->_event == nullptr)
		{
			throw Exceptions::EventNotInitializedException();
		}

		return std::dynamic_pointer_cast<T>(this->_event);
	}
}