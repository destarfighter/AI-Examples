#include "SheepFleeState.h"

void SheepFleeState::update(float deltaTime)
{
}

void SheepFleeState::enter()
{
}

void SheepFleeState::exit()
{
}

SheepFleeState::SheepFleeState(AIController* parent, AnimatedSprite* owner)
	: AnimalState(parent, owner) { }
