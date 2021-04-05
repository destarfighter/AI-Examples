#pragma once
#include "LittleProblemSolver.h"

class LittleProblemSolverState : public AIState {
protected:
	LittleProblemSolver* owner_;
public:
	void setOwner(LittleProblemSolver* owner) {
		owner_ = owner;
	};
};

class SolveProblemState : public LittleProblemSolverState {

	void update(float deltaTime) override {
		
		// find path / check if finished

		// if finished. - store result and change state to FollowPathState
	};
	void enter() override {
		// Set Animation to thinking animation
	};
	void exit() override {
		// Do nothing? 
	};
};

class FollowPathState : public LittleProblemSolverState {

	void update(float deltaTime) override {

	};
	void enter() override {

	};
	void exit() override {

	};
};

class ShowResultState : public LittleProblemSolverState {

	void update(float deltaTime) override {

	};
	void enter() override {

	};
	void exit() override {

	};
};