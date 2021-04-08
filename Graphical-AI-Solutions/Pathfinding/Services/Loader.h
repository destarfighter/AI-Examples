#pragma once
#include <SFML/Graphics.hpp>
#include "../WorldObjects/LittleProblemSolver.h"
#include "../Data/MapPackage.h"
#include "../WorldObjects/Maze.h"

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
		new_character.initialize(animData, 0, sf::Vector2f(0.f, 0.f));

		return new_character;
	}

	static Maze CreateMaze(MapData mapData) {
		// create the tilemap from the level definition
		Maze new_map;
		new_map.initialize("Resources/Images/tileset.png", mapData);
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