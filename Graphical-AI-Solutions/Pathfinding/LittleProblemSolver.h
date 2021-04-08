#pragma once
#include <map>
#include "AnimatedSprite.h"
#include "AIState.h"
#include "AIController.h"

class LittleProblemSolver : public WorldObject {
private:
	// Controller for behavior state machine. 
	AIController aiController_;
	// Graphics component to draw an animated sprite from sprite-sheet
	AnimatedSprite animatedSprite_;
	// mapping for animation states in the AnimatedSprite, name of animation - index of animation in AnimData
	std::map<std::string, int> animationStates_;
	// position of character
	sf::Vector2f position_;
public:
	void initialize(AnimData animData, unsigned int startingAnimNum, sf::Vector2f startPosition);
	virtual void update(float deltaTime) override;
	virtual void draw(sf::RenderWindow& window) override;

#pragma region friend-Classes "States"
	friend class SolveProblemState;
	friend class FollowPathState;
	friend class ShowResultState;
#pragma endregion
};

