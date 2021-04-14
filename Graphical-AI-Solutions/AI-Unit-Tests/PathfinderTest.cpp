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
		#define MAP_WALLS std::vector<unsigned int> {1}

	public:
		TEST_METHOD(PathfinderFindsCorrectPathForBasicMap)
		{
			// Create problem
			std::vector<int> tileMap = { 2, 0, 0, 0,
										 1, 0, 1, 0,
										 1, 3, 0, 0 };

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
			std::vector<int> tileMap = { 1, 1, 0,
										 1, 0, 0,
										 3, 1, 2 };

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

		TEST_METHOD(PathfinderFindsOptimalPathAvoidingGreedySolution)
		{
			// Create problem
			std::vector<int> tileMap = { 0, 0, 0, 1, 0,
										 2, 0, 0, 1, 3,
										 0, 0, 0, 1, 0,
										 0, 1, 1, 1, 0,
										 0, 0, 0, 0, 0 };

			MapData map = {
				sf::Vector2u(32, 32),
				tileMap,
				5,
				5
			};

			sf::Vector2f startPosition(0.f, 1.f);
			sf::Vector2u destination(4.f, 1.f);

			// Find path
			auto pathfinder = Pathfinder();
			auto result = pathfinder.findPath(startPosition, destination, map);

			// Check result
			Assert::AreEqual(result.size(), static_cast<size_t>(11));
			Assert::AreEqual(result[0], static_cast<unsigned long>(5));
			Assert::AreEqual(result[1], static_cast<unsigned long>(10));
			Assert::AreEqual(result[2], static_cast<unsigned long>(15));
			Assert::AreEqual(result[3], static_cast<unsigned long>(20));
			Assert::AreEqual(result[4], static_cast<unsigned long>(21));
			Assert::AreEqual(result[5], static_cast<unsigned long>(22));
			Assert::AreEqual(result[6], static_cast<unsigned long>(23));
			Assert::AreEqual(result[7], static_cast<unsigned long>(24));
			Assert::AreEqual(result[8], static_cast<unsigned long>(19));
			Assert::AreEqual(result[9], static_cast<unsigned long>(14));
			Assert::AreEqual(result[10], static_cast<unsigned long>(9));
		}
	};
}