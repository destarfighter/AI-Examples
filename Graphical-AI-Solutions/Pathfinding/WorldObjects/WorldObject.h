#pragma once
#include <SFML/Graphics.hpp>

struct WorldObjectIdentifier {
	std::string name_;
	int priority_;

	friend bool operator==(const WorldObjectIdentifier& lhs, const WorldObjectIdentifier& rhs) {
		return lhs.name_ == rhs.name_;
	}
	friend bool operator<(const WorldObjectIdentifier& lhs, const WorldObjectIdentifier& rhs) {
		if (rhs.priority_ == lhs.priority_) {
			return lhs.name_ < rhs.name_;
		}
		else {
			return lhs.priority_ < rhs.priority_;
		}
	}
};

class WorldObject {
public:
	virtual void update(float deltaTime) { /* Do Nothing */ };
	virtual void draw(sf::RenderWindow& window) { /* Do Nothing */ };
};