#pragma once

#include "../stdafx.h"
#include "../Interfaces/IConvertibleToByteArray.h"

namespace SMF
{
	class HeaderChunk :
		IConvertibleToByteArray
	{
	public:
		HeaderChunk();
		~HeaderChunk();
	};
}

