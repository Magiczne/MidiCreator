// MidiCreator.cpp : Defines the entry point for the console application.
//

#include "SMF\HeaderChunk.h"
#include "SMF\TrackChunk.h"

using namespace std;
using namespace SMF;

int main(int argc, char** argv[])
{
	/*
	Vector to file
	std::ofstream os{ "binaryfile.bin", std::ios::out };
	std::copy(std::begin(m), std::end(m),
		std::ostream_iterator<uint8_t>(os)); 
	os.close();
	*/

	HeaderChunk* hc = new HeaderChunk(FileFormat::SINGLE_TRACK, 1, 96);
	TrackChunk* tc = new TrackChunk();

	auto hc_v = hc->toByteVector();
	auto tc_v = tc->toByteVector();

	cout << "Header Chunk: " << endl;
	for (int i = 0; i < 14; i++) {
		cout << setfill('0') << setw(2);
		cout << uppercase << hex << (int)hc_v[i] << ' ';
		if (i == 3 || i == 7 || (i > 8 && i % 2)) cout << endl;
	}
	cout << endl;

	cout << "Track Chunk: " << endl;
	for (int i = 0; i < tc_v.size(); i++) {
		cout << setfill('0') << setw(2);
		cout << uppercase << hex << (int)tc_v[i] << ' ';
		if (i == 3 || i == 7) cout << endl;
	}
	cout << endl;

	tc->reopenTrack();

	auto innerEvent = tc
		->addTrackEvent(EventType::META_EVENT)
		->setDeltaTime(0)
		->getInnerEvent<MetaEvent>()
		->setEventType(MetaEventType::TIME_SIGNATURE)
		->setLength(4)
		->addParam(6)
		->addParam((uint8_t)log2(8))
		->addParam(36)
		->addParam(8);

	auto x = innerEvent->toByteVector();

	cout << "Meta event: " << endl;
	for (size_t i = 0; i < x.size(); i++)
	{
		cout << setfill('0') << setw(2);
		cout << uppercase << hex << (int)x[i] << ' ';
	}

	delete hc;
	delete tc;

	cout << endl << endl;
	system("pause");
    return 0;
}

