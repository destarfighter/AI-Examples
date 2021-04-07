#pragma once
#include <SFML/Graphics.hpp>
#include "LittleProblemSolver.h"
#include "MapPackage.h"

namespace Loader {

	static std::shared_ptr<sf::Texture> loadTexture(std::string image_path) {
		auto texture_ptr = std::make_shared<sf::Texture>();
		if (!texture_ptr->loadFromFile(image_path))
			throw std::exception("Failed to load image from file.");
		return texture_ptr;
	}

	static int* loadMapData(std::string mapData_path) {
		return nullptr;
	}

	static LittleProblemSolver CreateCharacter(MapData mapData) {

		auto texture = Loader::loadTexture("Resources/Images/Positiv Animation Sheet.png");
		texture->setSmooth(true);
		texture->setRepeated(false);

		auto frameInfo = std::vector<AnimFrameData>();
		frameInfo.push_back(AnimFrameData{ sf::Rect<int>(6 * 48, 0, 48, 48), 5, "celebrate" });
		AnimData animData{ texture, frameInfo, 1 };

		auto new_character = LittleProblemSolver();
		new_character.initialize(animData, 0);
		new_character.setPosition(0.f, 0.f);

		return new_character;
	}

	static TileMap CreateTileMap(MapData mapData) {
		// create the tilemap from the level definition
		TileMap new_map;
		if (!new_map.load("Resources/Images/tileset.png", mapData))
			throw std::exception("error while loading tileset!");

		return new_map;
	}

	static MapData CreateMapData() {

		std::vector<int> level = {
			0, 0, 0, 0, 0, 3, 0, 1, 1,
			0, 0, 0, 0, 0, 0, 0, 1, 0,
			0, 1, 1, 0, 1, 1, 0, 0, 0,
			0, 1, 0, 0, 0, 1, 0, 1, 1,
			0, 1, 0, 0, 0, 1, 0, 0, 0,
			0, 0, 0, 0, 0, 1, 0, 1, 1,
			0, 1, 1, 0, 0, 1, 0, 0, 0,
			0, 0, 1, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 2, 0, 0, 0, 0 };

		auto new_mapData = MapData{ sf::Vector2u(32, 32), level, 9, 9 };

		return new_mapData;
	}
}