#pragma once
#include "../Flocking/AI/AnimalStates.h"

class PredatorChaseState : public AnimalState {
private:

public:
	void update(float deltaTime) override;
	void enter() override;
	void exit() override;
	PredatorChaseState(AIController* parent, AnimatedSprite* owner);
};

