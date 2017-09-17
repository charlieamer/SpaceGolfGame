#include "PlanetCacheBaseSystem.h"
#include "../Components/PositionComponent.h"
#include "../Components/MassComponent.h"
#include "../Components/PlanetComponent.h"

void PlanetCacheBaseSystem::populatePlanets(entityx::EntityManager & entities, bool force)
{
	if (force) {
		planets.clear();
	}
	if (planets.size() == 0) {
		entities.each<PositionComponent, MassComponent, PlanetComponent>([this](entityx::Entity entity, PositionComponent&, MassComponent&, PlanetComponent&) {
			this->planets.push_back(entity);
		});
	}
}
