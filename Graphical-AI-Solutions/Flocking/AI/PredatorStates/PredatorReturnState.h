#pragma once
#include "../Flocking/AI/AnimalStates.h"

class PredatorReturnState : public AnimalState {
private:

public:
	void update(float deltaTime) override;
	void enter() override;
	void exit() override;
	PredatorReturnState(AIController* parent, AnimatedSprite* owner);
};

