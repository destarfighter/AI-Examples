#pragma once
#include "pch.h"
#include "CppUnitTest.h"
#include "CrtCheckMemory.h"

#include "../Pathfinding/WorldObjects/WorldObject.h"
#include "../Pathfinding/WorldObjects/ProblemSolver.h"
#include "../Pathfinding/WorldObjects/PathAnimater.h"
#include "../Pathfinding/WorldObjects/Maze.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PathfindingTest
{
	TEST_CLASS(MemoryTests)
	{
	public:
		// World Objects
		TEST_METHOD(WorldObjectsYieldsNoMemoryLeak)
		{
			CrtCheckMemory memoryCheck;
			{
				auto worldObject = new WorldObject();
				delete worldObject;
			}
		}
		TEST_METHOD(ProblemSolverYieldsNoMemoryLeak)
		{
			CrtCheckMemory memoryCheck;
			{
				auto problemSolver = new ProblemSolver();
				delete problemSolver;
			}
		}
		TEST_METHOD(PathAnimaterYieldsNoMemoryLeak)
		{
			// At the moment there is an issue with sfml with sf::Texture which leads to memory leaks. This test will fail
			CrtCheckMemory memoryCheck;
			{
				auto pathAnimater = new PathAnimater();
				delete pathAnimater;
			}
		}
		TEST_METHOD(MazeYieldsNoMemoryLeak)
		{
			// At the moment there is an issue with sfml with sf::Texture which leads to memory leaks. This test will fail
			CrtCheckMemory memoryCheck;
			{
				auto maze = new Maze();
				delete maze;
			}
		}

		// Services
		TEST_METHOD(WorldStateLocatorYieldsNoMemoryLeak)
		{
			CrtCheckMemory memoryCheck;
			{
			
			}
		}

		// Semi-Primitives
		TEST_METHOD(AnimatedSpriteYieldsNoMemoryLeak)
		{
			CrtCheckMemory memoryCheck;
			{
				auto animatedSprite = new AnimatedSprite();
				delete animatedSprite;
			}
		}
		TEST_METHOD(TileMapYieldsNoMemoryLeak)
		{
			// At the moment there is an issue with sfml with sf::Texture which leads to memory leaks. This test will fail
			CrtCheckMemory memoryCheck;
			{
				auto tileMap = new TileMap();
				delete tileMap;
			}
		}

		// AI
		TEST_METHOD(AIControllerYieldsNoMemoryLeak)
		{
			CrtCheckMemory memoryCheck;
			{
				auto aiController = new AIController();
				delete aiController;
			}
		}	
	};
}