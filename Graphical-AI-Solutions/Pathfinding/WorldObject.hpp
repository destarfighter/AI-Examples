#pragma once
#include <SFML/Graphics.hpp>

struct WorldObjectIdentifier {
	std::string uniqueName_;
	int priority_;

	friend bool operator==(const WorldObjectIdentifier& lhs, const WorldObjectIdentifier& rhs) {
		return lhs.uniqueName_ == rhs.uniqueName_;
	}
	friend bool operator<(const WorldObjectIdentifier& lhs, const WorldObjectIdentifier& rhs) {
		return lhs.priority_ < rhs.priority_;
	}
};

class WorldObject {
public:
	virtual void update(float deltaTime) { /* Do Nothing */};
	virtual void draw(sf::RenderWindow& window) { /* Do Nothing */ };
};