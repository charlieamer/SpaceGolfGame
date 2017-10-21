#pragma once

#include "../Components/MeshComponent.h"
#include "../LevelParsing/GleedTexture.h"

MeshComponent generatePlanet(Aabb3f bounds, std::string texturePath, uint32_t tint);