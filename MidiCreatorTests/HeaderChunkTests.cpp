#include "stdafx.h"
#include "CppUnitTest.h"
#include "Util.h"

#include "../MidiCreator/SMF/HeaderChunk.h"

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
			HeaderChunk h(FileFormat::MULTIPLE_SONG);

			Assert::AreEqual(
				FileFormat::MULTIPLE_SONG,
				h.getFileFormat(), 
				L"Not Equal\n",
				LINE_INFO());
		}

		TEST_METHOD(IncrementingTrackCounter)
		{
			HeaderChunk h(FileFormat::MULTIPLE_SONG);
			short n = h.getNumberOfTracks();
			h.addTrack();

			Assert::AreEqual(
				(short)(n + 1),
				h.getNumberOfTracks(),
				L"TrackCounter is not incrementing!\n",
				LINE_INFO());
		}

		TEST_METHOD(ConvertingToByteCollection)
		{
			HeaderChunk h(FileFormat::MULTIPLE_SONG);

			vector<uint8_t> arr = h.toByteVector();
			vector<uint8_t> expected = {
				'M', 'T' ,'h', 'd', 
				0x00, 0x00, 0x00, 0x06,
				0x00, (short)FileFormat::MULTIPLE_SONG,
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
				L"Byte vectors are not the same!\n",
				LINE_INFO()
			);
		}
		
		TEST_METHOD(SettingAndGettingDivision)
		{
			HeaderChunk h(FileFormat::MULTIPLE_SONG);
			h.setDivision(96);

			Assert::AreEqual(
				(short)96,
				h.getDivision(),
				L"Division is not changing!\n",
				LINE_INFO()
			);
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
			static std::wstring ToString<FileFormat>(const FileFormat& hc)
			{
				return std::to_wstring(hc);
			}
		}
	}
}