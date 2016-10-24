// MidiCreator.cpp : Defines the entry point for the console application.
//

#include "SMF\HeaderChunk.h"

int main(int argc, char** argv[])
{
	auto hc = SMF::HeaderChunk(SMF::FileFormat::MULTIPLE_SONG);

	//std::vector<byte> arr = hc.toByteVector();
	byte* arr = hc.toByteArray();

	for (size_t i = 0; i < 14; i++)
	{
		using namespace std;

		cout << setfill('0') << setw(2);
		cout << hex << (int)arr[i] << ' ';
	}

	system("pause");
    return 0;
}

