#pragma once
#include <SFML/Graphics.hpp>

class TileMap : public sf::Drawable, sf::Transformable {

	sf::VertexArray vertices;
	sf::Texture tileset;

public:
	bool load(const std::string& tilesetPath, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height);

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const; 
};

