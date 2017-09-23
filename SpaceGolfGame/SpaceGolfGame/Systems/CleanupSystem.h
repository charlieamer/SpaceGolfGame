#pragma once

#include <entityx/System.h>
#include <entityx/Event.h>
#include "../Components/MeshComponent.h"

class CleanupSystem : public entityx::System<CleanupSystem>, public entityx::Receiver<CleanupSystem>
{
public:
	void configure(entityx::EventManager &manager) override;
	void receive(const entityx::ComponentRemovedEvent<MeshComponent> &removed);
	virtual void update(entityx::EntityManager & entities, entityx::EventManager & events, entityx::TimeDelta dt) override;
};

