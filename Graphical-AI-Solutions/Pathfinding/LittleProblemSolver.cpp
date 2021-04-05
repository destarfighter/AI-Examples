#include "LittleProblemSolver.h"

void LittleProblemSolver::update(float deltaTime) {
	// Update Animation
	AnimatedSprite::update(deltaTime);
	// Update character based on current state
	ai_controller_.update(deltaTime);
}
