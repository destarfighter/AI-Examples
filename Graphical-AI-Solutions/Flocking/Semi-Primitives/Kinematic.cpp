#include "Kinematic.h"

Kinematic::Kinematic()
: position_(sf::Vector2f(0, 0))
, orientation_(0)
, velocity_(sf::Vector2f(0, 0))
, rotation_(0) { }

void Kinematic::initialize(sf::Vector2f startPosition, float startRotation) {
	position_ = startPosition;
	rotation_ = startRotation;
}

void Kinematic::update(float deltaTime, SteeringOutput steering) {
	// Update the position and orientation
	position_ += velocity_ * deltaTime;
	orientation_ += rotation_ * deltaTime;

	// Update the velocity and rotation
	velocity_ += steering.linear * deltaTime;
	rotation_ += steering.angular * deltaTime;
}

sf::Vector2f Kinematic::getPosition() {
	return position_;
}

float Kinematic::getRotation() {
	return rotation_;
}
