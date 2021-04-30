#pragma once
#include "SteeringBehavior.h"
#include <vector>
#include "SFML/Graphics/Vertex.hpp"

struct SteeringOutput {
	sf::Vector2f linear;
	float angular;
};

class BlendedSteering {
private:
	// All behaviors that should be blended
	std::vector<SteeringBehavior> behaviors;
	// Overall maximum acceleration and rotation
	float maxAcceleration;
	float maxRotation;

	SteeringOutput getSteering();
};

