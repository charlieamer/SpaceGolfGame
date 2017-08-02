#pragma once
#include "../Components/StaticMeshComponent.h"
#include "../Components/DynamicMeshComponent.h"
#include "../Rendering/RenderingData.h"
#include <bx/fpumath.h>

template<typename T, typename R>
R generateCircleMesh(uint32_t color, int vertices = 10)
{
	R ret;
	double angle = 0;

	for (int i = 0; i < vertices / 2; i++) {
		ret.vertices.push_back(T({ (float)cos(angle), (float)sin(angle) }, color));
		ret.vertices.push_back(T({ (float)cos(angle),-(float)sin(angle) }, color));
		angle += bx::kPi2 / (float)vertices;
	}
	ret.vertices.push_back(T({ -1.0f, 0.0f }, color));

	for (unsigned i = 0; i < ret.vertices.size(); i++) {
		ret.indices.push_back(i);
	}

	ret.renderState = 0
		| BGFX_STATE_DEFAULT
		| BGFX_STATE_PT_TRISTRIP;

	return ret;
}

DynamicMeshComponent generatePoint(uint32_t color);
StaticTexturedMeshComponent generateTexturedRectangle(Aabb3f bounds, std::string texturePath, uint32_t tint);