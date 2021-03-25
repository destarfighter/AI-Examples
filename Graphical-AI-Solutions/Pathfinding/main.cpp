#include <SFML/Graphics.hpp>
#include <thread>
#include "AnimatedSprite.h"


void renderingThread(sf::RenderWindow* window) {
	window->setActive(true);

	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Red);

	while (window->isOpen()) {
		window->clear();
		
		// draw problem graphical representation
		// draw sorted list of sprites
		window->draw(shape);

		window->display();
	}
}

void workerThread() {
	// solve problem
	// return solution
}

int main()
{
	// load Images -> Textures -> sprites
	// load problem data

	sf::RenderWindow window(sf::VideoMode(200, 200), "Pathfinder");
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