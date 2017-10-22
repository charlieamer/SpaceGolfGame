#pragma once
#include <entityx/System.h>
#include <vmath.h>
#include "PlanetCacheBaseSystem.h"

#define FORCE_FIELD_RESOLUTION 100

class GravitySystem
	: public entityx::System<GravitySystem>,
	  public PlanetCacheBaseSystem
{
	float constant;
    Vector2f topLeftExtent;
    Vector2f increment;
    Aabb3f extents;
    Vector2f forceField[FORCE_FIELD_RESOLUTION][FORCE_FIELD_RESOLUTION];
public:
	GravitySystem(float constant, Aabb3f extents);

	// Inherited via System
	virtual void update(entityx::EntityManager & entities, entityx::EventManager & events, entityx::TimeDelta dt) override;
	Vector2f forceAtPosition(Vector2f position);
    bool isInPlanet(Vector2f position);
};

