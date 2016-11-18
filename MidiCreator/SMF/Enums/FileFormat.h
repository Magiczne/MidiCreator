#pragma once

namespace SMF
{
	enum class FileFormat : uint8_t
	{
		SINGLE_TRACK = 0x00,
		MULTIPLE_TRACK = 0x01,
		MULTIPLE_SONG = 0x02
	};
}