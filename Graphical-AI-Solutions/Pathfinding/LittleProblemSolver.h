#pragma once
#include "AnimatedSprite.h"
#include "AIState.h"
#include "AIController.h"

class LittleProblemSolver : public AnimatedSprite {

	AIController ai_controller_;
	// map
	// path
	// position

	// Inherited via Updatable
	virtual void update(float deltaTime) override;

	friend class SolveProblemState;
	friend class FollowPathState;
	friend class ShowResultState;
};

