#include "LittleProblemSolver.h"

void LittleProblemSolver::update(float deltaTime) {
	// Update Animation
	AnimatedSprite::update(deltaTime);
	// Update character based on current state
	ai_controller_.update(deltaTime);
}

void LittleProblemSolver::initialize(AnimData _animData, unsigned int _startingAnimNum, MapData mapData) {
	// Initialize AnimationSprite
	AnimatedSprite::initialize(_animData, _startingAnimNum);
	// Create Animation States Mappings
	for (unsigned int i = 0; i < _animData.numOfAnimatons; ++i) {
		animationStates_.emplace(_animData.frameInfo[i].animName, i);
	}
	// set map to current environment. 
	mapData_ = mapData;
}
