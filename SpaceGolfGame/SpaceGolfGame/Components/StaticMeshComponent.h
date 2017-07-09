#pragma once
#include "BaseMeshComponent.h"

template <typename T>
struct StaticMeshBaseComponent : public BaseMeshComponent<T> {
	bgfx::IndexBufferHandle indicesHandle;
	bgfx::VertexBufferHandle verticesHandle;
	StaticMeshBaseComponent() {
		indicesHandle = BGFX_INVALID_HANDLE;
		verticesHandle = BGFX_INVALID_HANDLE;
	}
};

struct StaticMeshComponent : public StaticMeshBaseComponent<Pos2fColorVertex> {
};

struct StaticTexturedMeshComponent : public StaticMeshBaseComponent<Pos2fColorTextureVertex> {
	std::string texturePath;
};