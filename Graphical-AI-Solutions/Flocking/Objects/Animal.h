#include "WorldObject.h"
#include "AIController.h"
#include "AnimatedSprite.h"
#include "../AI/AnimalStates.h"
#include "../Flocking/Semi-Primitives/Kinematic.h"

class Animal : public WorldObject, public Kinematic {
private:
	AIController* aiController_;
	AnimatedSprite* animatedSprite_;

public:
	Animal();
	~Animal();
	void initialize(AnimData animData, unsigned int startingAnimNum, sf::Vector2f startPosition, AnimalState* startingState, float startRotation);
	virtual void update(float deltatime) override;
	virtual void draw(sf::RenderWindow& window) override;
};