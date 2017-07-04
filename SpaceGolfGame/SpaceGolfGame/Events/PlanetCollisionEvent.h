#pragma once

#include <entityx/Entity.h>

struct PlanetCollisionEvent {
	PlanetCollisionEvent(entityx::Entity &planet, entityx::Entity &collider, Vector2f entry) : planet(planet), collider(collider), entry(entry) {}
	entityx::Entity &planet, &collider;
	Vector2f entry;
};