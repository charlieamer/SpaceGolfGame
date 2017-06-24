#include "CircleEntity.h"

entityx::Entity CreateCircleEntity(entityx::EntityManager & manager, Vector2f position, float radius)
{
	entityx::Entity entity = manager.create();
	entity.assign<PositionComponent>(position);
	entity.assign<CircleRadiusComponent>(radius);
	return entity;
}
