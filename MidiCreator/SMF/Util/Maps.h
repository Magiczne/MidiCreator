#pragma once

#include "..\..\stdafx.h"
#include "..\Enums\FileFormat.h"
#include "..\Enums\NotePitch.h"

using namespace std;

namespace SMF
{
	static map<FileFormat, string> FileFormatMap = 
	{
		{ FileFormat::SINGLE_TRACK, "Single track" },
		{ FileFormat::MULTIPLE_TRACK, "Multiple tracks" },
		{ FileFormat::MULTIPLE_SONG, "Multiple songs" }
	};

	static map<NotePitch, string> NotePitchMap = 
	{
		//Octave -1
		{ NotePitch::C_MINUS_1, "C-1" },
		{ NotePitch::C_MINUS_1_SHARP, "C#-1" },
		{ NotePitch::D_MINUS_1, "D-1" },
		{ NotePitch::D_MINUS_1_SHARP, "Eb-1" },
		{ NotePitch::E_MINUS_1, "E-1" },
		{ NotePitch::F_MINUS_1, "F-1" },
		{ NotePitch::F_MINUS_1_SHARP, "F-1" },
		{ NotePitch::G_MINUS_1, "G-1" },
		{ NotePitch::G_MINUS_1_SHARP, "G#-1" },
		{ NotePitch::A_MINUS_1, "A-1" },
		{ NotePitch::A_MINUS_1_SHARP , "Bb-1" },
		{ NotePitch::B_MINUS_1 , "B-1" },

		//Octave 2
		{ NotePitch::C0, "C0" },
		{ NotePitch::C0_SHARP, "C#0" },
		{ NotePitch::D0, "D0" },
		{ NotePitch::D0_SHARP, "Eb0" },
		{ NotePitch::E0, "E0" },
		{ NotePitch::F0, "F0" },
		{ NotePitch::F0_SHARP, "F#0" },
		{ NotePitch::G0, "G0" },
		{ NotePitch::G0_SHARP, "G#0" },
		{ NotePitch::A0, "A0" },
		{ NotePitch::A0_SHARP, "Bb0" },
		{ NotePitch::B0, "B0" },
		
		//Octave 1
		{ NotePitch::C1, "C1" },
		{ NotePitch::C1_SHARP, "C#1" },
		{ NotePitch::D1, "D1" },
		{ NotePitch::D1_SHARP, "Eb1" },
		{ NotePitch::E1, "E1" },
		{ NotePitch::F1, "F1" },
		{ NotePitch::F1_SHARP, "F#1" },
		{ NotePitch::G1, "G1" },
		{ NotePitch::G1_SHARP, "G#1" },
		{ NotePitch::A1, "A1" },
		{ NotePitch::A1_SHARP, "Bb1" },
		{ NotePitch::B1, "B1" },

		//Octave 2
		{ NotePitch::C2, "C2" },
		{ NotePitch::C2_SHARP, "C#2" },
		{ NotePitch::D2, "D2" },
		{ NotePitch::D2_SHARP, "Eb2" },
		{ NotePitch::E2, "E2" },
		{ NotePitch::F2, "F2" },
		{ NotePitch::F2_SHARP, "F#2" },
		{ NotePitch::G2, "G2" },
		{ NotePitch::G2_SHARP, "G#2" },
		{ NotePitch::A2, "A2" },
		{ NotePitch::A2_SHARP, "Bb2" },
		{ NotePitch::B2, "B2" },

		//Octave 3
		{ NotePitch::C3, "C3" },
		{ NotePitch::C3_SHARP, "C#3" },
		{ NotePitch::D3, "D3" },
		{ NotePitch::D3_SHARP, "Eb3" },
		{ NotePitch::E3, "E3" },
		{ NotePitch::F3, "F3" },
		{ NotePitch::F3_SHARP, "F#3" },
		{ NotePitch::G3, "G3" },
		{ NotePitch::G3_SHARP, "G#3" },
		{ NotePitch::A3, "A3" },
		{ NotePitch::A3_SHARP, "Bb3" },
		{ NotePitch::B3, "B3" },

		//Octave 4
		{ NotePitch::C4, "C4" },
		{ NotePitch::C4_SHARP, "C#4" },
		{ NotePitch::D4, "D4" },
		{ NotePitch::D4_SHARP, "Eb4" },
		{ NotePitch::E4, "E4" },
		{ NotePitch::F4, "F4" },
		{ NotePitch::F4_SHARP, "F#4" },
		{ NotePitch::G4, "G4" },
		{ NotePitch::G4_SHARP, "G#4" },
		{ NotePitch::A4, "A4" },
		{ NotePitch::A4_SHARP, "Bb4" },
		{ NotePitch::B4, "B4" },

		//Octave 5
		{ NotePitch::C5, "C5" },
		{ NotePitch::C5_SHARP, "C#5" },
		{ NotePitch::D5, "D5" },
		{ NotePitch::D5_SHARP, "Eb5" },
		{ NotePitch::E5, "E5" },
		{ NotePitch::F5, "F5" },
		{ NotePitch::F5_SHARP, "F#5" },
		{ NotePitch::G5, "G5" },
		{ NotePitch::G5_SHARP, "G#5" },
		{ NotePitch::A5, "A5" },
		{ NotePitch::A5_SHARP, "Bb5" },
		{ NotePitch::B5, "B5" },

		//Octave 6
		{ NotePitch::C6, "C6" },
		{ NotePitch::C6_SHARP, "C#6" },
		{ NotePitch::D6, "D6" },
		{ NotePitch::D6_SHARP, "Eb6" },
		{ NotePitch::E6, "E6" },
		{ NotePitch::F6, "F6" },
		{ NotePitch::F6_SHARP, "F#6" },
		{ NotePitch::G6, "G6" },
		{ NotePitch::G6_SHARP, "G#6" },
		{ NotePitch::A6, "A6" },
		{ NotePitch::A6_SHARP, "Bb6" },
		{ NotePitch::B6, "B6" },

		//Octave 7
		{ NotePitch::C7, "C7" },
		{ NotePitch::C7_SHARP, "C#7" },
		{ NotePitch::D7, "D7" },
		{ NotePitch::D7_SHARP, "Eb7" },
		{ NotePitch::E7, "E7" },
		{ NotePitch::F7, "F7" },
		{ NotePitch::F7_SHARP, "F#7" },
		{ NotePitch::G7, "G7" },
		{ NotePitch::G7_SHARP, "G#7" },
		{ NotePitch::A7, "A7" },
		{ NotePitch::A7_SHARP, "Bb7" },
		{ NotePitch::B7, "B7" },

		//Octave 8
		{ NotePitch::C8, "C8" },
		{ NotePitch::C8_SHARP, "C#8" },
		{ NotePitch::D8, "D8" },
		{ NotePitch::D8_SHARP, "Eb8" },
		{ NotePitch::E8, "E8" },
		{ NotePitch::F8, "F8" },
		{ NotePitch::F8_SHARP, "F#8" },
		{ NotePitch::G8, "G8" },
		{ NotePitch::G8_SHARP, "G#8" },
		{ NotePitch::A8, "A8" },
		{ NotePitch::A8_SHARP, "Bb8" },
		{ NotePitch::B8, "B8" },

		//Octave 9
		{ NotePitch::C9, "C9" },
		{ NotePitch::C9_SHARP, "C#9" },
		{ NotePitch::D9, "D9" },
		{ NotePitch::D9_SHARP, "Eb9" },
		{ NotePitch::E9, "E9" },
		{ NotePitch::F9, "F9" },
		{ NotePitch::F9_SHARP, "F#9" },
		{ NotePitch::G9, "G9" }
	};
}
