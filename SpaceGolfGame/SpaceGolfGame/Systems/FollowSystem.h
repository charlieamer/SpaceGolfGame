#pragma once

#include <entityx/System.h>

class FollowSystem : public entityx::System<FollowSystem>
{
public:
	virtual void update(entityx::EntityManager & entities, entityx::EventManager & events, entityx::TimeDelta dt) override;
};

