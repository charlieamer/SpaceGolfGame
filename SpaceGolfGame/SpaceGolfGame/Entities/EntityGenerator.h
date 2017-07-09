#pragma once

#include <entityx/Entity.h>
#include "../LevelParsing/GleedCircle.h"
#include "../LevelParsing/GleedTexture.h"
#include "../LevelParsing/GleedBaseObject.h"

void loadComponents(entityx::Entity entity, GleedCircle & circle);
void loadComponents(entityx::Entity entity, GleedTexture & circle);
void loadComponents(entityx::Entity entity, GleedBaseObject & object);