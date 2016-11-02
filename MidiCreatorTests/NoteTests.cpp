#include "stdafx.h"
#include "CppUnitTest.h"

#include "../MidiCreator/SMF/Util/Note.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace SMF;
using namespace std;

namespace MidiCreatorTests
{
	TEST_CLASS(NoteTests)
	{
		//Not optimal. But works. :D
		static int getRandom(int min, int max)
		{
			random_device dev;
			mt19937 generator(dev());
			uniform_int_distribution<int> dist(min, max);

			return dist(generator);
		}

		TEST_METHOD(ConstructorAndGetters)
		{
			Note* n = new Note(NotePitch::A1, 150, 55);

			bool flag =
				n->getPitch() == NotePitch::A1 &&
				n->getVolume() == 150 &&
				n->getDuration() == 55;

			Assert::AreEqual(true, flag);

			delete n;
		}

		TEST_METHOD(SmallerThanOperator)
		{
			for (int i = 0; i < 15; i++)
			{
				int rnd = getRandom(0, 100);
				int rnd2 = getRandom(0, 100);

				Note* n = new Note(NotePitch::A0, 150, rnd);
				Note* m = new Note(NotePitch::A0, 150, rnd2);

				Logger::WriteMessage("n.duration = ");
				Logger::WriteMessage(to_string(n->getDuration()).c_str());
				Logger::WriteMessage("\nm.duration = ");
				Logger::WriteMessage(to_string(m->getDuration()).c_str());

				bool flag = *n < *m;
				bool expected = rnd < rnd2;

				Logger::WriteMessage("\nn < m = ");
				Logger::WriteMessage(flag ? "true\n\n" : "false\n\n");

				Assert::AreEqual(expected, flag);

				delete n, m;
			}
		}

		TEST_METHOD(GreaterThanOperator)
		{
			for (int i = 0; i < 15; i++)
			{
				int rnd = getRandom(0, 100);
				int rnd2 = getRandom(0, 100);

				Note* n = new Note(NotePitch::A0, 150, rnd);
				Note* m = new Note(NotePitch::A0, 150, rnd2);

				Logger::WriteMessage("n.duration = ");
				Logger::WriteMessage(to_string(n->getDuration()).c_str());
				Logger::WriteMessage("\nm.duration = ");
				Logger::WriteMessage(to_string(m->getDuration()).c_str());

				bool flag = *n > *m;
				bool expected = rnd > rnd2;

				Logger::WriteMessage("\nn > m = ");
				Logger::WriteMessage(flag ? "true\n\n" : "false\n\n");

				Assert::AreEqual(expected, flag);

				delete n, m;
			}
		}

		TEST_METHOD(SmallerOrEqualThanOperator)
		{
			Note* n = new Note(NotePitch::A0, 150, 55);
			Note* m = new Note(NotePitch::A0, 150, 55);

			Logger::WriteMessage("n.duration = ");
			Logger::WriteMessage(to_string(n->getDuration()).c_str());
			Logger::WriteMessage("\nm.duration = ");
			Logger::WriteMessage(to_string(m->getDuration()).c_str());

			bool flag = *n <= *m;

			Logger::WriteMessage("\nn <= m = ");
			Logger::WriteMessage(flag ? "true\n\n" : "false\n\n");

			Assert::AreEqual(true, flag);

			for (int i = 0; i < 14; i++)
			{
				int rnd = getRandom(0, 100);
				int rnd2 = getRandom(0, 100);

				Note* n = new Note(NotePitch::A0, 150, rnd);
				Note* m = new Note(NotePitch::A0, 150, rnd2);

				Logger::WriteMessage("n.duration = ");
				Logger::WriteMessage(to_string(n->getDuration()).c_str());
				Logger::WriteMessage("\nm.duration = ");
				Logger::WriteMessage(to_string(m->getDuration()).c_str());

				bool flag = *n <= *m;
				bool expected = rnd <= rnd2;

				Logger::WriteMessage("\nn <= m = ");
				Logger::WriteMessage(flag ? "true\n\n" : "false\n\n");

				Assert::AreEqual(expected, flag);

				delete n, m;
			}

			delete n, m;
		}

		TEST_METHOD(GreaterOrEqualThanOperator)
		{
			Note* n = new Note(NotePitch::A0, 150, 55);
			Note* m = new Note(NotePitch::A0, 150, 55);

			Logger::WriteMessage("n.duration = ");
			Logger::WriteMessage(to_string(n->getDuration()).c_str());
			Logger::WriteMessage("\nm.duration = ");
			Logger::WriteMessage(to_string(m->getDuration()).c_str());

			bool flag = *n >= *m;

			Logger::WriteMessage("\nn >= m = ");
			Logger::WriteMessage(flag ? "true\n\n" : "false\n\n");

			Assert::AreEqual(true, flag);

			for (int i = 0; i < 14; i++)
			{
				int rnd = getRandom(0, 100);
				int rnd2 = getRandom(0, 100);

				Note* n = new Note(NotePitch::A0, 150, rnd);
				Note* m = new Note(NotePitch::A0, 150, rnd2);

				Logger::WriteMessage("n.duration = ");
				Logger::WriteMessage(to_string(n->getDuration()).c_str());
				Logger::WriteMessage("\nm.duration = ");
				Logger::WriteMessage(to_string(m->getDuration()).c_str());

				bool flag = *n >= *m;
				bool expected = rnd >= rnd2;

				Logger::WriteMessage("\nn <= m = ");
				Logger::WriteMessage(flag ? "true\n\n" : "false\n\n");

				Assert::AreEqual(expected, flag);

				delete n, m;
			}

			delete n, m;
		}

		TEST_METHOD(EqualsOperator)
		{
			Note* n = new Note(NotePitch::C4, 55, 55);
			Note* m = new Note(NotePitch::C5, 55, 55);

			Assert::AreEqual(false, *n == *m);

			for (int i = 0; i < 14; i++)
			{
				int dur = getRandom(1, 100);
				int vol = getRandom(1, 100);
				int pitch = getRandom(0, 127);

				Note* n = new Note(NotePitch(pitch), dur, vol);
				Note* m = new Note(NotePitch(pitch), dur, vol);

				Assert::AreEqual(true, *n == *m);

				delete n, m;
			}

			delete n, m;
		}

		TEST_METHOD(NotEqualsOperator)
		{
			Note* n = new Note(NotePitch::C5, 55, 55);
			Note* m = new Note(NotePitch::C5, 55, 55);

			Assert::AreEqual(false, *n != *m);

			for (int i = 0; i < 14; i++)
			{
				int dur = getRandom(1, 100);
				int vol = getRandom(1, 100);
				int pitch = getRandom(0, 120);

				Note* n = new Note(NotePitch(pitch), dur, vol);
				Note* m = new Note(NotePitch(pitch + 7), dur + 3, vol + 1);

				Assert::AreEqual(true, *n != *m);

				delete n, m;
			}

			delete n, m;
		}
	};
}