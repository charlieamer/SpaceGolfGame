#include "CustomMeshGenerators.h"
#include "MeshGenerators.h"
#include "RenderingBackend.h"

MeshComponent generatePlanet(Aabb3f bounds, std::string texturePath, uint32_t tint) {
    std::vector<Pos2fColorTextureVertex> vertices;
    std::vector<uint16_t> indices;
    uint64_t renderState = BGFX_STATE_RGB_WRITE | BGFX_STATE_ALPHA_WRITE | BGFX_STATE_PT_TRISTRIP | BGFX_STATE_BLEND_ALPHA;
    
    generateTexturedRectangleVertices(tint, bounds, vertices, indices);
    
	MeshComponent ret((RenderingBackendBase*)new TexturedRenderingBackend<bgfx::IndexBufferHandle, bgfx::VertexBufferHandle>(indices, vertices, texturePath, renderState, "vs_textured", "fs_planet"));
	
	return ret;
}
