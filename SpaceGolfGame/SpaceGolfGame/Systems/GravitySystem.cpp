#include "GravitySystem.h"
#include "../Components/GravityComponent.h"
#include "../Components/VelocityComponent.h"
#include "../Components/PositionComponent.h"
#include "../Components/PlanetComponent.h"
#include "../Components/MassComponent.h"

GravitySystem::GravitySystem(float constant) : constant(constant)
{
}


GravitySystem::~GravitySystem()
{
}

void GravitySystem::update(entityx::EntityManager & entities, entityx::EventManager & events, entityx::TimeDelta dt)
{
	entities.each<GravityComponent, VelocityComponent, PositionComponent, MassComponent>([this, dt, &entities](entityx::Entity &entity, GravityComponent &gravity, VelocityComponent &velocity, PositionComponent& position, MassComponent& m1) {
		Vector2f force;
		entities.each<PlanetComponent, PositionComponent, MassComponent>([&force, &m1, &position](entityx::Entity &planetEntity, PlanetComponent &planet, PositionComponent &planetPosition, MassComponent &m2) {
			float forceLength = m1.m * m2.m / (position.pos - planetPosition.pos).lengthSq();
			Vector2f tempForce = (planetPosition.pos - position.pos);
			tempForce.normalize();
			tempForce *= forceLength;
			force += tempForce;
		});
		velocity.v += force * this->constant;
	});
}
