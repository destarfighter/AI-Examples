#include "pch.h"
#include "CppUnitTest.h"
#include "../Graphical-AI-Solutions/Pathfinder.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace AIUnitTests
{
	TEST_CLASS(Pathfinder_Tester)
	{
	public:
		
		TEST_METHOD(findpath_Tester)
		{
			auto pf = Pathfinder();
			int result = pf.findPath();
			Assert::AreEqual(result, 0);
		}

		TEST_METHOD(findpath_Tester_TWO)
		{
			auto pf = Pathfinder();
			int result = pf.findPath();
			Assert::AreNotEqual(result, 1);
		}
	};
}
