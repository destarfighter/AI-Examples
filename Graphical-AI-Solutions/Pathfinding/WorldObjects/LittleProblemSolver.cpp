#include "LittleProblemSolver.h"

void LittleProblemSolver::update(float deltaTime) {
	// Update Animation
	 animatedSprite_.update(deltaTime);
	// Update character based on current state
	//aiController_.update(deltaTime);
}

void LittleProblemSolver::draw(sf::RenderWindow& window) {
	window.draw(animatedSprite_);
}

void LittleProblemSolver::initialize(AnimData animData, unsigned int startingAnimNum, sf::Vector2f startPosition) {
	position_ = startPosition;
	animatedSprite_.setPosition(startPosition);
	// Initialize AnimationSprite
	animatedSprite_.initialize(animData, startingAnimNum);
	// Create Animation States Mappings
	/*for (unsigned int i = 0; i < animData.numOfAnimatons; ++i) {
		animationStates_.emplace(animData.frameInfo[i].animName, i);
	}*/
}
