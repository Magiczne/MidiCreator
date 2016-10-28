#pragma once

#include "../../stdafx.h"
#include "../StandardMIDIFile.h"

using namespace std;

namespace SMF
{
	class BpmOutOfRangeException :
		public exception
	{
		virtual const char* what() const throw()
		{
			string msg = "BPM out of range! ("
				+ to_string(StandardMIDIFile::MIN_BPM)
				+ " - "
				+ to_string(StandardMIDIFile::MAX_BPM)
				+ ")";

			return msg.c_str();
		}
	};
}