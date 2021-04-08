#pragma once
#include <map>
#include "WorldObject.hpp"

class WorldState {
public:
	virtual ~WorldState() { }
	virtual void addNewObject(WorldObjectIdentifier id, std::shared_ptr<WorldObject> obj_ptr, bool isDrawable = false, bool isUpdatable = false) = 0;
	virtual void removeObject(WorldObjectIdentifier id) = 0;
	virtual std::shared_ptr<WorldObject> getObject(WorldObjectIdentifier id) = 0;
	virtual std::map<WorldObjectIdentifier, std::shared_ptr<WorldObject>>& getDrawables() = 0;
	virtual std::map<WorldObjectIdentifier, std::shared_ptr<WorldObject>>& getUpdatables() = 0;
};

class WorldStateProvider : public WorldState {
	// Drawable collection
	std::map<WorldObjectIdentifier, std::shared_ptr<WorldObject>> drawableObjects_;
	// Updatable collection
	std::map<WorldObjectIdentifier, std::shared_ptr<WorldObject>> updatableObjects_;

public: // TODO: Make sure that a unique id is created / provided!
	virtual void addNewObject(WorldObjectIdentifier id, std::shared_ptr<WorldObject> obj_ptr, bool isDrawable = false, bool isUpdatable = false) {
		if (isDrawable) drawableObjects_.emplace(id, obj_ptr);
		if (isUpdatable) updatableObjects_.emplace(id, obj_ptr);
	};

	virtual void removeObject(WorldObjectIdentifier id) {
		drawableObjects_.erase(id);
		updatableObjects_.erase(id);
	};

	virtual std::shared_ptr<WorldObject> getObject(WorldObjectIdentifier id) {
		return std::make_shared<WorldObject>(WorldObject()); // TODO: Implement get function
	};

	virtual std::map<WorldObjectIdentifier, std::shared_ptr<WorldObject>>& getDrawables() { return drawableObjects_; };

	virtual std::map<WorldObjectIdentifier, std::shared_ptr<WorldObject>>& getUpdatables() { return updatableObjects_; }
};

class NullWorldState : public WorldState {
public:
	virtual void addNewObject(WorldObjectIdentifier id, std::shared_ptr<WorldObject> obj_ptr, bool isDrawable = false, bool isUpdatable = false) {};
	virtual void removeObject(WorldObjectIdentifier id) {};
	virtual std::shared_ptr<WorldObject> getObject(WorldObjectIdentifier id) { return nullptr; };
	virtual std::map<WorldObjectIdentifier, std::shared_ptr<WorldObject>>& getDrawables() {
		auto empty = std::map<WorldObjectIdentifier, std::shared_ptr<WorldObject>>();
		return empty;
	};
	virtual std::map<WorldObjectIdentifier, std::shared_ptr<WorldObject>>& getUpdatables() {
		auto empty = std::map<WorldObjectIdentifier, std::shared_ptr<WorldObject>>();
		return empty;
	};
};