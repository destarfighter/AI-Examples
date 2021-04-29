#pragma once
#include "../Flocking/AI/AnimalStates.h"

class SheepFleeState : public AnimalState {
private:

public:
	void update(float deltaTime) override;
	void enter() override;
	void exit() override;
	SheepFleeState(AIController* parent, AnimatedSprite* owner);
};

