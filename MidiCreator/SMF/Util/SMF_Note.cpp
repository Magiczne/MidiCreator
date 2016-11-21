#include "../../stdafx.h"
#include "SMF_Note.h"

using namespace SMF;

/*
pitch	-> C_MINUS_ONE - G9
volume	-> 0-255
*/
Note::Note(NotePitch pitch, uint8_t volume, int duration)
	: _pitch(pitch), _volume(volume), _duration(duration) {}