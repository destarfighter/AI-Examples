#pragma once
#include <SFML/Graphics.hpp>
#include "MapPackage.h"

class TileMap : public sf::WorldObject, sf::Transformable {

	sf::VertexArray vertices;
	sf::Texture tileset;

public:
	bool load(const std::string& tilesetPath, MapData mapData);

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override; 
};

