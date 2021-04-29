#pragma once
#include "AIState.h"
#include "AnimatedSprite.h"

class AnimalState : public AIState {
protected:
	AnimatedSprite* owner_;

public:
	AnimalState(AIController* parent, AnimatedSprite* owner)
		: AIState(parent)
		, owner_(owner) {};
	void initialize(AIController* parent, AnimatedSprite* owner) {
		parent_ = parent;
		owner_ = owner;
	};
};