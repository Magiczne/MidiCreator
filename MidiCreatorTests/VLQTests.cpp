#include "stdafx.h"
#include "CppUnitTest.h"

#include "../MidiCreator/Util/VLQ.h"
#include "Util.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MidiCreatorTests
{
	TEST_CLASS(VLQTests)
	{
		TEST_METHOD(ConvertFromIntToVLQ)
		{
			VLQ vlq(0x08000000);
			auto res = vlq.getVlq();

			std::vector<uint8_t> expected = { 0xC0, 0x80, 0x80, 0x00 };

			Logger::WriteMessage("Integer: 0x08000000\n");
			printByteVector("Actual: ", res);
			printByteVector("Expected: ", expected);

			bool flag = std::equal(
				res.begin(), res.end(),
				expected.begin(), expected.end());

			Assert::AreEqual(true, flag);
		}

		TEST_METHOD(ConvertFromVQLToInt)
		{
			std::vector<uint8_t> vec = { 0xFF, 0xFF, 0xFF, 0x7F };
			VLQ vlq(vec);
			auto res = vlq.getInt();

			unsigned long expected = 0x0FFFFFFF;

			Logger::WriteMessage("Integer: 0x0FFFFFFF\n");

			Assert::AreEqual(res, expected);
		}
	};
}