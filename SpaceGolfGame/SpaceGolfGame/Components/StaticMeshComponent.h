#pragma once
#include "BaseMeshComponent.h"
struct StaticMeshComponent : public BaseMeshComponent {
	bgfx::IndexBufferHandle indicesHandle;
	bgfx::VertexBufferHandle verticesHandle;
	StaticMeshComponent() {
		indicesHandle = BGFX_INVALID_HANDLE;
		verticesHandle = BGFX_INVALID_HANDLE;
	}
};