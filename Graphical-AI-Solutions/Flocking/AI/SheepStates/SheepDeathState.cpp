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

SheepDeathState::SheepDeathState(AIController* parent, AnimatedSprite* owner, Kinematic* ownerKinematic)
	: AnimalState(parent, owner, ownerKinematic) { }
