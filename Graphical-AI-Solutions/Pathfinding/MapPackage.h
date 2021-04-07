#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

struct MapData {
	// The size of each individual tile in a tileMap
	sf::Vector2u tileSize;
	// The map 2d layout represented as integers
	std::vector<int> tiles;
	// The width of the map in number of tiles
	unsigned int width;
	// The height of the map in number of tiles 
	unsigned int height;
};