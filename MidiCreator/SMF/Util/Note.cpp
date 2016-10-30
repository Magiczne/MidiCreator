#include "../../stdafx.h"
#include "Note.h"

using namespace SMF;

/*
pitch	-> C_MINUS_ONE - G9
volume	-> 0-255
*/
Note::Note(NotePitch pitch, uint8_t volume, int duration)
	: pitch(pitch), volume(volume), duration(duration)
{

}