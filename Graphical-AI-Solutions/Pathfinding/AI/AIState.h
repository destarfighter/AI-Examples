#pragma once

// Forward declaration
class AIController; 

class AIState {
protected:
	AIController* parent_;
public: 
	~AIState() { /* Do Nothing */};
	AIState(AIController* parent)
	: parent_(parent) {};
	virtual void update(float deltaTime) {};
	virtual void enter() {};
	virtual void exit() {};
};

