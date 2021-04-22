#pragma once
#include "pch.h"
#include <SFML/System/Vector2.hpp>
#include <vector>

#define AICOMMONLIBRARY_API __declspec(dllexport)

struct AICOMMONLIBRARY_API MapData {
	// The size of each individual tile in a tileMap
	sf::Vector2u tileSize_;
	// The map 2d layout represented as integers
	std::vector<int> tiles_;
	// The width of the map in number of tiles
	unsigned int width_;
	// The height of the map in number of tiles 
	unsigned int height_;
};