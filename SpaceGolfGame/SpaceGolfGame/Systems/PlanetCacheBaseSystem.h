#pragma once

#include <vector>
#include <entityx/Entity.h>

class PlanetCacheBaseSystem
{
protected:
	std::vector<entityx::Entity> planets;
	bool populatePlanets(entityx::EntityManager & entities, bool force = false);
};

