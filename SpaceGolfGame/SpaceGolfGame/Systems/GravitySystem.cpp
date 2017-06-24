#include "GravitySystem.h"
#include "../Components/GravityComponent.h"
#include "../Components/VelocityComponent.h"

GravitySystem::GravitySystem(float constant) : constant(constant)
{
}


GravitySystem::~GravitySystem()
{
}

void GravitySystem::update(entityx::EntityManager & entities, entityx::EventManager & events, entityx::TimeDelta dt)
{
	entities.each<GravityComponent, VelocityComponent>([this, dt](entityx::Entity &entity, GravityComponent &gravity, VelocityComponent &velocity) {
		velocity.v.y += dt * this->constant;
	});
}
