#include "SequenceFile.h"
#include "Sequence.h"

SequenceFile SequenceFile::fromSequence(Sequence& seq)
{
	SequenceFile file;

	#pragma region Basic Sequence Data

	file.name = seq._name;;
	file.nameLength = file.name.length();
	file.fileFormat = static_cast<uint8_t>(seq._format);
	file.numerator = seq._numerator;
	file.denominator = seq._denominator;
	
	#pragma endregion

	for(auto& map : seq._notes)
	{
		for(auto& pair : map)
		{
			for(auto& note : pair.second)
			{
				//TODO: Get note values and push to data
			}
		}
	}

	//TODO: Calculate things for FileHeader

	return file;
}