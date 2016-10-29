#include "MetaEvent.h"

using namespace SMF;

MetaEvent* MetaEvent::setEventType(MetaEventType eventType)
{
	this->type = eventType;
	return this;
}

MetaEvent* MetaEvent::setLength(int length)
{
	this->vLength = new VLQ(length);
	return this;
}

std::vector<uint8_t> MetaEvent::toByteVector()
{
	std::vector<uint8_t> ret;

	ret.push_back(this->id);
	ret.push_back(this->type);

	//vLength
	std::vector<uint8_t> vLengthBytes = this->vLength->getVlq();
	ret.insert(ret.end(), vLengthBytes.begin(), vLengthBytes.end());

	//Params
	ret.insert(ret.end(), this->params.begin(), this->params.end());

	#ifdef DEBUG
		std::cout << "MetaEvent::toByteVector()" << std::endl;
	#endif // DEBUG	

	return ret;
}

MetaEvent::~MetaEvent()
{
	delete this->vLength;
}