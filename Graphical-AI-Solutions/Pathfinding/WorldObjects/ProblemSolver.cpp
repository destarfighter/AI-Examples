#include "ProblemSolver.h"
#include "../AI/ProblemSolverState.h"
#include "../AI/FindPathState.h"
#include "../AI/FollowPathState.h"
#include "../AI/ShowResultState.h"

void ProblemSolver::update(float deltaTime) {
	// Update Animation
	animatedSprite_->update(deltaTime);
	// Update character based on current state
	aiController_->update(deltaTime);
}

void ProblemSolver::draw(sf::RenderWindow& window) {
	window.draw(*animatedSprite_);
}

ProblemSolver::ProblemSolver()
	: aiController_(new AIController())
	, animatedSprite_(new AnimatedSprite())
	, position_(sf::Vector2f(0.f, 0.f)) 
{ }

void ProblemSolver::initialize(AnimData animData, unsigned int startingAnimNum, sf::Vector2f startPosition) {
	// Set Starting positions of own object and animated sprite. 
	position_ = startPosition;
	animatedSprite_->setPosition(startPosition);
	// Initialize AnimationSprite
	animatedSprite_->initialize(animData, startingAnimNum);
	// Set state for ai controller
	aiController_->initialize(new FindPathState(aiController_ ,animatedSprite_));
}
