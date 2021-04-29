#include "Map.h"

Map::Map() 
: tileMap_(TileMap()) { }

void Map::draw(sf::RenderWindow& window) {
	window.draw(tileMap_);
}

void Map::initialize(std::string tileSetPath, MapData mapData) {
	tileMap_.initialize(tileSetPath, mapData);
}
