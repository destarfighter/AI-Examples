#pragma once
#include <stdlib.h>
#include "../Services/WorldState.hpp"

class WorldStateLocator {
public:
	static void initialize() {
		service_ = &nullService_;
	}

	static WorldState& getWorldState() { return *service_; };

	static void provide(WorldState* service) {
		// Revert to null service.
		if (service == NULL) service = &nullService_;

		service_ = service;
	}

private:
	static WorldState* service_;
	static NullWorldState nullService_;
};
