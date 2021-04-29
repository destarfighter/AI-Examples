#include "SheepSeparateState.h"

void SheepSeparateState::update(float deltaTime)
{
}

void SheepSeparateState::enter()
{
}

void SheepSeparateState::exit()
{
}

SheepSeparateState::SheepSeparateState(AIController* parent, AnimatedSprite* owner)
	: AnimalState(parent, owner) { }
