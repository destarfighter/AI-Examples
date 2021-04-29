#pragma once
#include "../Flocking/AI/AnimalStates.h"

class SheepFlockState : public AnimalState {
private:

public:
	void update(float deltaTime) override;
	void enter() override;
	void exit() override;
	SheepFlockState(AIController* parent, AnimatedSprite* owner);
};
