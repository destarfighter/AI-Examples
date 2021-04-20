#pragma once
#include "WorldObject.h"

class DerivedFromWorldObject : public WorldObject {
	WorldObjectIdentifier id_;
public:
	DerivedFromWorldObject(WorldObjectIdentifier id)
		: id_(id) {};

	WorldObjectIdentifier getId() { return id_; }
};

