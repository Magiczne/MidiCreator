#include "MetaEvent.h"

#include "../Exceptions/EventNotInitializedException.h"

using namespace SMF;
using namespace SMF::Exceptions;

MetaEvent::MetaEvent(MetaEventType eventType) : _type(eventType)
{
	this->_initialized = { true };
}

MetaEvent::~MetaEvent()
{
	delete this->_vLength;
}

MetaEvent* MetaEvent::setEventType(MetaEventType eventType)
{
	this->_type = eventType;
	this->_initialized[0] = true;
	return this;
}

MetaEvent* MetaEvent::setLength(int length)
{
	this->_vLength = new VLQ(length);
	this->_initialized[1] = true;
	return this;
}

std::vector<uint8_t> MetaEvent::toByteVector() const
{
#ifdef METHOD_DEBUG
	std::cout << "MetaEvent::toByteVector()" << std::endl;
#endif // METHOD_DEBUG	

	if (!this->isInitialized())
	{
		throw EventNotInitializedException();
	}

	std::vector<uint8_t> ret;

	ret.push_back(this->_id);
	ret.push_back(static_cast<uint8_t>(this->_type));

	//vLength
	std::vector<uint8_t> vLengthBytes = this->_vLength->getVlq();
	ret.insert(ret.end(), vLengthBytes.begin(), vLengthBytes.end());

	//Params
	ret.insert(ret.end(), this->params.begin(), this->params.end());

	return ret;
}

bool MetaEvent::isInitialized() const
{
	for (const auto& i : this->_initialized)
	{
		if (!i)
		{
			return false;
		}
	}
	return true;
}