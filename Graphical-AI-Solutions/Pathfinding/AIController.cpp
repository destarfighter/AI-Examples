#include "AIController.h"

void AIController::update(float deltaTime) {
	state.update(deltaTime);
}

void AIController::setState(AIState newState) {
	state.exit();
	state = newState;
	state.enter();
}
