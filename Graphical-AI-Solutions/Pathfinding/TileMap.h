#pragma once
#include <SFML/Graphics.hpp>
#include "MapPackage.h"
#include "WorldObject.hpp"

class TileMap : public WorldObject, public sf::Drawable, sf::Transformable {

	sf::VertexArray vertices;
	sf::Texture tileset;

public:
	bool load(const std::string& tilesetPath, MapData mapData);
	virtual void draw(sf::RenderWindow window);

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const; 
};

