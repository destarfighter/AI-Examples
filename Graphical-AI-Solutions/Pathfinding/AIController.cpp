#include "AIController.h"

void AIController::update(float deltaTime) {
	state_.update(deltaTime);
}

void AIController::setState(AIState newState) {
	state_.exit();
	state_ = newState;
	state_.enter();
}
