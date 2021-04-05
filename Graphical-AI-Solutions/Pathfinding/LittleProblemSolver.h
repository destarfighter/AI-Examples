#pragma once
#include <map>
#include "AnimatedSprite.h"
#include "AIState.h"
#include "AIController.h"
#include "TileMap.h"

class LittleProblemSolver : public AnimatedSprite {

	// Controller for behavior state machine. 
	AIController ai_controller_;
	// mapping for animation states in the AnimatedSprite
	std::map<std::string, int> animationStates_;
	// int representation of map
	MapData mapData_;
	// position of character
	sf::Vector2f position;

	// Inherited via Updatable
	virtual void update(float deltaTime) override;

public: 

	void initialize(AnimData _animData, unsigned int _startingAnimNum, MapData mapData);


#pragma region friend-Classes "States"
	friend class SolveProblemState;
	friend class FollowPathState;
	friend class ShowResultState;
#pragma endregion
};

