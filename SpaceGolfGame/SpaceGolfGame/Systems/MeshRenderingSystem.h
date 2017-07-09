#pragma once
#include <entityx/System.h>
#include <entityx/Event.h>
#include <bgfx/bgfx.h>
#include <vmath.h>
#include <map>
#include <vector>
#include <string>
#include "../Rendering/RenderingData.h"
#include "../Rendering/Shader.h"
#include "../Rendering/RenderTexture.h"
#include "../Components/DynamicMeshComponent.h"
#include "../Components/StaticMeshComponent.h"

struct VectorComparison {
	template<typename T>
	bool compare (const std::vector<T> &a, const std::vector<T> &b) const {
		if (a.size() < b.size()) return false;
		if (a.size() > b.size()) return true;
		for (size_t i = 0; i < a.size(); i++) {
			if (a[i] < b[i]) return false;
			if (a[i] > b[i]) return true;
		}
		return false;
	}

	bool operator() (const std::vector<uint16_t> &a, const std::vector<uint16_t> &b) const {
		return compare(a, b);
	}

	bool operator() (const std::vector<Pos2fColorVertex> &a, const std::vector<Pos2fColorVertex> &b) const {
		return compare(a, b);
	}

	bool operator() (const std::vector<Pos2fColorTextureVertex> &a, const std::vector<Pos2fColorTextureVertex> &b) const {
		return compare(a, b);
	}
};

class MeshRenderingSystem : public entityx::System<MeshRenderingSystem>
{
	static Matrix4f calculateTransform(entityx::Entity entity);
	std::map<std::vector<Pos2fColorVertex>, bgfx::VertexBufferHandle, VectorComparison> vertexBufferCache;
	std::map<std::vector<Pos2fColorTextureVertex>, bgfx::VertexBufferHandle, VectorComparison> vertexTexturedBufferCache;
	std::map<std::vector<uint16_t>, bgfx::IndexBufferHandle, VectorComparison> indexBufferCache;
	std::map<std::string, RenderTexture> textureCache;
	Shader colorShader, texturedShader;
public:
	MeshRenderingSystem();
	~MeshRenderingSystem();

	static Vector3f getScale(entityx::Entity entity);

	void configure(entityx::EventManager &event_manager);

	void setTransform(entityx::Entity & entity, int & nonStatic, int & notCached);

	template <typename T>
	void prepareStaticBuffers(StaticMeshBaseComponent<T> & mesh, std::map<std::vector<T>, bgfx::VertexBufferHandle, VectorComparison>& cache) {
		if (mesh.indicesHandle.idx == bgfx::kInvalidHandle) {
			if (this->indexBufferCache.find(mesh.indices) == this->indexBufferCache.end()) {
				this->indexBufferCache[mesh.indices] = bgfx::createIndexBuffer(bgfx::makeRef(mesh.indices.data(), sizeof(uint16_t) * mesh.indices.size()));
				printf("MeshRenderingSystem - Created indices buffer with size of %d\n", mesh.indices.size());
			}
			mesh.indicesHandle = this->indexBufferCache[mesh.indices];
		}
		if (mesh.verticesHandle.idx == bgfx::kInvalidHandle) {
			if (cache.find(mesh.vertices) == cache.end()) {
				cache[mesh.vertices] = bgfx::createVertexBuffer(bgfx::makeRef(mesh.vertices.data(), sizeof(mesh.vertices[0]) * mesh.vertices.size()), mesh.vertices[0].vertexDeclaration());
				printf("MeshRenderingSystem - Created vertex buffer with size of %d\n", mesh.vertices.size());
			}
			mesh.verticesHandle = cache[mesh.vertices];
		}
		bgfx::setVertexBuffer(0, mesh.verticesHandle);
		bgfx::setIndexBuffer(mesh.indicesHandle);
		bgfx::setState(mesh.renderState);
	}
	template <typename T>
	void prepareDynamicBuffers(T & mesh) {
		if (mesh.indicesHandle.idx == bgfx::kInvalidHandle) {
			mesh.indicesHandle = bgfx::createDynamicIndexBuffer(mesh.indices.size());
		}
		if (mesh.verticesHandle.idx == bgfx::kInvalidHandle) {
			mesh.verticesHandle = bgfx::createDynamicVertexBuffer(mesh.vertices.size(), mesh.vertices[0].vertexDeclaration());
		}
		if (!mesh.indicesValid && mesh.indicesHandle.idx != bgfx::kInvalidHandle) {
			mesh.indicesValid = true;
			bgfx::updateDynamicIndexBuffer(mesh.indicesHandle, 0, bgfx::makeRef(mesh.indices.data(), mesh.indices.size() * sizeof(uint16_t)));
		}
		if (!mesh.verticesValid && mesh.verticesHandle.idx != bgfx::kInvalidHandle) {
			mesh.verticesValid = true;
			bgfx::updateDynamicVertexBuffer(mesh.verticesHandle, 0, bgfx::makeRef(mesh.vertices.data(), mesh.vertices.size() * sizeof(Pos2fColorVertex)));
		}
		if (mesh.verticesHandle.idx != bgfx::kInvalidHandle && mesh.indicesHandle.idx != bgfx::kInvalidHandle) {
			bgfx::setVertexBuffer(0, mesh.verticesHandle);
			bgfx::setIndexBuffer(mesh.indicesHandle);
			bgfx::setState(mesh.renderState);
		}
	}

	// Inherited via System
	virtual void update(entityx::EntityManager & entities, entityx::EventManager & events, entityx::TimeDelta dt) override;
};

