#pragma once
#include "../WorldObjects/WorldObject.hpp"
#include "../AI/AIController.h"
#include "../Semi-Primitives/AnimatedSprite.h"
#include "../WorldObjects/ProblemSolverStates.hpp"

class ProblemSolver : public WorldObject{
private:
	// Controller for behavior state machine. 
	AIController aiController_;
	// Graphics component to draw an animated sprite from sprite-sheet
	AnimatedSprite animatedSprite_;
	// Mapping for animation states in the AnimatedSprite, name of animation - index of animation in AnimData
	std::map<std::string, int> animationStates_;
	// Position of character
	sf::Vector2f position_;
public:
	ProblemSolver();
	void initialize(AnimData animData, unsigned int startingAnimNum, sf::Vector2f startPosition);
	virtual void update(float deltaTime) override;
	virtual void draw(sf::RenderWindow& window) override;

#pragma region friend-Classes "States"
	friend class AskForProblemState;
	friend class SolveProblemState;
	friend class FollowPathState;
	friend class ShowResultState;
#pragma endregion
};

