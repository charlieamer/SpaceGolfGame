#pragma once

#include <entityx/System.h>

class AABBCacheSystem
	: public entityx::System<AABBCacheSystem>
{
public:
	AABBCacheSystem();
	~AABBCacheSystem();

	// Inherited via System
	virtual void update(entityx::EntityManager & entities, entityx::EventManager & events, entityx::TimeDelta dt) override;
};

