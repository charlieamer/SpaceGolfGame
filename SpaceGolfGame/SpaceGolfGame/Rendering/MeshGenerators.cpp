#include "MeshGenerators.h"

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

StaticTexturedMeshComponent generateTexturedRectangle(Aabb3f bounds, std::string texturePath, uint32_t tint)
{
	StaticTexturedMeshComponent ret;

	ret.vertices.push_back(Pos2fColorTextureVertex(Vector2f(bounds.min.x, bounds.min.y), Vector2f(0, 0), tint));
	ret.vertices.push_back(Pos2fColorTextureVertex(Vector2f(bounds.min.x, bounds.max.y), Vector2f(0, 1), tint));
	ret.vertices.push_back(Pos2fColorTextureVertex(Vector2f(bounds.max.x, bounds.max.y), Vector2f(1, 1), tint));
	ret.vertices.push_back(Pos2fColorTextureVertex(Vector2f(bounds.max.x, bounds.min.y), Vector2f(1, 0), tint));

	ret.indices.push_back(0);
	ret.indices.push_back(1);
	ret.indices.push_back(3);
	ret.indices.push_back(2);

	ret.texturePath = texturePath;

	ret.renderState = BGFX_STATE_RGB_WRITE | BGFX_STATE_ALPHA_WRITE | BGFX_STATE_PT_TRISTRIP | BGFX_STATE_BLEND_ALPHA;
	
	return ret;
}
