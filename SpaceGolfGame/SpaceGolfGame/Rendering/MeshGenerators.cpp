#include "MeshGenerators.h"
#include <bx/fpumath.h>

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
