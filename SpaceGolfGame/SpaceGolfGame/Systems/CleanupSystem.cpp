#include "CleanupSystem.h"

void CleanupSystem::configure(entityx::EventManager& manager)
{
    manager.subscribe<entityx::ComponentRemovedEvent<MeshComponent>>(*this);
}

void CleanupSystem::receive(const entityx::ComponentRemovedEvent<MeshComponent>& removed)
{
    MeshComponent *component = (MeshComponent*)removed.component.get();
    component->backend->destroy();
    component->backend.reset();
}

void CleanupSystem::update(entityx::EntityManager& entities, entityx::EventManager& events, entityx::TimeDelta dt)
{
}
