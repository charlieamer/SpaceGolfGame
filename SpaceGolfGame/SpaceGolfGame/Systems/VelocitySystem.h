#pragma once

#include <entityx/System.h>

class VelocitySystem
	: public entityx::System<VelocitySystem>
{
public:
	VelocitySystem();
	~VelocitySystem();

	// Inherited via System
	virtual void update(entityx::EntityManager & entities, entityx::EventManager & events, entityx::TimeDelta dt) override;
};

