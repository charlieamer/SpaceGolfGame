#include "MeshRenderingSystem.h"
#include "../Components/MeshComponent.h"
#include "../Components/PositionComponent.h"
#include "../Components/CircleRadiusComponent.h"
#include "../Components/MeshTransformCacheComponent.h"
#include "../Rendering/RenderingData.h"
#include <bgfx/bgfx.h>
#include <bgfx_utils.h>

MeshRenderingSystem::MeshRenderingSystem()
{
}


MeshRenderingSystem::~MeshRenderingSystem()
{
}

Vector3f MeshRenderingSystem::getScale(entityx::Entity entity)
{
	Vector3f scale(1, 1, 1);
	if (entity.component<CircleRadiusComponent>()) {
		CircleRadiusComponent* circleRadiusComponent = entity.component<CircleRadiusComponent>().get();
		scale.x = circleRadiusComponent->r;
		scale.y = circleRadiusComponent->r;
	}
	return scale;
}

Matrix4f MeshRenderingSystem::calculateTransform(entityx::Entity entity)
{
	Vector2f position = (entity.component<PositionComponent>()) ? entity.component<PositionComponent>().get()->pos : Vector2f();
	Matrix4f transform = Matrix4f::createTranslation(position.x, position.y, 0);
	Vector3f scale = MeshRenderingSystem::getScale(entity);
	transform.setScale(scale);
	return transform;
}

void MeshRenderingSystem::configure(entityx::EventManager & event_manager)
{
	this->program = loadProgram("vs_cubes", "fs_cubes");
}

void MeshRenderingSystem::update(entityx::EntityManager & entities, entityx::EventManager & events, entityx::TimeDelta dt)
{
	int drawn = 0;
	int nonStatic = 0;
	int notCached = 0;
	entities.each<MeshComponent>([this, &drawn, &nonStatic, &notCached](entityx::Entity& entity, MeshComponent& mesh) {
		drawn++;

		if (entity.component<MeshTransformCacheComponent>()) {
			MeshTransformCacheComponent* cacheComponent = entity.component<MeshTransformCacheComponent>().get();
			if (!cacheComponent->valid) {
				cacheComponent->transform = MeshRenderingSystem::calculateTransform(entity);
				cacheComponent->valid = true;
				nonStatic++;
			}
			bgfx::setTransform(cacheComponent->transform.data);
		}
		else {
			bgfx::setTransform(MeshRenderingSystem::calculateTransform(entity).data);
			notCached++;
		}

		if (mesh.indicesHandle.idx == bgfx::kInvalidHandle) {
			if (this->indexBufferCache.find(mesh.indices) == this->indexBufferCache.end()) {
				this->indexBufferCache[mesh.indices] = bgfx::createIndexBuffer(bgfx::makeRef(mesh.indices.data(), sizeof(uint16_t) * mesh.indices.size()));
				printf("MeshRenderingSystem - Created indices buffer with size of %d\n", mesh.indices.size());
			}
			mesh.indicesHandle = this->indexBufferCache[mesh.indices];
		}
		if (mesh.verticesHandle.idx == bgfx::kInvalidHandle) {
			if (this->vertexBufferCache.find(mesh.vertices) == this->vertexBufferCache.end()) {
				this->vertexBufferCache[mesh.vertices] = bgfx::createVertexBuffer(bgfx::makeRef(mesh.vertices.data(), sizeof(Pos2fColorVertex) * mesh.vertices.size()), Pos2fColorVertex::ms_decl);
				printf("MeshRenderingSystem - Created vertex buffer with size of %d\n", mesh.vertices.size());
			}
			mesh.verticesHandle = this->vertexBufferCache[mesh.vertices];
		}
		bgfx::setVertexBuffer(0, mesh.verticesHandle);
		bgfx::setIndexBuffer(mesh.indicesHandle);
		bgfx::setState(mesh.renderState);

		bgfx::submit(0, this->program);
	});
	bgfx::dbgTextPrintf(0, 3, 0xf, "Entities: %d", entities.size());
	bgfx::dbgTextPrintf(0, 4, 0xf, "Drawn entities: %d", drawn);
	bgfx::dbgTextPrintf(0, 5, 0xf, "Non static entities: %d", nonStatic);
	bgfx::dbgTextPrintf(0, 6, 0xf, "Not cached entities: %d", notCached);
}
