#pragma once
#include <SFML/System/Vector2.hpp>
#include "../Data/MapPackage.h"

struct ProblemDefinition {
	// The environment of a problem for a pathfinder
	MapData mapData;
	// The desination of a pathfinder problem
	sf::Vector2u destination;
};