#include "GravitySystem.h"
#include "../Components/GravityComponent.h"
#include "../Components/VelocityComponent.h"
#include "../Components/PositionComponent.h"
#include "../Components/PlanetComponent.h"
#include "../Components/MassComponent.h"
#include "../Components/MeshComponent.h"
#include "../Components/AimLineComponent.h"
#include "../Components/CircleRadiusComponent.h"
#include "../utilities.h"
using namespace Debug;

GravitySystem::GravitySystem(float constant) : constant(constant)
{
}


GravitySystem::~GravitySystem()
{
}

void GravitySystem::update(entityx::EntityManager & entities, entityx::EventManager & events, entityx::TimeDelta dt)
{
	this->populatePlanets(entities);
	entities.each<GravityComponent, VelocityComponent, PositionComponent, MassComponent>([this]
			(entityx::Entity entity, GravityComponent &gravity, VelocityComponent &velocity, PositionComponent& position, MassComponent& m1) {
		Vector2f force = GravitySystem::forceAtPosition(position.pos);
		velocity.v += force * this->constant * m1.m;
	});
	entities.each<GravityComponent, VelocityComponent, MassComponent, MeshComponent, AimLineComponent>([this]
			(entityx::Entity entity, GravityComponent &gravity, VelocityComponent &velocity, MassComponent &mass, MeshComponent &mesh, AimLineComponent &aimLine) {
        auto backend = (SolidRenderingBackend<bgfx::IndexBufferHandle, bgfx::DynamicVertexBufferHandle>*)(mesh.getBackend());
        if (backend) {
            Vector2f tempVelocity = velocity.v;
            Vector2f tempPosition = Vector2f(backend->vertices[0].m_x, backend->vertices[0].m_y);
            for (unsigned i = 1; i < backend->indices.size(); i++) {
                if (!isInPlanet(tempPosition)) {
                    Vector2f force = GravitySystem::forceAtPosition(tempPosition);
                    tempVelocity += force * this->constant * mass.m;
                    tempPosition += tempVelocity;
                }
                backend->vertices[i] = Pos2fColorVertex(tempPosition);
            }
            backend->updateVertices();
        }
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

bool GravitySystem::isInPlanet(Vector2f position) {
	for (entityx::Entity& entity : this->planets) {
        if ((position - entity.component<PositionComponent>()->pos).length() < entity.component<CircleRadiusComponent>()->r) {
            return true;
        }
    }
    return false;
}