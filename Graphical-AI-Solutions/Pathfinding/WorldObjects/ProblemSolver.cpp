#include "ProblemSolver.h"

void ProblemSolver::update(float deltaTime) {
	// Update Animation
	animatedSprite_.update(deltaTime);
	// Update character based on current state
	aiController_->update(deltaTime);
}

void ProblemSolver::draw(sf::RenderWindow& window) {
	window.draw(animatedSprite_);
}

ProblemSolver::ProblemSolver()
	: aiController_(new AIController())
	, animatedSprite_(AnimatedSprite())
	, animationStates_(std::map<std::string, int>())
	, position_(sf::Vector2f()) 
{ }

void ProblemSolver::initialize(AnimData animData, unsigned int startingAnimNum, sf::Vector2f startPosition) {
	// Set Starting positions of own object and animated sprite. 
	position_ = startPosition;
	animatedSprite_.setPosition(startPosition);
	// Initialize AnimationSprite
	animatedSprite_.initialize(animData, startingAnimNum);
	// Create Animation States Mappings
	for (unsigned int i = 0; i < animData.numOfAnimatons_; ++i) {
		animationStates_.emplace(animData.frameInfo_[i].animName_, i);
	}
	// Set state for ai controller
	aiController_->initialize(new AskForProblemState(aiController_, this));
}
