#include "stdafx.h"
#include "MidiCreator.h"

int main(int argc, char** argv[])
{
	MidiCreator app;

	int exec = app.exec();

	if (exec != 0)
	{
		std::cout << std::endl;
		std::cin.get();
	}

    return exec;
}