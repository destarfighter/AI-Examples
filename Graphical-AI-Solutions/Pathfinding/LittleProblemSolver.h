#pragma once
#include <map>
#include "AnimatedSprite.h"
#include "AIState.h"
#include "AIController.h"

class LittleProblemSolver : public AnimatedSprite {
private:
	// Controller for behavior state machine. 
	//AIController aiController_;
	// mapping for animation states in the AnimatedSprite, name of animation - index of animation in AnimData
	//std::map<std::string, int> animationStates_;
	// position of character
	//sf::Vector2f position_;
	// Inherited via Updatable
	virtual void update(float deltaTime) override;
public: 
	void initialize(AnimData animData, unsigned int startingAnimNum);

#pragma region friend-Classes "States"
	friend class SolveProblemState;
	friend class FollowPathState;
	friend class ShowResultState;
#pragma endregion
};

