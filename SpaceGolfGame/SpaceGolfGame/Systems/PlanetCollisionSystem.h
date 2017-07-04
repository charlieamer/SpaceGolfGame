#pragma once

#include <entityx/System.h>
#include "PlanetCacheBaseSystem.h"

class PlanetCollisionSystem
	: public entityx::System<PlanetCollisionSystem>,
	  public PlanetCacheBaseSystem
{
public:
	PlanetCollisionSystem();
	~PlanetCollisionSystem();

	// Inherited via System
	virtual void update(entityx::EntityManager & entities, entityx::EventManager & events, entityx::TimeDelta dt) override;
};

