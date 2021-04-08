#include "Maze.h"

void Maze::initialize(std::string tileSetPath, MapData mapData) {
	mapData_ = mapData;
	tileMap_ = TileMap();
	tileMap_.load(tileSetPath, mapData_);
}

void Maze::draw(sf::RenderWindow& window) {
	window.draw(tileMap_);
}
