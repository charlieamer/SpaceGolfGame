#pragma once
#include <entityx/System.h>
#include <vmath.h>
#include "PlanetCacheBaseSystem.h"

class GravitySystem
	: public entityx::System<GravitySystem>,
	  public PlanetCacheBaseSystem
{
	float constant;
public:
	GravitySystem(float constant);
	~GravitySystem();

	// Inherited via System
	virtual void update(entityx::EntityManager & entities, entityx::EventManager & events, entityx::TimeDelta dt) override;
	Vector2f forceAtPosition(Vector2f position);
    bool isInPlanet(Vector2f position);
};

