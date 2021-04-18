#include "FindPathState.h"

ProblemDefinition FindPathState::generateRandomProblem(sf::Vector2f characterPosition)
{
	srand(time(NULL));
	// create base n x n tile
	std::vector<int> tileData(MAP_HEIGHT * MAP_WIDTH, FLOOR_TILE_INDEX);
	
	// randomize walls locations
	for (unsigned int i = 0; i < AMOUNT_OF_WALLS; ++i) {
		tileData[rand() % tileData.size()] =  MAP_WALLS[rand() % MAP_WALLS.size()];
	}
	
	// set random destination // TODO: seems like destination sometimes tries to place itself outside of map. 
	int destination = rand() % tileData.size();
	sf::Vector2u newDestination(destination % MAP_WIDTH, destination / MAP_WIDTH);
	tileData[destination] = TARGET_TILE_INDEX;
	
	// set current position to be open
	tileData[((characterPosition.y / TILESIZE) * MAP_WIDTH) + (characterPosition.x / TILESIZE)] = START_TILE_INDEX;
	
	auto newProblem = ProblemDefinition{ MapData { sf::Vector2u(TILESIZE, TILESIZE), tileData, MAP_WIDTH, MAP_HEIGHT }, newDestination };
	return newProblem;
}

void FindPathState::update(float deltaTime) {
	if (path_._Is_ready()) {
		if (clock_.getElapsedTime().asSeconds() > waitTime_) {
			parent_->setState(new DrawPathProcessState(parent_, owner_, path_.get(), pathfinder_.getSearchProcess(), pathfinder_.getFoundPath()));
		}
	}
}

void FindPathState::enter() {
	// if no problem was provided generate a new problem
	problemDefinition_ = generateRandomProblem(owner_->getPosition());
	
	// find maze object in worlState
	WorldState* worldState = WorldStateLocator::getWorldState();
	auto mazeId = worldState->getObjectId(MAP_NAME);
	auto maze = worldState->getObject(mazeId);
	
	// Cast to Maze and call setMapData with problem update	
	std::static_pointer_cast<Maze>(maze)->setMapData(problemDefinition_.mapData);

	path_ = std::async(&Pathfinder::findPath, &pathfinder_, owner_->getPosition(), problemDefinition_.destination, problemDefinition_.mapData);

	// Set thinking animation
	auto animIndex = owner_->getAnimationByName(IDLE_ANIMATION.animName_);
	owner_->changeAnim(animIndex);

	// Start clock
	clock_.restart();
}

FindPathState::FindPathState(AIController* parent, AnimatedSprite* owner, ProblemDefinition problemDefinition)
	: ProblemSolverState(parent, owner)
	, problemDefinition_(problemDefinition)
	, clock_(sf::Clock())
	, waitTime_(1) { }
