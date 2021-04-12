#include "pch.h"
#include "CppUnitTest.h"
#include "CrtCheckMemory.h"
#include "../Pathfinding/AI/Pathfinder.h"
#include "../Pathfinding/Data/ProblemPackage.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PathfindingTest
{
	TEST_CLASS(PathfinderTest)
	{
	public:
		TEST_METHOD(PathfinderFindsCorrectPathForBasicMap)
		{
			// Create problem
			std::vector<int> tileMap = { 1, 1, 1, 1,
										 0, 1, 0, 1,
										 0, 1, 1, 1 };

			MapData map = {
				sf::Vector2u(32, 32),
				tileMap,
				4,
				3
			};

			sf::Vector2f startPosition(0.f, 0.f);
			sf::Vector2u destination(1.f, 2.f);

			// Find path
			auto pathfinder = Pathfinder();
			auto result = pathfinder.findPath(startPosition, destination, map);

			// Check result
			Assert::AreEqual(result.size(), static_cast<size_t>(3));
			Assert::AreEqual(result[0], static_cast<unsigned long>(1));
			Assert::AreEqual(result[1], static_cast<unsigned long>(5));
			Assert::AreEqual(result[2], static_cast<unsigned long>(9));
		}

		TEST_METHOD(PathfinderFindsNoPathReturnsEmptyVector) {
			// Create problem
			std::vector<int> tileMap = { 0, 0, 1,
										 0, 1, 1,
										 1, 0, 1 };

			MapData map = {
				sf::Vector2u(32, 32),
				tileMap,
				3,
				3
			};

			sf::Vector2f startPosition(2.f, 0.f);
			sf::Vector2u destination(0.f, 2.f);

			// Find path
			auto pathfinder = Pathfinder();
			auto result = pathfinder.findPath(startPosition, destination, map);

			// Check result
			Assert::AreEqual(result.size(), static_cast<size_t>(0));
		}
	};
}