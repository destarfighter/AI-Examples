#pragma once
#include <SFML/Graphics.hpp>
#include "../Data/MapPackage.h"
#include "../config.h"

class TileMap : public sf::Drawable, public sf::Transformable {
private:
	sf::VertexArray vertices_;
	std::shared_ptr<sf::Texture> tileset_ptr_; // TODO: Memory leak in sf::Texture. texture should be freed as TileMap goes out of scope or is destroyed, but it doesnt. 

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
	TileMap();
	bool initialize(const std::string& tilesetPath, MapData mapData);
	void setMapData(MapData mapData);
	void SetTileData(int tileIndex, int newTextureIndex);
};

