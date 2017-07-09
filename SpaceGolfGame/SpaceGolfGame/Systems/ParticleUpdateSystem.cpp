#include "ParticleUpdateSystem.h"
#include "../Components/ParticleComponent.h"
#include "../Components/ParticleEmitterComponent.h"
#include "../Components/PositionComponent.h"
#include "../Components/VelocityComponent.h"
#include "../Components/MassComponent.h"
#include "../Components/AABBCacheComponent.h"
#include "../Components/PlanetCollisionComponent.h"
#include "../Components/GravityComponent.h"
#include "../Components/MeshTransformCacheComponent.h"
#include "../Rendering/MeshGenerators.h"
#include "../utilities.h"

void ParticleUpdateSystem::emitParticle(entityx::Entity & entity, entityx::EntityManager & entities, const ParticleEmitterComponent & emitter)
{
	Vector2f& position = entity.component<PositionComponent>()->pos;
	Vector2f velocity = Utilities::getVelocity(entity) * Utilities::random(0, emitter.velocityInfluence) + Utilities::randomVector(-emitter.initialPower, emitter.initialPower);
	entityx::Entity particle = entities.create();
	particle.assign<PositionComponent>(position);
	particle.assign<MassComponent>(emitter.mass);
	particle.assign<ParticleComponent>(Utilities::random(0, emitter.initialLife), emitter.initialLife);
	particle.assign<VelocityComponent>(velocity);
	particle.assign<GravityComponent>();
	particle.assign<MeshTransformCacheComponent>();
	particle.assign<AABBCacheComponent>();
	particle.assign_from_copy<DynamicMeshComponent>(generatePoint(Utilities::abgr(1.0f, 1.0f, 1.0f, 1.0f)));
	particle.component<DynamicMeshComponent>()->renderState |= BGFX_STATE_BLEND_ALPHA;
	particle.assign<PlanetCollisionComponent>(true, true, 0.9);
}

ParticleUpdateSystem::ParticleUpdateSystem()
{
}


ParticleUpdateSystem::~ParticleUpdateSystem()
{
}

void ParticleUpdateSystem::update(entityx::EntityManager & entities, entityx::EventManager & events, entityx::TimeDelta dt)
{
	entities.each<ParticleEmitterComponent>([&entities, this](entityx::Entity & entity, ParticleEmitterComponent & emitter) {
		if (emitter.active) {
			for (int i = 0; i < emitter.amount; i++) {
				this->emitParticle(entity, entities, emitter);
			}
		}
	});
	entities.each<ParticleComponent>([](entityx::Entity & entity, ParticleComponent & particle) {
		if (--particle.remainingUpdates <= 0) {
			entity.destroy();
		}
		else {
			DynamicMeshComponent* mesh = entity.component<DynamicMeshComponent>().get();
			float a = (float)particle.remainingUpdates / (float)particle.maxUpdates + Utilities::random(-0.5f, 0.5f);
			mesh->vertices[0].m_abgr = Utilities::abgr(1.0f, 1.0f, 1.0f, a);
			mesh->verticesValid = false;
		}
	});
}
