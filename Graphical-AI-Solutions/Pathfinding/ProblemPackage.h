#pragma once
#include <SFML/Graphics.hpp>
#include "MapPackage.h"

struct ProblemDefinition {
	MapData mapData;
	sf::Vector2u destination;
};