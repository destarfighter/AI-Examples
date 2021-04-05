#pragma once
#include <SFML/Graphics.hpp>

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

class TileMap : public sf::Drawable, sf::Transformable {

	sf::VertexArray vertices;
	sf::Texture tileset;

public:
	bool load(const std::string& tilesetPath, MapData mapData);

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const; 
};

