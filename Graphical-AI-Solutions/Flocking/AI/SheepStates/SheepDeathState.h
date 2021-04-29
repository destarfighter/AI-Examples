#pragma once
#include "../Flocking/AI/AnimalStates.h"

class SheepDeathState : public AnimalState {
private:

public:
	void update(float deltaTime) override;
	void enter() override;
	void exit() override;
	SheepDeathState(AIController* parent, AnimatedSprite* owner);
};

