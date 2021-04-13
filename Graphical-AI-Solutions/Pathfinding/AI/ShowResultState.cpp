#include "ShowResultState.h"
#include "FindPathState.h"

void ShowResultState::update(float deltaTime) {
	parent_->setState(new FindPathState(parent_, owner_));
};

void ShowResultState::enter() {
	// Set Animation "Celebrate" or "Cry"
};

void ShowResultState::exit() {

};

ShowResultState::ShowResultState(AIController* parent, AnimatedSprite* owner, bool foundPath)
	: ProblemSolverState(parent, owner)
	, foundPath_(foundPath) {};