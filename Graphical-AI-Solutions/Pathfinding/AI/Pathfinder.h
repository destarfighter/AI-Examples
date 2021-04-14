#pragma once
#include <SFML/System/Vector2.hpp>
#include <vector>
#include <queue>
#include <stack>
#include <climits>
#include <future>
#include "../Data/MapPackage.h"
#include "../config.h"

enum Direction
{
	UP = 0,
	DOWN = 1,
	LEFT = 2,
	RIGHT = 3
};

struct Step {
	Direction direction;
	long int step_value;
};

struct Position
{
	// describes a point in a 2D-grid of "FindPath"- nMapWidth and nMapHeight
	long int pos;  
	// tentative distance from a source to pos. and manhattan distance from position to target
	long int dist; 

	friend bool operator<(const Position& lhs, const Position& rhs)
	{
		// TODO: include h_value to this operator. 
		// compare is reversed due to smaller being better
		return lhs.dist > rhs.dist;
	}
};

class Pathfinder {
private:
	bool foundPath_{ false };

	bool isTraversable(const long int prev_pos, const Step& direction, MapData mapData);
	std::vector<unsigned long int> makePath(const long int target, const long int start, std::vector<long int>& prev);
	long int manhattanDistance(long int position, long int target);

public:
	std::vector<unsigned long int> findPath(sf::Vector2f startPosition, sf::Vector2u destination, MapData mapData);
	const bool getFoundPath() const noexcept { return foundPath_; }
};

