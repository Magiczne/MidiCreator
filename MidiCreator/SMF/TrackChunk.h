#pragma once

#include "../stdafx.h"
#include "../Interfaces/IConvertibleToByteArray.h"

namespace SMF 
{
	class TrackChunk : 
		IConvertibleToByteArray
	{
	public:
		TrackChunk();
		~TrackChunk();
	};
}

