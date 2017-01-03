#include "MetaEvent.h"

#include "../Exceptions/EventNotInitializedException.h"

using namespace SMF;
using namespace SMF::Exceptions;

MetaEvent::MetaEvent(MetaEventType eventType) : type(eventType)
{
	this->initialized = { true };
}

MetaEvent::~MetaEvent()
{
	delete this->vLength;
}

MetaEvent* MetaEvent::setEventType(MetaEventType eventType)
{
	this->type = eventType;
	this->initialized[0] = true;
	return this;
}

MetaEvent* MetaEvent::setLength(int length)
{
	this->vLength = new VLQ(length);
	this->initialized[1] = true;
	return this;
}

std::vector<uint8_t> MetaEvent::toByteVector()
{
#ifdef METHOD_DEBUG
	std::cout << "MetaEvent::toByteVector()" << std::endl;
#endif // METHOD_DEBUG	

	if (!this->isInitialized())
	{
		throw EventNotInitializedException();
	}

	std::vector<uint8_t> ret;

	ret.push_back(this->id);
	ret.push_back(static_cast<uint8_t>(this->type));

	//vLength
	std::vector<uint8_t> vLengthBytes = this->vLength->getVlq();
	ret.insert(ret.end(), vLengthBytes.begin(), vLengthBytes.end());

	//Params
	ret.insert(ret.end(), this->params.begin(), this->params.end());

	return ret;
}

bool MetaEvent::isInitialized()
{
	for (auto& i : this->initialized)
	{
		if (!i)
		{
			return false;
		}
	}
	return true;
}