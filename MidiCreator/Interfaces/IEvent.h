#pragma once

namespace SMF
{
	class IEvent 
	{
	public:
		virtual ~IEvent() = 0;	//To not instantiate IEvent somewhere
	};
}