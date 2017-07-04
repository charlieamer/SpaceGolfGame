#include "GravitySystem.h"
#include "../Components/GravityComponent.h"
#include "../Components/VelocityComponent.h"
#include "../Components/PositionComponent.h"
#include "../Components/PlanetComponent.h"
#include "../Components/MassComponent.h"
#include "../Components/DynamicMeshComponent.h"

GravitySystem::GravitySystem(float constant) : constant(constant)
{
}


GravitySystem::~GravitySystem()
{
}

void GravitySystem::update(entityx::EntityManager & entities, entityx::EventManager & events, entityx::TimeDelta dt)
{
	this->populatePlanets(entities);
	entities.each<GravityComponent, VelocityComponent, PositionComponent, MassComponent>([this, &entities]
			(entityx::Entity &entity, GravityComponent &gravity, VelocityComponent &velocity, PositionComponent& position, MassComponent& m1) {
		Vector2f force = GravitySystem::forceAtPosition(position.pos);
		velocity.v += force * this->constant * m1.m;
	});
	entities.each<GravityComponent, VelocityComponent, MassComponent, DynamicMeshComponent>([this, &entities]
			(entityx::Entity &entity, GravityComponent &gravity, VelocityComponent &velocity, MassComponent &mass, DynamicMeshComponent &mesh) {
		Vector2f tempVelocity = velocity.v;
		Vector2f tempPosition = Vector2f(mesh.vertices[0].m_x, mesh.vertices[0].m_y);
		for (int i = 1; i < mesh.indices.size(); i++) {
			Vector2f force = GravitySystem::forceAtPosition(tempPosition);
			tempVelocity += force * this->constant * mass.m;
			tempPosition += tempVelocity;
			mesh.vertices[i] = Pos2fColorVertex(tempPosition);
		}
		mesh.verticesValid = false;
	});
}

Vector2f GravitySystem::forceAtPosition(Vector2f position)
{
	Vector2f force;
	for (auto& entity : this->planets) {
		float m = entity.component<MassComponent>()->m;
		Vector2f &pos = entity.component<PositionComponent>()->pos;
		float forceLength = m / (position - pos).lengthSq();
		Vector2f tempForce = (pos - position);
		tempForce.normalize();
		tempForce *= forceLength;
		force += tempForce;
	};
	return force;
}
