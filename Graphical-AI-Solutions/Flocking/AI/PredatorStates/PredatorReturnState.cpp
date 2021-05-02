#include "PredatorReturnState.h"

void PredatorReturnState::update(float deltaTime)
{
}

void PredatorReturnState::enter()
{
}

void PredatorReturnState::exit()
{
}

PredatorReturnState::PredatorReturnState(AIController* parent, AnimatedSprite* owner, Kinematic* ownerKinematic)
: AnimalState(parent, owner, ownerKinematic) { }
