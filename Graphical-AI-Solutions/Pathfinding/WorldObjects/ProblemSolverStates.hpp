#pragma once
#include <future>
#include "../Services/WorldStateLocator.h"
#include "../Data/ProblemPackage.h"
#include "../Data/MapPackage.h"
#include "../WorldObjects/Maze.h"
#include "../AI/Pathfinder.h"
#include "../AI/AIState.h"
#include <stdlib.h>
#include <time.h>
#include "../config.h"

// Forward Declaration of owner
class ProblemSolver;

class ProblemSolverState : public AIState {
protected:
	ProblemSolver* owner_;

public:
	ProblemSolverState(AIController* parent, ProblemSolver* owner)
		: AIState(parent)
		, owner_(owner) {};
};

/// <summary>
/// A State where we display the result of our problem solver atempt. success or failure
/// </summary>
class ShowResultState : public ProblemSolverState {
private:
	bool foundPath_;

public:
	void update(float deltaTime) override {
		// wait in state for n seconds. 
			// ask for new assignment. 
			// set State to ProblemSolving. 
	};
	void enter() override {
		// Set Animation "Celebrate" or "Cry"
	};
	void exit() override {

	};

	ShowResultState(AIController* parent, ProblemSolver* owner, bool foundPath)
		: ProblemSolverState(parent, owner)
		, foundPath_(foundPath) {};
};

/// <summary>
/// A State where we follow the path represented by an int vector. 
/// </summary>
class FollowPathState : public ProblemSolverState {
private:
	// shortest path to destination
	std::vector<unsigned int> path_;

public:
	void update(float deltaTime) override {
		// calculate movement
		// move character
		// check if at next-tile
			// change animation to face the correct direction	
			// check if at end-tile
				// set State to showResult
	};
	void enter() override {

	};
	void exit() override {

	};

	FollowPathState(AIController* parent, ProblemSolver* owner, std::vector<unsigned int> path)
		: ProblemSolverState(parent, owner)
		, path_(path) {};
};

/// <summary>
/// The State for the LittleProblemSolver where it is supposed to asynchroniously retrieve the shortest path from point A to point B. 
/// </summary>
class SolveProblemState : public ProblemSolverState {
private:
	Pathfinder pathfinder_;
	std::future<std::vector<unsigned int>> path_;
	ProblemDefinition problemDefinition_;

	ProblemDefinition generateRandomProblem(sf::Vector2f characterPosition, int mapHeight, int mapWidth, int amountOfWalls) {
		srand(time(NULL));

		// create base n x n tile
		std::vector<int> tileData(mapHeight * mapWidth, 0);

		// randomize walls locations
		for (unsigned int i = 0; i < amountOfWalls; ++i) {
			tileData[rand() % tileData.size()] = 1;
		}

		// set random destination
		int destination = rand() % tileData.size();
		sf::Vector2u newDestination(destination % 9, destination / 9);
		tileData[destination] = 3;

		// set current position to be open
		tileData[(characterPosition.y * mapWidth) + characterPosition.x] = 0;

		auto newProblem = ProblemDefinition{ MapData { sf::Vector2u(32, 32), tileData, 9, 9 }, newDestination };
		return newProblem;
	}

public:
	void update(float deltaTime) override {

		/*if (pathfinder_.getState() == IS_IDLE)
			path_ = std::async(&Pathfinder::findPath, &pathfinder_, owner_->position_, problemDefinition_.destination, problemDefinition_.mapData);

		if (pathfinder_.getState() == IS_READY) {

			if (pathfinder_.getFoundPath()) {
				parent_->setState(FollowPathState(path_.get()));
			}
			else {
				parent_->setState(ShowResultState(false));
			}
		}*/
	};

	void enter() override {
		// if no problem was provided generate a new problem
		auto problem = generateRandomProblem(owner_->position_, MAP_WIDTH, MAP_HEIGHT, AMOUNT_OF_WALLS);

		// find maze object in worlState
		WorldState* worldState = WorldStateLocator::getWorldState();
		auto mazeId = worldState->getObjectId(MAP_NAME);
		auto maze = worldState->getObject(mazeId);

		// Cast to Maze and call setMapData with problem update	
		std::static_pointer_cast<Maze>(maze)->setMapData(problem.mapData);
	};

	SolveProblemState(AIController* parent, ProblemSolver* owner, ProblemDefinition problemDefinition = {})
		: ProblemSolverState(parent, owner)
		,problemDefinition_(problemDefinition) { };
};