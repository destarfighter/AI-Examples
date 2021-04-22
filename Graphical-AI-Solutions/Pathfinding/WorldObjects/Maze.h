#pragma once
#include <SFML/Graphics.hpp>
#include "WorldObject.h"
#include "TileMap.h"
#include "MapPackage.h"

class Maze : public WorldObject {
	TileMap tileMap_;

public:
	Maze();
	void setMapData(MapData mapData);
	void initialize(std::string tileSetPath, MapData mapData);
	virtual void draw(sf::RenderWindow& window) override;
};

