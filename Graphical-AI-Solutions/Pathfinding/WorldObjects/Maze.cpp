#include "Maze.h"

Maze::Maze()
: mapData_(MapData())
, tileMap_(TileMap()) { }

void Maze::setMapData(MapData mapData) {
	mapData_ = mapData;
	//tileMap_.
}

void Maze::initialize(std::string tileSetPath, MapData mapData) {
	mapData_ = mapData;
	tileMap_ = TileMap();
	tileMap_.initialize(tileSetPath, mapData_);
}

void Maze::draw(sf::RenderWindow& window) {
	window.draw(tileMap_);
}
