#pragma once
#include "../AI/AIState.h"

class AIController {
private:
	AIState* state_;
public:
	void initialize(AIState* initialState);
	void update(float deltaTime);
	void setState(AIState* newState);
};

