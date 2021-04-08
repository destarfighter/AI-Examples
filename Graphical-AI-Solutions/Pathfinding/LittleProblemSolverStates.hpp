#pragma once
#include <future>
#include "LittleProblemSolver.h"
#include "Pathfinder.h"
#include "MapPackage.h"
#include "ProblemPackage.h"

class LittleProblemSolverState : public AIState {
protected:
	LittleProblemSolver* owner_;
public:
	void setOwner(LittleProblemSolver* owner) {
		owner_ = owner;
	};
};

/// <summary>
/// A State where we ask for a new problem to be generated and pushed to the world. 
/// </summary>
class AskForProblemState : public LittleProblemSolverState {

	void update(float deltaTime) override {
		// ask for new problem
		// set state to SolveProblemState
	};
	void enter() override {
		
	};
	void exit() override {

	};
};

/// <summary>
/// The State for the LittleProblemSolver where it is supposed to asynchroniously retrieve the shortest path from point A to point B. 
/// </summary>
class SolveProblemState : public LittleProblemSolverState {

	Pathfinder pathfinder_;
	std::future<std::vector<unsigned int>> path_;
	ProblemDefinition problemDefinition_;

	void update(float deltaTime) override {
		
		if (pathfinder_.getState() == IS_IDLE)
			path_ = std::async(&Pathfinder::findPath, &pathfinder_, owner_->position_, problemDefinition_.destination, problemDefinition_.mapData);
				
		if (pathfinder_.getState() == IS_READY) {

			if (pathfinder_.getFoundPath()) {
				parent_->setState(FollowPathState(path_.get()));
			}
			else {
				parent_->setState(ShowResultState(false));
			}
		}
	};
	void enter() override {
		// Initialize pathfinde
		pathfinder_ = Pathfinder();
		// Set Animation to thinking animation
		owner_->animatedSprite_.changeAnim(0);
	};
public:
	SolveProblemState(ProblemDefinition problemDefinition) 
	: problemDefinition_(problemDefinition) { };
};

/// <summary>
/// A State where we follow the path represented by an int vector. 
/// </summary>
class FollowPathState : public LittleProblemSolverState {
	// shortest path to destination
	std::vector<unsigned int> path_;

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
public:
	FollowPathState(std::vector<unsigned int> path) // call base constructor
		: path_(path) {}
};

/// <summary>
/// A State where we display the result of our problem solver atempt. success or failure
/// </summary>
class ShowResultState : public LittleProblemSolverState {

	bool foundPath_;

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
public:
	ShowResultState(bool foundPath)
		: foundPath_(foundPath) {};
};