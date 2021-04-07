#include <SFML/Graphics.hpp>
#include "TileMap.h"
#include "Loader.h"
#include "LittleProblemSolver.h"
#include "WorldState.hpp"
#include "WorldStateLocator.h"


using namespace Loader;

int main() {
	sf::RenderWindow window(sf::VideoMode(288, 288), "Pathfinder");

	// Create WorldState
	WorldStateProvider* worldState = new WorldStateProvider();
	WorldStateLocator::initialize();
	WorldStateLocator::provide(worldState);

	// Create MapData
	auto mapData = CreateMapData();

	//// Create Map
	auto map = CreateTileMap(mapData);
	worldState->addNewObject(map, true, false);

	////// Create Character
	//auto problemSolver = CreateCharacter(mapData);
	//worldState->addNewObject(problemSolver, true, true);

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

		//// Update Objects
		for (auto uObj : worldState->getUpdatables()) {
			uObj.second->update(deltaTime.asSeconds());
		}

		//// Render Objects
		for (auto dObj : worldState->getDrawables()) {
			window.draw(*dObj.second);
		}

		window.display();
	}

	return 0;
}