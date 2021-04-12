#pragma once
#include <SFML/System/Vector2.hpp>
#include <vector>
#include <queue>
#include <stack>
#include <climits>
#include "../Data/MapPackage.h"

enum PathfinderStates {
	IS_IDLE = 0,
	IS_WORKING = 1,
	IS_READY = 2
};

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
	// tentative distance from a source to pos. 
	long int dist; 
	// distance from current position to target.
	long int h_value;

	friend bool operator<(const Position& lhs, const Position& rhs)
	{
		// TODO: include h_value to this operator. 
		// compare is reversed due to smaller being better
		return lhs.dist > rhs.dist;
	}
};

// TODO: clean way to reset Pathfinder? 

class Pathfinder {
private:
	PathfinderStates state_ {IS_IDLE};
	bool foundPath_{ false };

	bool IsTraversable(const long int& prev_pos, const Step& direction, MapData mapData);
	std::vector<unsigned long int> MakePath(const long int& target, const long int& start, std::vector<long int>& prev);

public:
	std::vector<unsigned long int> findPath(sf::Vector2f startPosition, sf::Vector2u destination, MapData mapData);
	const PathfinderStates getState() const noexcept { return state_; }
	const bool getFoundPath() const noexcept { return foundPath_; }
};

