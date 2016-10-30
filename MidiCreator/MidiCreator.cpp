// MidiCreator.cpp : Defines the entry point for the console application.
//

#include "SMF\HeaderChunk.h"
#include "SMF\TrackChunk.h"
#include "SMF\StandardMIDIFile.h"

using namespace std;
using namespace SMF;

int main(int argc, char** argv[])
{
	StandardMIDIFile* smf = new StandardMIDIFile();
	HeaderChunk* hc = new HeaderChunk(FileFormat::SINGLE_TRACK, 1, 96);
	TrackChunk* tc = new TrackChunk();

	smf->setHeader(hc);
	smf->addTrackChunk(tc);
	smf->setTimeSignature(4, 4);
	smf->setTempo(120);

	//tc->setVoiceProgram(GMPatch::ELECTRIC_PIANO_2);

	//tc->setCurrentChannel(MIDIChannel::CHANNEL_2);
	//tc->setVoiceProgram(GMPatch::ORCHESTRAL_HARP);

	tc->setCurrentChannel(MIDIChannel::CHANNEL_3);
	tc->setVoiceProgram(GMPatch::BASSOON);

	Note* note = new Note(NotePitch::C3, 96, 500);

	tc->addNote(note);

	delete note;

	smf->exportToFile("magic.midi");

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
	for (size_t i = 0; i < tc_v.size(); i++) {
		cout << setfill('0') << setw(2);
		cout << uppercase << hex << (int)tc_v[i] << ' ';
		if (
			i == 3 || i == 7 || i == 15 || i == 22 || i == 25 || i == 29 || i == 33
			) cout << endl;
	}
	cout << endl;

	delete smf;

	//cout << endl << endl;
	system("pause");
    return 0;
}

