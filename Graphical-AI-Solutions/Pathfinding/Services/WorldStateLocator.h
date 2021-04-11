#pragma once
#include <stdlib.h>
#include "../Services/WorldState.hpp"

class WorldStateLocator {
public:
	static WorldState* getWorldState() { return service_; };

	static void provide(WorldState* service) {
		service_ = service;
	}

private:
	static WorldState* service_;
};
