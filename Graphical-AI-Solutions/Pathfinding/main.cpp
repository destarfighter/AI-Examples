//#include <SFML/Graphics.hpp>
#include <thread>
#include "AnimatedSprite.h"
#include "TileMap.h"

std::shared_ptr<sf::Texture> loadTexture(std::string image_path) {
	auto texture_ptr = std::make_shared<sf::Texture>();
	if (!texture_ptr->loadFromFile(image_path))
		throw std::exception("Failed to load image from file.");
	return texture_ptr;
}

// Creating arbitrary animated sprite for testing.
AnimatedSprite loadAnimatedSprite(std::shared_ptr<sf::Texture> texture) {
	auto frameInfo = std::vector<AnimFrameData>();
	frameInfo.push_back(AnimFrameData{ sf::Rect<int>(6*48, 0, 48, 48), 5 });
	AnimData animData{ texture, frameInfo, 1 };

	auto new_animatedSprite = AnimatedSprite();
	new_animatedSprite.Initialize(animData, 0);
	return new_animatedSprite;
}

void renderingThread(sf::RenderWindow* window) {
	window->setActive(true);

#pragma region  temporary game-objects - Testing

	//create an animated sprite
	auto texture = loadTexture("Resources/Images/Positiv Animation Sheet.png");
	texture->setSmooth(true);
	texture->setRepeated(false);
	auto animatedSprite = loadAnimatedSprite(texture);
	animatedSprite.setPosition(0.f, 0.f);

	//create tileset
	const int level[] = {
		0, 0, 0, 0, 0, 3, 0, 1, 1,
		0, 0, 0, 0, 0, 0, 0, 1, 0,
		0, 1, 1, 0, 1, 1, 0, 0, 0,
		0, 1, 0, 0, 0, 1, 0, 1, 1,
		0, 1, 0, 0, 0, 1, 0, 0, 0,
		0, 0, 0, 0, 0, 1, 0, 1, 1,
		0, 1, 1, 0, 0, 1, 0, 0, 0,
		0, 0, 1, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 2, 0, 0, 0, 0 };

	// create the tilemap from the level definition
	TileMap map;
	if (!map.load("Resources/Images/tileset.png", sf::Vector2u(32, 32), level, 9, 9))
		throw std::exception("error while loading tileset!");

#pragma endregion

	sf::Clock deltaClock;
	while (window->isOpen()) {
		window->clear();
		
		// draw problem graphical representation
		// draw sorted list of sprites
		animatedSprite.UpdateAnim(deltaClock.getElapsedTime().asSeconds());
		window->draw(map);
		window->draw(animatedSprite);

		window->display();
		deltaClock.restart();
	}
}

void workerThread() {
	// solve problem
	// return solution
}


int main() {

	sf::RenderWindow window(sf::VideoMode(288, 288), "Pathfinder");
	window.setActive(false);

	// create threads for rendering and pathfinding
	std::thread renderThread(renderingThread, &window);
	std::thread workThread(workerThread);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
	}

	// join and close all threads
	renderThread.join();
	workThread.join();

	return 0;
}