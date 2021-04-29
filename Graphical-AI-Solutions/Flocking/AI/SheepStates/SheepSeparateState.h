#pragma once
#include "../Flocking/AI/AnimalStates.h"

class SheepSeparateState : public AnimalState {
private:

public:
	void update(float deltaTime) override;
	void enter() override;
	void exit() override;
	SheepSeparateState(AIController* parent, AnimatedSprite* owner);
};

