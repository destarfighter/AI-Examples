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
		if (true) {
			parent_->setState(FollowPathState());
		}
	};
	void enter() override {

	};
	void exit() override {

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