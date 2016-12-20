#include "stdafx.h"
#include "CppUnitTest.h"
#include "Util.h"

#include "../MidiCreator/Util/CRC32.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace MidiCreatorTests
{
	TEST_CLASS(CRCTests)
	{
		TEST_METHOD(CRCFromVector)
		{
			CRC32<> crc;
			CRC32<> crc2;

			uint8_t arr[6] = {
				'M', 'C', 'F', 'F',
				0x01, 0x00
			};

			std::vector<uint8_t> header = {
				'M', 'C', 'F', 'F',
				0x01, 0x00
			};

			crc.update(header);
			auto checksum = static_cast<uint32_t>(crc);
			printHex(checksum);
			Logger::WriteMessage("\n");

			crc2.update(arr, 6);
			auto checksum2 = static_cast<uint32_t>(crc2);
			printHex(checksum);

			Assert::AreEqual(checksum, checksum2);
		}
	};
}