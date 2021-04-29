#include "SheepDeathState.h"

void SheepDeathState::update(float deltaTime)
{
}

void SheepDeathState::enter()
{
}

void SheepDeathState::exit()
{
}

SheepDeathState::SheepDeathState(AIController* parent, AnimatedSprite* owner)
	: AnimalState(parent, owner) { }
