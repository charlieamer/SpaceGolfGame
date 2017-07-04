#include "BounceSystem.h"

#include "../Components/PositionComponent.h"
#include "../Components/AABBCacheComponent.h"
#include "../Components/VelocityComponent.h"
#include "../Components/PlanetCollisionComponent.h"
#include "../Events/PlanetCollisionEvent.h"
#include <vmath.h>

BounceSystem::BounceSystem(Aabb3f* extents) : extents(extents)
{
}


BounceSystem::~BounceSystem()
{
}

void BounceSystem::update(entityx::EntityManager & entities, entityx::EventManager & events, entityx::TimeDelta dt)
{
	entities.each<PositionComponent, VelocityComponent>([this](entityx::Entity &entity, PositionComponent &position, VelocityComponent &velocity) {
		Aabb3f aabb;
		if (entity.component<AABBCacheComponent>()) {
			aabb = entity.component<AABBCacheComponent>().get()->AABB;
		}
		float diffRight = position.pos.x + aabb.max.x - this->extents->max.x;
		if (diffRight >= 0) {
			position.pos.x = this->extents->max.x - aabb.max.x - diffRight;
			velocity.v.x *= -1.0f;
		}
		float diffLeft = position.pos.x + aabb.min.x - this->extents->min.x;
		if (diffLeft <= 0) {
			position.pos.x = this->extents->min.x - aabb.min.x - diffLeft;
			velocity.v.x *= -1.0f;
		}
		float diffBottom = position.pos.y + aabb.max.y - this->extents->max.y;
		if (diffBottom >= 0) {
			position.pos.y = this->extents->max.y - aabb.max.y - diffBottom;
			velocity.v.y *= -1.0f;
		}
		float diffTop = position.pos.y + aabb.min.y - this->extents->min.y;
		if (diffTop <= 0) {
			position.pos.y = this->extents->min.y - aabb.min.y - diffTop;
			velocity.v.y *= -1.0f;
		}
	});
}

void BounceSystem::configure(entityx::EventManager & manager)
{
	manager.subscribe<PlanetCollisionEvent>(*this);
}

void BounceSystem::receive(const PlanetCollisionEvent & collision)
{
	Vector2f &v = collision.collider.component<VelocityComponent>()->v;
	Vector2f &p = collision.collider.component<PositionComponent>()->pos;
	Vector2f &planet = collision.planet.component<PositionComponent>()->pos;
	Vector2f relativeEntry = collision.entry - planet;

	v = v.reflect(relativeEntry);

	Vector2f vNorm = v;
	vNorm.normalize();
	p = collision.entry + vNorm * (v.length() - (collision.entry - p).length());

	v *= collision.collider.component<PlanetCollisionComponent>()->damping;
}
