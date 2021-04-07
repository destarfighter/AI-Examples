#include "LittleProblemSolver.h"

void LittleProblemSolver::update(float deltaTime) {
	// Update Animation
	AnimatedSprite::update(deltaTime);
	// Update character based on current state
	//aiController_.update(deltaTime);
}

void LittleProblemSolver::initialize(AnimData animData, unsigned int startingAnimNum) {
	// Initialize AnimationSprite
	AnimatedSprite::initialize(animData, startingAnimNum);
	// Create Animation States Mappings
	/*for (unsigned int i = 0; i < animData.numOfAnimatons; ++i) {
		animationStates_.emplace(animData.frameInfo[i].animName, i);
	}*/
}
