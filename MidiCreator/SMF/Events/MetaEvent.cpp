#include "MetaEvent.h"

using namespace SMF;

MetaEvent::MetaEvent()
{
}

MetaEvent* MetaEvent::setEventType(MetaEventType eventType)
{
	this->type = eventType;
	return this;
}

MetaEvent* MetaEvent::setLength(int val)
{
	this->vLength = val;
	return this;
}

std::vector<uint8_t> MetaEvent::toByteVector()
{
	std::vector<uint8_t> ret;

	ret.push_back(this->id);
	ret.push_back(this->type);
	//TODO: push_back values by var-Length int
	ret.insert(ret.end(), this->params.begin(), this->params.end());

	return ret;
}

MetaEvent::~MetaEvent()
{
}