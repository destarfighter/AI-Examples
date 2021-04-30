#pragma once
#include "SFML/Graphics/Vertex.hpp"
#include "../AI/Steering Behaviors/BlendedSteering.h"

class Kinematic {
private:
	// current position and orientation
	sf::Vector2f position_;
	float orientation_;
	// forces for velocity and rotation
	sf::Vector2f velocity_;
	float rotation_;
public:
	Kinematic();
	void initialize(sf::Vector2f startPosition, float startRotation);
	void update(float deltaTime, SteeringOutput steering);
	sf::Vector2f getPosition();
	float getRotation();
};

