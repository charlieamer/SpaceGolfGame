#pragma once
#include <entityx/System.h>
#include <bgfx/bgfx.h>
#include <vmath.h>
#include <map>
#include <vector>
#include <string>
#include "../Rendering/RenderingData.h"

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
};

class MeshRenderingSystem : public entityx::System<MeshRenderingSystem>
{
	static Matrix4f calculateTransform(entityx::Entity entity);
	std::map<std::vector<Pos2fColorVertex>, bgfx::VertexBufferHandle, VectorComparison> vertexBufferCache;
	std::map<std::vector<uint16_t>, bgfx::IndexBufferHandle, VectorComparison> indexBufferCache;
public:
	MeshRenderingSystem();
	~MeshRenderingSystem();
	bgfx::ProgramHandle program;

	static Vector3f getScale(entityx::Entity entity);

	void configure(entityx::EventManager &event_manager);

	// Inherited via System
	virtual void update(entityx::EntityManager & entities, entityx::EventManager & events, entityx::TimeDelta dt) override;
};

