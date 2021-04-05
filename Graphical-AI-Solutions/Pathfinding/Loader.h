#pragma once
#include <SFML/Graphics.hpp>

class Loader {


public:
	static std::shared_ptr<sf::Texture> loadTexture(std::string image_path) {
		auto texture_ptr = std::make_shared<sf::Texture>();
		if (!texture_ptr->loadFromFile(image_path))
			throw std::exception("Failed to load image from file.");
		return texture_ptr;
	}

	static int* loadMapData(std::string mapData_path) {
		return nullptr;
	}

};