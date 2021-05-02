#pragma once
#include "AIState.h"
#include "AnimatedSprite.h"
#include "../Semi-Primitives/Kinematic.h"

class AnimalState : public AIState {
protected:
	AnimatedSprite* ownerAnimation_;
	Kinematic* ownerKinematic_;

public:
	AnimalState(AIController* parent, AnimatedSprite* ownerAnimation, Kinematic* ownerKinematic)
		: AIState(parent)
		, ownerAnimation_(ownerAnimation)
	    , ownerKinematic_(ownerKinematic) {};
	void initialize(AIController* parent, AnimatedSprite* ownerAnimation, Kinematic* ownerKinematic) {
		parent_ = parent;
		ownerAnimation_ = ownerAnimation;
		ownerKinematic_ = ownerKinematic;
	};
};