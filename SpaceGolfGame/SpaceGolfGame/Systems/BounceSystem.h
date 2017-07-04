#pragma once

#include <entityx/System.h>
#include <entityx/Event.h>
#include <vmath.h>

#include "../Events/PlanetCollisionEvent.h"

class BounceSystem
	: public entityx::System<BounceSystem>,
	public entityx::Receiver<BounceSystem>
{
protected:
	Aabb3f *extents;
public:
	BounceSystem(Aabb3f *extents);
	~BounceSystem();

	// Inherited via System
	virtual void update(entityx::EntityManager & entities, entityx::EventManager & events, entityx::TimeDelta dt) override;

	void configure(entityx::EventManager &manager) override;
	void receive(const PlanetCollisionEvent &collision);
};

