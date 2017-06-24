#pragma once
#include <entityx/System.h>

class GravitySystem
	: public entityx::System<GravitySystem>
{
	float constant;
public:
	GravitySystem(float constant);
	~GravitySystem();

	// Inherited via System
	virtual void update(entityx::EntityManager & entities, entityx::EventManager & events, entityx::TimeDelta dt) override;
};

