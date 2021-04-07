#pragma once
#include <SFML/Graphics/WorldObject.hpp>
#include <map>

using objectContainer = std::map<sf::WorldObjectIdentifier, std::shared_ptr<sf::WorldObject>>;

class WorldState {
public:
	virtual ~WorldState() { }
	virtual void addNewObject(sf::WorldObject obj, bool isDrawable = false, bool isUpdatable = false) = 0;
	virtual void removeObject(sf::WorldObjectIdentifier id) = 0;
	virtual std::shared_ptr<sf::WorldObject> getObject(sf::WorldObjectIdentifier id) = 0;
	virtual objectContainer& getDrawables() = 0;
	virtual objectContainer& getUpdatables() = 0;
};

class WorldStateProvider : public WorldState {
	// WorldObjects collection
	objectContainer worldObjects_;
	// DrawableObjects collection
	objectContainer drawableObjects_;
	// Updatable collection
	objectContainer updatableObjects_;

public:
	virtual void addNewObject(sf::WorldObject obj, bool isDrawable = false, bool isUpdatable = false) {
		auto obj_ptr = std::make_shared<sf::WorldObject>(obj);
		if (isDrawable) drawableObjects_.emplace(obj.getIdentity(), obj_ptr);
		if (isUpdatable) updatableObjects_.emplace(obj.getIdentity(), obj_ptr);
		worldObjects_.emplace(obj.getIdentity(), obj_ptr);
	};

	virtual void removeObject(sf::WorldObjectIdentifier id) {
		worldObjects_.erase(id);
		drawableObjects_.erase(id);
		updatableObjects_.erase(id);
	};

	virtual std::shared_ptr<sf::WorldObject> getObject(sf::WorldObjectIdentifier id) {
		return worldObjects_[id];
	};

	virtual objectContainer& getDrawables() { return drawableObjects_; };

	virtual objectContainer& getUpdatables() { return updatableObjects_; }
};

class NullWorldState : public WorldState {
public:
	virtual void addNewObject(sf::WorldObject obj, bool isDrawable = false, bool isUpdatable = false) {};
	virtual void removeObject(sf::WorldObjectIdentifier id) {};
	virtual std::shared_ptr<sf::WorldObject> getObject(sf::WorldObjectIdentifier id) { return nullptr; };
	virtual objectContainer& getDrawables() { 
		auto empty = objectContainer();
		return empty;
	};
	virtual objectContainer& getUpdatables() {
		auto empty = objectContainer();
		return empty;
	};
};