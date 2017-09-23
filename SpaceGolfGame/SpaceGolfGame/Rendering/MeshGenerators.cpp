#include "MeshGenerators.h"
#include "RenderingBackend.h"


MeshComponent generatePoint(uint32_t color) {
    return generatePoint(color, BGFX_STATE_DEFAULT | BGFX_STATE_PT_POINTS);
}

MeshComponent generatePoint(uint32_t color, uint64_t renderState)
{
    std::vector<Pos2fColorVertex> vertices;
    std::vector<uint16_t> indices;
	vertices.push_back(Pos2fColorVertex(Vector2f(0, 0), color));
	indices.push_back(0);
	MeshComponent ret((RenderingBackendBase*)new SolidRenderingBackend<bgfx::IndexBufferHandle, bgfx::DynamicVertexBufferHandle>(indices, vertices, renderState));
	return ret;
}

MeshComponent generateTexturedRectangle(Aabb3f bounds, std::string texturePath, uint32_t tint)
{
    std::vector<Pos2fColorTextureVertex> vertices;
    std::vector<uint16_t> indices;
    uint64_t renderState = BGFX_STATE_RGB_WRITE | BGFX_STATE_ALPHA_WRITE | BGFX_STATE_PT_TRISTRIP | BGFX_STATE_BLEND_ALPHA;
    
	vertices.push_back(Pos2fColorTextureVertex(Vector2f(bounds.min.x, bounds.min.y), Vector2f(0, 0), tint));
	vertices.push_back(Pos2fColorTextureVertex(Vector2f(bounds.min.x, bounds.max.y), Vector2f(0, 1), tint));
	vertices.push_back(Pos2fColorTextureVertex(Vector2f(bounds.max.x, bounds.max.y), Vector2f(1, 1), tint));
	vertices.push_back(Pos2fColorTextureVertex(Vector2f(bounds.max.x, bounds.min.y), Vector2f(1, 0), tint));

	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(3);
	indices.push_back(2);
    
	MeshComponent ret((RenderingBackendBase*)new TexturedRenderingBackend<bgfx::IndexBufferHandle, bgfx::VertexBufferHandle>(indices, vertices, texturePath, renderState));
	
	return ret;
}

MeshComponent generateSolidCircleMesh(uint32_t color, int vertices) {
    std::vector<uint16_t> indices;
    std::vector<Pos2fColorVertex> verts;
    generateCircleVertices(color, vertices, verts, indices);
    auto backend = new SolidRenderingBackend<bgfx::IndexBufferHandle, bgfx::VertexBufferHandle>(indices, verts, BGFX_STATE_DEFAULT | BGFX_STATE_PT_TRISTRIP);
    return MeshComponent((RenderingBackendBase*) backend);
}