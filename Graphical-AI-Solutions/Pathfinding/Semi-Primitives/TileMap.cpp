#include "TileMap.h"

TileMap::TileMap()
	: vertices_(sf::VertexArray())
	, tileset_(sf::Texture()) { }

bool TileMap::initialize(const std::string& tilesetPath, MapData mapData) {
	// Load the tileset Texture
	if (!tileset_.loadFromFile(tilesetPath))
		return false;

	setMapData(mapData);

	return true;
}

void TileMap::setMapData(MapData mapData)
{
	// Resize the vertex array to fit the level size
	vertices_.setPrimitiveType(sf::Quads);
	vertices_.resize(mapData.width_ * mapData.height_ * 4);

	// Populate the vertex array, with one quad per tile
	for (unsigned int i = 0; i < mapData.width_; ++i) {
		for (unsigned int j = 0; j < mapData.height_; ++j) {
			// Get the current tileNumber
			int tileNumber = mapData.tiles_[i + j * mapData.width_];

			// Get a pointer to the current tile's quad
			sf::Vertex* quad = &vertices_[(i + j * mapData.width_) * 4];

			// Define the quads 4 corners
			quad[0].position = sf::Vector2f(i * mapData.tileSize_.x, j * mapData.tileSize_.y);
			quad[1].position = sf::Vector2f((i + 1) * mapData.tileSize_.x, j * mapData.tileSize_.y);
			quad[2].position = sf::Vector2f((i + 1) * mapData.tileSize_.x, (j + 1) * mapData.tileSize_.y);
			quad[3].position = sf::Vector2f(i * mapData.tileSize_.x, (j + 1) * mapData.tileSize_.y);

			// Find the tiles position in the tileset
			int tu = tileNumber % (tileset_.getSize().x / mapData.tileSize_.x);
			int tv = tileNumber / (tileset_.getSize().x / mapData.tileSize_.x);

			// Define the quads 4 texture coordinates
			quad[0].texCoords = sf::Vector2f(tu * mapData.tileSize_.x, tv * mapData.tileSize_.y);
			quad[1].texCoords = sf::Vector2f((tu + 1) * mapData.tileSize_.x, tv * mapData.tileSize_.y);
			quad[2].texCoords = sf::Vector2f((tu + 1) * mapData.tileSize_.x, (tv + 1) * mapData.tileSize_.y);
			quad[3].texCoords = sf::Vector2f(tu * mapData.tileSize_.x, (tv + 1) * mapData.tileSize_.y);
		}
	}
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	// Apply the transform
	states.transform *= getTransform();

	// Apply the tileset texture
	states.texture = &tileset_;
	
	// Draw the vertex
	target.draw(vertices_, states);
}
