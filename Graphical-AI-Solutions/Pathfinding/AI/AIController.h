#pragma once
#include "../AI/AIState.h"

class AIController {
private:
	AIState state_;
public:
	void update(float deltaTime);
	void setState(AIState newState);
};

