#pragma once
#include "../Flocking/AI/AnimalStates.h"
#include "../Flocking/Semi-Primitives/Kinematic.h"

class PredatorWanderState : public AnimalState {
private:

public:
	void update(float deltaTime) override;
	void enter() override;
	void exit() override;
	PredatorWanderState(AIController* parent, AnimatedSprite* owner, Kinematic* ownerKinematic);
};

