#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include "TileMap.h"
#include "Loader.h"
#include "Updatable.h"
#include "LittleProblemSolver.h"


LittleProblemSolver CreateCharacter() {

	auto texture = Loader::loadTexture("Resources/Images/Positiv Animation Sheet.png");
	texture->setSmooth(true);
	texture->setRepeated(false);
	
	auto frameInfo = std::vector<AnimFrameData>();
	frameInfo.push_back(AnimFrameData{ sf::Rect<int>(6 * 48, 0, 48, 48), 5 });
	AnimData animData{ texture, frameInfo, 1 };

	auto new_character = LittleProblemSolver();
	new_character.Initialize(animData, 0);
	new_character.setPosition(0.f, 0.f);

	return new_character; 
}

TileMap CreateMap() {
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
	TileMap new_map;
	if (!new_map.load("Resources/Images/tileset.png", sf::Vector2u(32, 32), level, 9, 9))
		throw std::exception("error while loading tileset!");

	return new_map;
}

// Sorted-Draw-List
static std::map<const int, sf::Drawable*> DrawableObjects;
// Update-List
static std::vector<Updatable*> UpdatableObjects;

int main() {
	sf::RenderWindow window(sf::VideoMode(288, 288), "Pathfinder");

	// Create Map
	auto map = CreateMap();
	DrawableObjects.emplace(-1, &map);

	// Create Character
	auto problemSolver = CreateCharacter();
	DrawableObjects.emplace(10, &problemSolver);
	UpdatableObjects.push_back(&problemSolver);

	// create clock to keep track of frame deltas. 
	sf::Clock clock;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		// Restart clock and get the time passed since last frame. 
		sf::Time deltaTime = clock.restart();
		// Clear all drawn objects from previous frame
		window.clear();

		// Update Objects
		for (auto updatebleObject : UpdatableObjects) {
			updatebleObject->update(deltaTime.asSeconds());
		}

		// Render Objects
		for (auto drawableObject : DrawableObjects) {
			window.draw(*drawableObject.second);
		}

		window.display();
	}

	return 0;
}