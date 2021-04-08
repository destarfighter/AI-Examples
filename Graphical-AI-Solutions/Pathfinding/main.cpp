#include <SFML/Graphics.hpp>
#include "TileMap.h"
#include "Loader.h"
#include "LittleProblemSolver.h"
#include "WorldState.hpp"
#include "WorldStateLocator.h"
#include "Maze.h"

using namespace Loader;

int main() {
	sf::RenderWindow window(sf::VideoMode(288, 288), "Pathfinder");

	// Create provider for worldState and add to WorldState Service Locator 
	WorldStateProvider* worldState = new WorldStateProvider();
	WorldStateLocator::initialize();
	WorldStateLocator::provide(worldState);

	// Create MapData
	auto mapData = CreateMapData();

	// Create Map
	auto map = CreateMaze(mapData);
	worldState->addNewObject({ "map", -1 }, std::make_shared<Maze>(map), true, false);

	// Create Character
	auto problemSolver = CreateCharacter(mapData);
	worldState->addNewObject({ "ai-character", 10 }, std::make_shared<LittleProblemSolver>(problemSolver), true, true);

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
		for (auto obj_ptr : worldState->getUpdatables()) {
			obj_ptr.second->update(deltaTime.asSeconds());
		}

		// Render Objects
		for (auto obj_ptr : worldState->getDrawables()) {
			obj_ptr.second->draw(window);
		}

		window.display();
	}

	return 0;
}