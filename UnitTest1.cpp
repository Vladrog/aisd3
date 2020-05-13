#include "pch.h"
#include "CppUnitTest.h"
#include "C:\Users\vlad-\source\repos\AisdNew\AisdNew\towns.h"
#include "C:\Users\vlad-\source\repos\AisdNew\AisdNew\edges.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
Assert assert;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(townsFindPositionWithElement)
		{
			towns* townList = new towns;
			townList->pushBack("Moscow");
			assert.AreEqual(townList->findPosition("Moscow"), 0);
			delete townList;
		}

		TEST_METHOD(townsFindPositionWithNoElement)
		{
			towns* townList = new towns;
			townList->pushBack("Moscow");
			assert.AreEqual(townList->findPosition("Saint Petersburg"), -1);
		}

		TEST_METHOD(townsSetStartTown)
		{
			towns* townList = new towns;
			townList->pushBack("Moscow");
			townList->pushBack("Saint Petersburg");
			townList->setStartTown(1);
			assert.AreEqual(townList->findPosition("Saint Petersburg"), 0);
		}

		TEST_METHOD(townsGetName)
		{
			towns* townList = new towns;
			string name = "Moscow";
			townList->pushBack(name);
			assert.AreEqual(townList->getName(0), name);
		}

		TEST_METHOD(edgesGetIterator)
		{
			edges* edgesList = new edges;
			int from, to, cost;
			edgesList->pushBack(0, 1, 10);
			edgesList->pushBack(1, 2, 20);
			edgesList->refreshIterator();
			edgesList->iteration();
			edgesList->getIterator(from, to, cost);
			assert.AreEqual(cost, 20);
		}
	};
}
