#pragma once
#include "WorldObject.h"
#include "TileMap.h"

class Map : public WorldObject {
private:
	TileMap tileMap_;
	// obstructions
	// Obstruction* obstructions

public:
	Map();
	virtual void draw(sf::RenderWindow& window) override;
	void initialize(std::string tileSetPath, MapData mapData);
};

