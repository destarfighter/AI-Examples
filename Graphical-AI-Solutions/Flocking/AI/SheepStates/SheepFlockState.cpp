#include "SheepFlockState.h"

void SheepFlockState::update(float deltaTime)
{
}

void SheepFlockState::enter()
{
}

void SheepFlockState::exit()
{
}

SheepFlockState::SheepFlockState(AIController* parent, AnimatedSprite* owner)
	: AnimalState(parent, owner) { }