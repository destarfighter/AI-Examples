#pragma once
#include <future>
#include "AIController.h"

#include "ProblemSolverState.h"
#include "FollowPathState.h"
#include "ShowResultState.h"
#include "../AI/Pathfinder.h"
#include "../Data/ProblemPackage.h"
#include "../Services/WorldStateLocator.h"
#include "../WorldObjects/Maze.h"

/// <summary>
/// The State for the LittleProblemSolver where it is supposed to asynchroniously retrieve the shortest path from point A to point B. 
/// </summary>
class FindPathState : public ProblemSolverState {
private:
	Pathfinder pathfinder_;
	std::future<std::vector<unsigned long int>> path_;
	ProblemDefinition problemDefinition_;
	sf::Clock clock_;
	int waitTime_;

	ProblemDefinition generateRandomProblem(sf::Vector2f characterPosition, int mapHeight, int mapWidth, int amountOfWalls);

public:
	void update(float deltaTime) override;
	void enter() override;
	FindPathState(AIController* parent, AnimatedSprite* owner, ProblemDefinition problemDefinition = {});
};