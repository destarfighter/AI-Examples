#include "PredatorChaseState.h"

void PredatorChaseState::update(float deltaTime)
{
}

void PredatorChaseState::enter()
{
}

void PredatorChaseState::exit()
{
}

PredatorChaseState::PredatorChaseState(AIController* parent, AnimatedSprite* owner, Kinematic* ownerKinematic)
: AnimalState(parent, owner, ownerKinematic) { }
