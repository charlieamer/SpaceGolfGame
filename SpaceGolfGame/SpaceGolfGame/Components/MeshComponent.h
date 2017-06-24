#pragma once

#include "../Rendering/RenderingData.h"
#include <vector>

struct MeshComponent {
	std::vector<Pos2fColorVertex> vertices;
	std::vector<uint16_t> indices;
	bgfx::IndexBufferHandle indicesHandle;
	bgfx::VertexBufferHandle verticesHandle;
	uint64_t renderState;
	MeshComponent() {
		indicesHandle = BGFX_INVALID_HANDLE;
		verticesHandle = BGFX_INVALID_HANDLE;
	}
};