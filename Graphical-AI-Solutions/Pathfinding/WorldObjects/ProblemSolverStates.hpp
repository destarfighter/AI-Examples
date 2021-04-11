#pragma once
#include <future>
#include "../Services/WorldStateLocator.h"
#include "../Data/ProblemPackage.h"
#include "../Data/MapPackage.h"
#include "../WorldObjects/Maze.h"
#include "../AI/Pathfinder.h"
#include "../AI/AIState.h"

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
		//// Initialize pathfinde
		//pathfinder_ = Pathfinder();
		//// Set Animation to thinking animation
		//owner_->animatedSprite_.changeAnim(0);
	};

	SolveProblemState(AIController* parent, ProblemSolver* owner, ProblemDefinition problemDefinition)
		: ProblemSolverState(parent, owner)
		,problemDefinition_(problemDefinition) { };
};

/// <summary>
/// A State where we ask for a new problem to be generated and pushed to the world. 
/// </summary>
class AskForProblemState : public ProblemSolverState {
public:
	virtual void update(float deltaTime) override {
		// ask for new problem
		auto problem = ProblemDefinition();

		// find maze object in worlState
		WorldState* worldState = WorldStateLocator::getWorldState();
		auto mazeId = worldState->getObjectId("maze");
		auto maze = worldState->getObject(mazeId);

		// Cast to Maze and call setMapData with problem update	
		std::static_pointer_cast<Maze>(maze)->setMapData(problem.mapData);

		// Change state to Solve Problem State with 'problem' as argument. 
		parent_->setState(new SolveProblemState(parent_, owner_, problem));
	}
	void enter() override {};
	void exit() override {};

	AskForProblemState(AIController* parent, ProblemSolver* owner)
		: ProblemSolverState(parent, owner) {};
};