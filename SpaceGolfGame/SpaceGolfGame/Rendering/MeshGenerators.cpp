#include "MeshGenerators.h"
#include <bx/fpumath.h>

StaticMeshComponent generateCircleMesh(uint32_t color, int vertices)
{
	StaticMeshComponent ret;
	double angle = 0;

	for (int i = 0; i < vertices / 2; i++) {
		ret.vertices.push_back(Pos2fColorVertex({ (float)cos(angle), (float)sin(angle) }, color));
		ret.vertices.push_back(Pos2fColorVertex({ (float)cos(angle),-(float)sin(angle) }, color));
		angle += bx::kPi2 / (float)vertices;
	}
	ret.vertices.push_back(Pos2fColorVertex({ -1.0f, 0.0f }, color));

	for (int i = ret.vertices.size() - 1; i >= 0; i--) {
		ret.indices.push_back(i);
	}

	ret.renderState = 0
		| BGFX_STATE_DEFAULT
		| BGFX_STATE_PT_TRISTRIP;

	return ret;
}

DynamicMeshComponent generatePoint(uint32_t color)
{
	DynamicMeshComponent ret;
	ret.vertices.push_back(Pos2fColorVertex({ 0,0 }, color));
	ret.indices.push_back(0);
	ret.renderState = 0
		| BGFX_STATE_DEFAULT
		| BGFX_STATE_PT_POINTS;
	return ret;
}
