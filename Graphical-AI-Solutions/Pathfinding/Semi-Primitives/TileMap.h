#pragma once
#include <SFML/Graphics.hpp>
#include "../Data/MapPackage.h"

class TileMap : public sf::Drawable, public sf::Transformable {
private:
	sf::VertexArray vertices_;
	sf::Texture tileset_;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
	bool load(const std::string& tilesetPath, MapData mapData);
};

