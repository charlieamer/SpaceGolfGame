#pragma once

#include <entityx/Entity.h>

struct FollowComponent {
    FollowComponent(entityx::Entity entity, float moveSpeed) {
        toFollow = entity;
        speed = moveSpeed;
    }
    entityx::Entity toFollow;
    float speed;
};
