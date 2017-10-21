#include "FollowSystem.h"

#include "../Components/PositionComponent.h"
#include "../Components/FollowComponent.h"

void FollowSystem::update(entityx::EntityManager & entities, entityx::EventManager & events, entityx::TimeDelta dt) {
    entities.each<PositionComponent, FollowComponent>([](const entityx::Entity &entity, PositionComponent &position, FollowComponent &follow) {
        position.pos += (follow.toFollow.component<PositionComponent>()->pos - position.pos) * follow.speed;
    });
}