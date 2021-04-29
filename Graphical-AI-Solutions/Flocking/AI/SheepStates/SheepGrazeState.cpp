#include "SheepGrazeState.h"

void SheepGrazeState::update(float deltaTime)
{
}

void SheepGrazeState::enter()
{
}

void SheepGrazeState::exit()
{
}

SheepGrazeState::SheepGrazeState(AIController* parent, AnimatedSprite* owner)
	: AnimalState(parent, owner) { }
