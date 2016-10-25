#include "stdafx.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MidiCreatorTests
{
	static void printByteVector(string name, vector<uint8_t>& arr)
	{
		stringstream stream;
		stream << name << endl;

		for (auto &v : arr)
		{
			stream << setfill('0') << setw(2);
			stream << hex << (int)v << ' ';
		}

		stream << endl;

		string s = stream.str();

		Logger::WriteMessage(s.c_str());
	}
}