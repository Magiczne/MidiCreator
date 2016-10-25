#include "stdafx.h"
#include "CppUnitTest.h"
#include "Util.h"

#include "../MidiCreator/SMF/TrackChunk.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace SMF;
using namespace std;

namespace MidiCreatorTests
{
	TEST_CLASS(TrackChunkTests)
	{
		TEST_METHOD(ConvertingToByteCollectionWithoutTrackEvents)
		{
			TrackChunk c;

			vector<uint8_t> arr = c.toByteVector();
			vector<uint8_t> expected = {
				'M', 'T', 'r', 'k',
				0x00, 0x00, 0x00, 0x00
			};

			printByteVector("Actual: ", arr);
			printByteVector("Expected: ", expected);

			bool flag = std::equal(
				arr.begin(), arr.end(),
				expected.begin(), expected.end());

			Assert::AreEqual(true, flag);
		}

		TEST_METHOD(ConvertingToByteCollectionWithTrackEvents)
		{

		}
	};
}