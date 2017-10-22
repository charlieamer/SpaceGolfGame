#pragma once

#include <entityx/System.h>

class LightUpdateSystem : public entityx::System<LightUpdateSystem>
{
public:
    LightUpdateSystem();
    ~LightUpdateSystem();
	virtual void update(entityx::EntityManager & entities, entityx::EventManager & events, entityx::TimeDelta dt) override;
};

