#include "PlanetCollisionSystem.h"
#include "../Components/PlanetCollisionComponent.h"
#include "../Components/PlanetComponent.h"
#include "../Components/PositionComponent.h"
#include "../Components/CircleRadiusComponent.h"
#include "../Events/PlanetCollisionEvent.h"
#include "../utilities.h"

PlanetCollisionSystem::PlanetCollisionSystem()
{
}


PlanetCollisionSystem::~PlanetCollisionSystem()
{
}

void PlanetCollisionSystem::update(entityx::EntityManager & entities, entityx::EventManager & events, entityx::TimeDelta dt)
{
	this->populatePlanets(entities);
	entities.each<PlanetCollisionComponent>([&entities, &events, this](entityx::Entity colliderEntity, PlanetCollisionComponent &planetCollision) {
		for (auto& planetEntity : this->planets) {
			if (Utilities::isColliding(colliderEntity, planetEntity)) {
				if (planetCollision.generateEvent) {
					Vector2f entry;
					if (planetCollision.calculatePointOfEntry) {
						entry = Utilities::getPointOfImpact(planetEntity, colliderEntity);
					}
					events.emit<PlanetCollisionEvent>(planetEntity, colliderEntity, entry);
				}
			}
		}
	});
}
