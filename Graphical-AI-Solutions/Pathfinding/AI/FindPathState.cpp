#include "FindPathState.h"

ProblemDefinition FindPathState::generateRandomProblem(sf::Vector2f characterPosition, int mapHeight, int mapWidth, int amountOfWalls)
{
	srand(time(NULL));
	// create base n x n tile
	std::vector<int> tileData(mapHeight * mapWidth, 0);
	
	// randomize walls locations
	for (unsigned int i = 0; i < amountOfWalls; ++i) {
		tileData[rand() % tileData.size()] = 1;
	}
	
	// set random destination
	int destination = rand() % tileData.size();
	sf::Vector2u newDestination(destination % mapWidth, destination / mapWidth);
	tileData[destination] = 3;
	
	// set current position to be open
	tileData[((characterPosition.y / TILESIZE) * mapWidth) + (characterPosition.x / TILESIZE)] = 0;
	
	auto newProblem = ProblemDefinition{ MapData { sf::Vector2u(32, 32), tileData, 9, 9 }, newDestination };
	return newProblem;
}

void FindPathState::update(float deltaTime) {
	if (path_._Is_ready()) {
		if (pathfinder_.getFoundPath()) {
			parent_->setState(new FollowPathState(parent_, owner_, path_.get()));
		}
		else {
			parent_->setState(new ShowResultState(parent_, owner_, false));
		}
	}
}

void FindPathState::enter() {
	// if no problem was provided generate a new problem
	problemDefinition_ = generateRandomProblem(owner_->getPosition(), MAP_WIDTH, MAP_HEIGHT, AMOUNT_OF_WALLS);
	
	// find maze object in worlState
	WorldState* worldState = WorldStateLocator::getWorldState();
	auto mazeId = worldState->getObjectId(MAP_NAME);
	auto maze = worldState->getObject(mazeId);
	
	// Cast to Maze and call setMapData with problem update	
	std::static_pointer_cast<Maze>(maze)->setMapData(problemDefinition_.mapData);

	path_ = std::async(&Pathfinder::findPath, &pathfinder_, owner_->getPosition(), problemDefinition_.destination, problemDefinition_.mapData);
}

FindPathState::FindPathState(AIController* parent, AnimatedSprite* owner, ProblemDefinition problemDefinition)
	: ProblemSolverState(parent, owner)
	, problemDefinition_(problemDefinition) { }
