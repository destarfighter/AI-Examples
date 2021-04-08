#pragma once
#include <SFML/Graphics.hpp>
#include "WorldObject.hpp"
#include "MapPackage.h"
#include "TileMap.h"

class Maze : public WorldObject {
	MapData mapData_;
	TileMap tileMap_;

public:
	void initialize(std::string tileSetPath, MapData mapData);
	virtual void draw(sf::RenderWindow& window) override;
};

