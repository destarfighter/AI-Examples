#include "pch.h"
#include "CppUnitTest.h"
#include "../Pathfinding/Pathfinder.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Pathfinding
{
	TEST_CLASS(Pathfinder_TEST)
	{
	public:
		
		TEST_METHOD(findpath_IS_0)
		{
			auto pf = Pathfinder();
			int result = pf.findPath();
			Assert::AreEqual(result, 0);
		}

		TEST_METHOD(findpath_IS_NOT_1)
		{
			auto pf = Pathfinder();
			int result = pf.findPath();
			Assert::AreNotEqual(result, 1);
		}
	};
}