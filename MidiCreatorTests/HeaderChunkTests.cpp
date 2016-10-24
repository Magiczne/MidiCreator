#include "stdafx.h"
#include "CppUnitTest.h"

#include "../MidiCreator/SMF/HeaderChunk.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace SMF;

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

		TEST_METHOD(AddTrackMethod)
		{
			Logger::WriteMessage("Magic");
			HeaderChunk h(FileFormat::MULTIPLE_SONG);
			short n = h.getNumberOfTracks();
			h.addTrack();

			Assert::AreEqual(
				(short)(n + 1),
				h.getNumberOfTracks(),
				L"TrackCounter is not incrementing!\n",
				LINE_INFO());
		}

		TEST_METHOD(ToByteArrayMethod)
		{
			HeaderChunk h(FileFormat::MULTIPLE_SONG);

			byte* arr = h.toByteArray();
			byte* expected = new byte[14]{
				'M', 'T' ,'h', 'd', 
				0x00, 0x00, 0x00, 0x06,
				0x00, (short)FileFormat::MULTIPLE_SONG,
				0x00, 0x00,
				0x00, 0x00
			};

			printByteArray("Actual: ", arr, 14);
			printByteArray("Expected: ", expected, 14);

			bool flag = true;

			for (size_t i = 0; i < 14; i++)
			{
				if (arr[i] != expected[i]) 
				{
					flag = false;
					break;
				}
			}

			Assert::AreEqual(
				true,
				flag,
				L"Byte arrays are not the same!\n",
				LINE_INFO()
			);
		}

		static void printByteArray(std::string name, byte* arr, size_t size)
		{
			using namespace std;

			stringstream stream;
			stream << name << endl;

			for (size_t i = 0; i < size; i++)
			{
				stream << setfill('0') << setw(2);
				stream << hex << (int)arr[i] << ' ';
			}

			stream << endl;

			string s = stream.str();

			Logger::WriteMessage(s.c_str());
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