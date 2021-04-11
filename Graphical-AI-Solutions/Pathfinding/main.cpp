#include <SFML/Graphics.hpp>
#include "Services/WorldState.hpp"
#include "Services/WorldStateLocator.h"
#include "WorldObjects/ProblemSolver.h"
#include "WorldObjects/Maze.h"
#include "Data/MapPackage.h"
#include "WorldObjects/ProblemSolverStates.hpp"

std::shared_ptr<sf::Texture> loadTexture(std::string texturePath) {
	auto texture_ptr = std::make_shared<sf::Texture>();
	if (!texture_ptr->loadFromFile(texturePath))
		throw std::exception("Failed to load image from file.");
	return texture_ptr;
}

std::shared_ptr<ProblemSolver> createProblemSolver() {
	auto texture = loadTexture("Resources/Images/Positiv Animation Sheet.png");
	texture->setSmooth(true);
	texture->setRepeated(false);

	auto frameInfo = std::vector<AnimFrameData>();
	frameInfo.push_back(AnimFrameData{ sf::Rect<int>(6 * 48, 0, 48, 48), 5, "celebrate" });
	AnimData animData{ texture, frameInfo, 1 };

	auto new_character = ProblemSolver();
	new_character.initialize(animData, 0, sf::Vector2f(0.f, 0.f));

	return std::make_shared<ProblemSolver>(new_character);
}

 std::shared_ptr<Maze> createEmptyMaze() {
	// Create map
	std::vector<int> map(90, 0);
	MapData mapData{ sf::Vector2u(32, 32), map, 9, 9 };

	// Create maze
	auto maze = Maze();
	maze.initialize("Resources/Images/tileset.png", mapData);

	return std::make_shared<Maze>(maze);
}

int main() {
	sf::RenderWindow window(sf::VideoMode(288, 288), "Pathfinder");

	// Create provider for worldState and add to WorldState-Service-Locator 
	WorldStateProvider* worldState = new WorldStateProvider();
	WorldStateLocator::provide(worldState);

	// Create Map
	auto maze = createEmptyMaze();
	worldState->addNewObject({ "maze", -1 }, maze, true, false);

	// Create Character
	auto problemSolver = createProblemSolver();
	worldState->addNewObject({ "ai-character", 10 }, problemSolver, true, true);

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