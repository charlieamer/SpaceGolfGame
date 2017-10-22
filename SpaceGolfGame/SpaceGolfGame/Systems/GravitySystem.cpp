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

GravitySystem::GravitySystem(float constant, Aabb3f extents) : constant(constant), extents(extents)
{
    topLeftExtent = Vector2f(extents.min.x, extents.min.y);
    Vector3f extentsExtent = (extents.max - extents.min);
    increment = Vector2f(extentsExtent.x, extentsExtent.y) / (float)FORCE_FIELD_RESOLUTION;
}

void GravitySystem::update(entityx::EntityManager & entities, entityx::EventManager & events, entityx::TimeDelta dt)
{
	if (this->populatePlanets(entities)) {
        for (int i=0; i<FORCE_FIELD_RESOLUTION; i++) {
            for (int j=0; j<FORCE_FIELD_RESOLUTION; j++) {
                Vector2f position = increment * Vector2f(i, j) + topLeftExtent;
                forceField[i][j] = forceAtPosition(position) * this->constant;
            }
        }
    }
	entities.each<GravityComponent, VelocityComponent, PositionComponent, MassComponent>([this]
			(entityx::Entity entity, GravityComponent &gravity, VelocityComponent &velocity, PositionComponent& position, MassComponent& m1) {
        Vector2f force;
        if (gravity.fast) {
            Vector2f forceFieldIndex = (position.pos - this->topLeftExtent) / this->increment;
            force = forceField[Utilities::clamp((int)forceFieldIndex.x, 0, FORCE_FIELD_RESOLUTION - 1)][Utilities::clamp((int)forceFieldIndex.y, 0, FORCE_FIELD_RESOLUTION - 1)];
        } else {
            force = GravitySystem::forceAtPosition(position.pos) * this->constant;
        }
		velocity.v += force * m1.m;
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