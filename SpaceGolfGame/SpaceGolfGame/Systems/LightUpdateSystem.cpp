#include "LightUpdateSystem.h"

#include "../Components/PositionComponent.h"
#include "../Components/LightComponent.h"
#include "../Components/ZComponent.h"

#include "../Rendering/RenderManager.h"
#include <vmath.h>

LightUpdateSystem::LightUpdateSystem()
{
}

LightUpdateSystem::~LightUpdateSystem()
{
}

void LightUpdateSystem::update(entityx::EntityManager& entities, entityx::EventManager& events, entityx::TimeDelta dt)
{
    bool isSet = false;
    entities.each<PositionComponent, LightComponent>([&isSet](entityx::Entity entity, PositionComponent& position, LightComponent& light) {
        if (!isSet) {
            float z = 0;
            if (entity.has_component<ZComponent>()) {
                z = entity.component<ZComponent>().get()->z;
            }
            RenderManager::get().setUniformVec4f("vec4_light_pos", position.pos.x, position.pos.y, z, 0);
            RenderManager::get().setUniformVec4f("vec4_light_color", light.colorR, light.colorG, light.colorB, 1);
            isSet = true;
        }
    });
}