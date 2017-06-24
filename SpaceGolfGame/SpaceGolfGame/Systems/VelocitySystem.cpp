#include "VelocitySystem.h"

#include "../Components/VelocityComponent.h"
#include "../Components/PositionComponent.h"
#include "../Components/MeshTransformCacheComponent.h"

VelocitySystem::VelocitySystem()
{
}


VelocitySystem::~VelocitySystem()
{
}

void VelocitySystem::update(entityx::EntityManager & entities, entityx::EventManager & events, entityx::TimeDelta dt)
{
	entities.each<PositionComponent, VelocityComponent>([dt](entityx::Entity& entity, PositionComponent& position, VelocityComponent& velocity) {
		if (velocity.v.lengthSq() > 0) {
			position.pos += velocity.v * dt;
			if (entity.component<MeshTransformCacheComponent>()) {
				entity.component<MeshTransformCacheComponent>().get()->valid = false;
			}
		}
	});
}
