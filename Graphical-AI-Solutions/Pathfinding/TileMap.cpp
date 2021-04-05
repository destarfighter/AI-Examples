#include "TileMap.h"

bool TileMap::load(const std::string& tilesetPath, MapData mapData) {
	// Load the tileset Texture
	if (!tileset.loadFromFile(tilesetPath))
		return false;

	// resize the vertex array to fit the level size
	vertices.setPrimitiveType(sf::Quads);
	vertices.resize(mapData.width * mapData.height * 4);

	// populate the vertex array, with one quad per tile
	for (unsigned int i = 0; i < mapData.width; ++i) {
		for (unsigned int j = 0; j < mapData.height; ++j) {
			// get the current tileNumber
			int tileNumber = mapData.tiles[i + j * mapData.width];
			
			// get a pointer to the current tile's quad
			sf::Vertex* quad = &vertices[(i + j * mapData.width) * 4];

			// define the quads 4 corners
			quad[0].position = sf::Vector2f(i * mapData.tileSize.x, j * mapData.tileSize.y);
			quad[1].position = sf::Vector2f((i + 1) * mapData.tileSize.x, j * mapData.tileSize.y);
			quad[2].position = sf::Vector2f((i + 1) * mapData.tileSize.x, (j + 1) * mapData.tileSize.y);
			quad[3].position = sf::Vector2f(i * mapData.tileSize.x, (j + 1) * mapData.tileSize.y);

			// find the tiles position in the tileset
			int tu = tileNumber % (tileset.getSize().x / mapData.tileSize.x);
			int tv = tileNumber / (tileset.getSize().x / mapData.tileSize.x);

			// define the quads 4 texture coordinates
			quad[0].texCoords = sf::Vector2f(tu * mapData.tileSize.x, tv * mapData.tileSize.y);
			quad[1].texCoords = sf::Vector2f((tu + 1) * mapData.tileSize.x, tv * mapData.tileSize.y);
			quad[2].texCoords = sf::Vector2f((tu + 1) * mapData.tileSize.x, (tv + 1) * mapData.tileSize.y);
			quad[3].texCoords = sf::Vector2f(tu * mapData.tileSize.x, (tv + 1) * mapData.tileSize.y);
		}
	}
	return true;
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	// apply the transform
	states.transform *= getTransform();

	// apply the tileset texture
	states.texture = &tileset;
	
	// draw the vertex
	target.draw(vertices, states);
}
