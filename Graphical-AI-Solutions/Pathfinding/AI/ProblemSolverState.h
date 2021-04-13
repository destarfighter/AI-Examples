#pragma once
#include "../AI/AIState.h"
#include "../Semi-Primitives/AnimatedSprite.h"

class ProblemSolverState : public AIState {
protected:
	AnimatedSprite* owner_;

public:
	ProblemSolverState(AIController* parent, AnimatedSprite* owner)
		: AIState(parent)
		, owner_(owner) {};
};

