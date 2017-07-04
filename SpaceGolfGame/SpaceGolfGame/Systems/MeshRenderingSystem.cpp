#include "MeshRenderingSystem.h"
#include "../Components/PositionComponent.h"
#include "../Components/CircleRadiusComponent.h"
#include "../Components/MeshTransformCacheComponent.h"
#include "../Rendering/RenderingData.h"
#include <bgfx/bgfx.h>
#include <bgfx_utils.h>
#include <entityx/Event.h>

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

void MeshRenderingSystem::setTransform(entityx::Entity & entity, int & nonStatic, int & notCached)
{

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
}

void MeshRenderingSystem::prepareBuffers(StaticMeshComponent & mesh)
{
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
}

void MeshRenderingSystem::prepareBuffers(DynamicMeshComponent & mesh)
{
	if (mesh.indicesHandle.idx == bgfx::kInvalidHandle) {
		mesh.indicesHandle = bgfx::createDynamicIndexBuffer(mesh.indices.size());
		// printf("MeshRenderingSystem - Created dynamic index buffer with size of %d\n", mesh.indices.size());
	}
	if (mesh.verticesHandle.idx == bgfx::kInvalidHandle) {
		mesh.verticesHandle = bgfx::createDynamicVertexBuffer(mesh.vertices.size(), Pos2fColorVertex::ms_decl);
		// printf("MeshRenderingSystem - Created dynamic index buffer with size of %d\n", mesh.indices.size());
	}
	if (!mesh.indicesValid && mesh.indicesHandle.idx != bgfx::kInvalidHandle) {
		mesh.indicesValid = true;
		bgfx::updateDynamicIndexBuffer(mesh.indicesHandle, 0, bgfx::makeRef(mesh.indices.data(), mesh.indices.size() * sizeof(uint16_t)));
		// printf("MeshRenderingSystem - Updating index buffer\n");
	}
	if (!mesh.verticesValid && mesh.verticesHandle.idx != bgfx::kInvalidHandle) {
		mesh.verticesValid = true;
		bgfx::updateDynamicVertexBuffer(mesh.verticesHandle, 0, bgfx::makeRef(mesh.vertices.data(), mesh.vertices.size() * sizeof(Pos2fColorVertex)));
		// printf("MeshRenderingSystem - Updating vertex buffer\n");
	}
	if (mesh.verticesHandle.idx != bgfx::kInvalidHandle && mesh.indicesHandle.idx != bgfx::kInvalidHandle) {
		bgfx::setVertexBuffer(0, mesh.verticesHandle);
		bgfx::setIndexBuffer(mesh.indicesHandle);
		bgfx::setState(mesh.renderState);
	}
}

void MeshRenderingSystem::update(entityx::EntityManager & entities, entityx::EventManager & events, entityx::TimeDelta dt)
{
	int drawn = 0;
	int nonStatic = 0;
	int notCached = 0;
	entities.each<StaticMeshComponent>([this, &drawn, &nonStatic, &notCached](entityx::Entity& entity, StaticMeshComponent& mesh) {
		drawn++;
		this->prepareBuffers(mesh);
		this->setTransform(entity, nonStatic, notCached);
		bgfx::submit(0, this->program);
	});
	entities.each<DynamicMeshComponent>([this, &drawn, &nonStatic, &notCached](entityx::Entity& entity, DynamicMeshComponent& mesh) {
		drawn++;
		this->prepareBuffers(mesh);
		this->setTransform(entity, nonStatic, notCached);
		bgfx::submit(0, this->program);
	});
	bgfx::dbgTextPrintf(0, 3, 0xf, "Entities: %d", entities.size());
	bgfx::dbgTextPrintf(0, 4, 0xf, "Drawn entities: %d", drawn);
	bgfx::dbgTextPrintf(0, 5, 0xf, "Moving entities: %d", nonStatic);
	bgfx::dbgTextPrintf(0, 6, 0xf, "Not cached entities: %d", notCached);
}