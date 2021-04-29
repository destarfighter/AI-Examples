#pragma once
#include "../Flocking/AI/AnimalStates.h"

class SheepGrazeState : public AnimalState {
private:

public:
	void update(float deltaTime) override;
	void enter() override;
	void exit() override;
	SheepGrazeState(AIController* parent, AnimatedSprite* owner);
};

