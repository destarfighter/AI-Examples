#pragma once
#include <SFML/Graphics.hpp>
#include "../WorldObjects/WorldObject.hpp"
#include "../Data/MapPackage.h"
#include "../Semi-Primitives/TileMap.h"

class Maze : public WorldObject {
	MapData mapData_;
	TileMap tileMap_;

public:
	Maze();
	void setMapData(MapData mapData);
	void initialize(std::string tileSetPath, MapData mapData);
	virtual void draw(sf::RenderWindow& window) override;
};

