#pragma once
#include <SFML/Graphics/WorldObject.hpp>
#include <map>

using objectContainer = std::map<sf::WorldObjectIdentifier, std::shared_ptr<sf::WorldObject>>;

class WorldState {
public:
	virtual ~WorldState() { }
	virtual void addNewObject(std::shared_ptr<sf::WorldObject> obj_ptr, bool isDrawable = false, bool isUpdatable = false) = 0;
	virtual void removeObject(sf::WorldObjectIdentifier id) = 0;
	virtual std::shared_ptr<sf::WorldObject> getObject(sf::WorldObjectIdentifier id) = 0;
	virtual objectContainer& getDrawables() = 0;
	virtual objectContainer& getUpdatables() = 0;
};

class WorldStateProvider : public WorldState {

	// TODO: redesign containers. remove code from SFML-Lib and design common container in project instead. 

	// WorldObjects collection
	objectContainer worldObjects_; // TODO: Remove list, and only keep drawables and updatables
	// DrawableObjects collection
	objectContainer drawableObjects_;
	// Updatable collection
	objectContainer updatableObjects_;

public: // TODO: Make sure that a unique id is created / provided!
	virtual void addNewObject(std::shared_ptr<sf::WorldObject> obj_ptr, bool isDrawable = false, bool isUpdatable = false) {
		if (isDrawable) drawableObjects_.emplace(obj_ptr->getIdentity(), obj_ptr);
		if (isUpdatable) updatableObjects_.emplace(obj_ptr->getIdentity(), obj_ptr);
		worldObjects_.emplace(obj_ptr->getIdentity(), obj_ptr);
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
	virtual void addNewObject(std::shared_ptr<sf::WorldObject> obj_ptr, bool isDrawable = false, bool isUpdatable = false) {};
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