#include "Animal.h"

Animal::Animal()
: Kinematic()
, aiController_(new AIController())
, animatedSprite_(new AnimatedSprite()) { }

Animal::~Animal() {
	delete aiController_;
	delete animatedSprite_;
}

void Animal::initialize(AnimData animData, unsigned int startingAnimNum, sf::Vector2f startPosition, AnimalState* startingState, float startRotation) {
	// Initialize AnimatedSprite
	animatedSprite_->setPosition(startPosition);
	animatedSprite_->setRotation(startRotation);
	animatedSprite_->initialize(animData, startingAnimNum);
	// Initialize AIController
	startingState->initialize(aiController_, animatedSprite_, this);
	aiController_->initialize(startingState);
	// Initialize Kinematic
	Kinematic::initialize(startPosition, startRotation);
}

void Animal::update(float deltatime) {
	aiController_->update(deltatime);
	animatedSprite_->update(deltatime);
}

void Animal::draw(sf::RenderWindow& window) {
	window.draw(*animatedSprite_);
}
