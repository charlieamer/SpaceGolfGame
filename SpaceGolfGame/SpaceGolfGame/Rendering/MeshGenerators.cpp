#include "MeshGenerators.h"
#include <bx/fpumath.h>

MeshComponent generateCircle(int vertices)
{
	MeshComponent ret;
	double angle = 0;
	uint32_t color = 0xff00ff00;

	for (int i = 0; i < vertices; i++) {
		ret.vertices.push_back({
			(float)cos(angle), // X
			(float)sin(angle), // Y
			0,				   // Z
			color       // ABGR
		});
		angle += bx::kPi2 / (float)vertices;
	}
	ret.vertices.push_back({ 0, 0, 0, color });

	for (int i = 0; i < vertices; i++) {
		ret.indices.push_back(i);
		ret.indices.push_back((i + 1) % vertices);
		ret.indices.push_back(vertices);
	}

	ret.renderState = 0
		| BGFX_STATE_DEFAULT
		| BGFX_STATE_PT_TRISTRIP;

	return ret;
}
