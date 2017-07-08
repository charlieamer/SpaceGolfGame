#pragma once
#include "BaseMeshComponent.h"
#include <bgfx/bgfx.h>

struct DynamicMeshComponent : public BaseMeshComponent<Pos2fColorVertex> {
	bgfx::DynamicIndexBufferHandle indicesHandle;
	bgfx::DynamicVertexBufferHandle verticesHandle;
	bool indicesValid;
	bool verticesValid;
	DynamicMeshComponent() {
		indicesHandle.idx = BGFX_INVALID_HANDLE;
		verticesHandle.idx = BGFX_INVALID_HANDLE;
		indicesValid = false;
		verticesValid = false;
	}
	~DynamicMeshComponent() {
		if (indicesHandle.idx != bgfx::kInvalidHandle) {
			bgfx::destroyDynamicIndexBuffer(indicesHandle);
		}
		if (verticesHandle.idx != bgfx::kInvalidHandle) {
			bgfx::destroyDynamicVertexBuffer(verticesHandle);
		}
	}
};