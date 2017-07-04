#pragma once

#include <entityx/System.h>
#include <vmath.h>
#include "../Components/ParticleEmitterComponent.h"

class ParticleUpdateSystem : public entityx::System<ParticleUpdateSystem>
{
	void emitParticle(entityx::Entity & entity, entityx::EntityManager & entities, const ParticleEmitterComponent &emitter);
public:
	ParticleUpdateSystem();
	~ParticleUpdateSystem();

	// Inherited via System
	virtual void update(entityx::EntityManager & entities, entityx::EventManager & events, entityx::TimeDelta dt) override;
};

