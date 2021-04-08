#pragma once
#include <SFML/System/Vector2.hpp>
#include <vector>
#include "MapPackage.h"

enum PathfinderStates {
	IS_IDLE = 0,
	IS_WORKING = 1,
	IS_READY = 2
};

// TODO: clean way to reset Pathfinder? 
class Pathfinder {
private:
	PathfinderStates state_ {IS_IDLE};
	bool foundPath_{ false };
public:
	std::vector<unsigned int> findPath(sf::Vector2f startPosition, sf::Vector2u destination, MapData mapData);
	const PathfinderStates getState() const noexcept { return state_; }
	const bool getFoundPath() const noexcept { return foundPath_; }
};

