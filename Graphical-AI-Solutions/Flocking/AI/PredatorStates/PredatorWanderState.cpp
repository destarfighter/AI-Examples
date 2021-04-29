#include "PredatorWanderState.h"

void PredatorWanderState::update(float deltaTime)
{
}

void PredatorWanderState::enter()
{
}

void PredatorWanderState::exit()
{
}

PredatorWanderState::PredatorWanderState(AIController* parent, AnimatedSprite* owner)
	: AnimalState(parent, owner) { }
