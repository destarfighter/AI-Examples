#include "SheepFlockState.h"

void SheepFlockState::update(float deltaTime) {

	// get steering from steeringblender

	// get position and rotation from kinematic

	// set position and rotation with Animator
}

void SheepFlockState::enter() {
}

void SheepFlockState::exit() {
}

SheepFlockState::SheepFlockState(AIController* parent, AnimatedSprite* owner, Kinematic* ownerKinematic)
	: AnimalState(parent, owner, ownerKinematic) { }