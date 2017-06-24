#pragma once

#include <entityx\Entity.h>
#include <vmath.h>
#include "../Components/PositionComponent.h"
#include "../Components/CircleRadiusComponent.h"

entityx::Entity CreateCircleEntity(entityx::EntityManager& manager, Vector2f position, float radius);