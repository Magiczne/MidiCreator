#include "stdafx.h"
#include "CppUnitTest.h"
#include "Util.h"

#include "../MidiCreator/SMF/HeaderChunk.h"
#include "../MidiCreator/SMF/Util/Maps.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace SMF;
using namespace std;

namespace MidiCreatorTests
{		
	TEST_CLASS(HeaderChunkTests)
	{
	public:
		
		TEST_METHOD(FileFormatConstructor)
		{
			HeaderChunk h(FileFormat::MULTIPLE_SONG, 0, 0);

			Assert::AreEqual(
				FileFormat::MULTIPLE_SONG,
				h.fileFormat(), 
				L"Not Equal\n");
		}

		TEST_METHOD(IncrementingTrackCounter)
		{
			HeaderChunk h(FileFormat::MULTIPLE_SONG, 0, 0);
			short n = h.numberOfTracks();
			h.addTrack();

			Assert::AreEqual(
				static_cast<short>(n + 1),
				h.numberOfTracks(),
				L"TrackCounter is not incrementing!\n");
		}

		TEST_METHOD(ConvertingToByteCollection)
		{
			HeaderChunk h(FileFormat::MULTIPLE_SONG, 0, 0);

			vector<uint8_t> arr = h.toByteVector();
			vector<uint8_t> expected = {
				'M', 'T' ,'h', 'd', 
				0x00, 0x00, 0x00, 0x06,
				0x00, static_cast<short>(FileFormat::MULTIPLE_SONG),
				0x00, 0x00,
				0x00, 0x00
			};

			printByteVector("Actual: ", arr);
			printByteVector("Expected: ", expected);

			bool flag = std::equal(
				arr.begin(), arr.end(), 
				expected.begin(), expected.end());

			Assert::AreEqual(
				true,
				flag,
				L"Byte vectors are not the same!\n");
		}
		
		TEST_METHOD(SettingAndGettingDivision)
		{
			HeaderChunk h(FileFormat::MULTIPLE_SONG, 0, 0);
			h.division(96);

			Assert::AreEqual(
				static_cast<short>(96),
				h.division(),
				L"Division is not changing!\n");
		}
	};
}

namespace Microsoft
{
	namespace VisualStudio
	{
		namespace CppUnitTestFramework
		{
			template<>
			static std::wstring ToString<FileFormat>(const FileFormat& ff)
			{
				auto str = FileFormatMap[ff];
				return wstring(str.begin(), str.end());
			}
		}
	}
}