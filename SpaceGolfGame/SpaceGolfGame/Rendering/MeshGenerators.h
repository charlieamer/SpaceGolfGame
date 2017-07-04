#pragma once
#include "../Components/StaticMeshComponent.h"
#include "../Components/DynamicMeshComponent.h"
#include "../Rendering/RenderingData.h"

StaticMeshComponent generateCircleMesh(uint32_t color, int vertices = 10);
DynamicMeshComponent generatePoint(uint32_t color);