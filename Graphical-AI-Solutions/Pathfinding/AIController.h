#pragma once
#include "AIState.h"

class AIController {
	AIState state;
public:
	void update(float deltaTime);
	void setState(AIState newState);
};

