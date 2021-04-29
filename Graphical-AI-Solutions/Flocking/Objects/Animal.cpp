#include "Animal.h"

Animal::Animal()
: aiController_(new AIController())
, animatedSprite_(new AnimatedSprite()) { }

Animal::~Animal() {
	delete aiController_;
	delete animatedSprite_;
}

void Animal::initialize(AnimData animData, unsigned int startingAnimNum, sf::Vector2f startPosition, AnimalState* startingState, float startRotation) {
	animatedSprite_->setPosition(startPosition);
	animatedSprite_->initialize(animData, startingAnimNum);

	animatedSprite_->setRotation(startRotation);

	startingState->initialize(aiController_, animatedSprite_);
	aiController_->initialize(startingState);
}

void Animal::update(float deltatime) {
	animatedSprite_->update(deltatime);
	aiController_->update(deltatime);
}

void Animal::draw(sf::RenderWindow& window) {
	window.draw(*animatedSprite_);
}
