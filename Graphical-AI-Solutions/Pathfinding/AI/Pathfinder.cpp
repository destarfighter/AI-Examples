#include "Pathfinder.h"


bool Pathfinder::isTraversable(const long int prev_pos, const Step& step, MapData mapData)
{
	long int new_index = prev_pos + step.step_value;

	switch (step.direction)
	{
	case UP:
		if (new_index < 0) return false; // out-of-bounds: above
		break;
	case DOWN:
		if (new_index >= mapData.width_ * mapData.height_)  return false; // out-of-bounds: under
		break;
	case LEFT:
		if (new_index % mapData.width_ == mapData.width_ - 1 || new_index < 0)  return false; // out-of-bounds: left
		break;
	case RIGHT:
		if (new_index % mapData.width_ == 0 || new_index >= mapData.height_ * mapData.width_)  return false; // out-of-bounds: right
		break;
	}

	for (auto tile : MAP_WALLS) {
		if (mapData.tiles_[new_index] == tile) {
			return false; // Node is not traversable
		}
	}
	return true; // Node is traversable
}

std::vector<unsigned long int> Pathfinder::makePath(const long int target, const long int start, std::vector<long int>& prev)
{
	std::vector<unsigned long int> path;
	long int current = target;

	while (current != start && current != LONG_MAX)
	{
		path.push_back(current);
		current = prev[current];
	}

	// reverse path
	std::reverse(path.begin(), path.end());
	return path;
}

long int Pathfinder::manhattanDistance(long int position, long int target)
{
	// convert values to coordinates
	int positionX = (position % MAP_WIDTH) * TILESIZE;
	int positionY = (position / MAP_WIDTH) * TILESIZE;
	int targetX = (target % MAP_WIDTH)* TILESIZE;
	int targetY = (target / MAP_WIDTH) * TILESIZE;

	// subtract position from target and return absolute value of distance
	return std::abs(targetX - positionX) + std::abs(targetY - positionY);
}

std::vector<unsigned long int> Pathfinder::findPath(sf::Vector2f startPosition, sf::Vector2u destination, MapData mapData) {
	
	std::priority_queue<Position> open_pos_que;
	std::vector<long int> distances_from_start(mapData.height_ * mapData.width_, LONG_MAX);
	std::vector<long int> previous_positions(mapData.height_ * mapData.width_, LONG_MAX);

	long int target = (destination.y * mapData.width_) + destination.x;
	long int start = ((startPosition.y / TILESIZE) * mapData.width_) + (startPosition.x / TILESIZE);

	const Step movement_directions[] = { {UP, -static_cast<long int>(mapData.width_)}, {DOWN, mapData.width_}, {LEFT, -1}, {RIGHT, 1} };
	const int step_cost = 1;

	// Start position need manhattan distance
	auto start_manhattan = manhattanDistance(start, target);
	open_pos_que.push({ start , start_manhattan });
	distances_from_start[start] = start_manhattan;

	while (!open_pos_que.empty())
	{
		Position current = open_pos_que.top();
		open_pos_que.pop();

		if (distances_from_start[current.pos] != current.dist) 
			continue; // position is outdated by another route. 

		if (current.pos == target)
		{
			auto result = makePath(current.pos, start, previous_positions);
			foundPath_ = true;
			return result; // found path from start to target
		}

		for (Step step : movement_directions)
		{
			if (!isTraversable(current.pos, step, mapData)) 
				continue; // Node is not traversable

			long int new_position = current.pos + step.step_value;

			long int new_dist = distances_from_start[current.pos] + step_cost
				+ manhattanDistance(new_position, target);

			if (new_dist < distances_from_start[new_position])
			{
				distances_from_start[new_position] = new_dist;
				previous_positions[new_position] = current.pos;
				open_pos_que.push({ new_position, new_dist });
			}
		}
	}
	foundPath_ = false;
	return std::vector<unsigned long int>(); // found no path from start to target
}
