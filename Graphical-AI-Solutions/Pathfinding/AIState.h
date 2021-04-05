#pragma once

class AIController; // Forward declaration

class AIState {
protected:
	AIController* parent_;
public: 
	virtual void update(float deltaTime) {};
	virtual void enter() {};
	virtual void exit() {};
};

