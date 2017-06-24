#pragma once

#include <entityx/System.h>
#include <vmath.h>

class BounceSystem
	: public entityx::System<BounceSystem>
{
protected:
	Aabb3f *extents;
public:
	BounceSystem(Aabb3f *extents);
	~BounceSystem();

	// Inherited via System
	virtual void update(entityx::EntityManager & entities, entityx::EventManager & events, entityx::TimeDelta dt) override;
};

