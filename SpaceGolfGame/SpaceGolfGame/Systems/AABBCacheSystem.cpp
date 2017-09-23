#include "AABBCacheSystem.h"

#include "../Components/AABBCacheComponent.h"
#include "../Components/CircleRadiusComponent.h"
#include "../Rendering/RenderingData.h"
#include "../Systems/MeshRenderingSystem.h"
#include <vmath.h>

#include <iostream>

AABBCacheSystem::AABBCacheSystem()
{
}


AABBCacheSystem::~AABBCacheSystem()
{
}

void AABBCacheSystem::update(entityx::EntityManager & entities, entityx::EventManager & events, entityx::TimeDelta dt)
{
	entities.each<AABBCacheComponent>([](entityx::Entity entity, AABBCacheComponent& aabb) {
		if (!aabb.valid) {
			aabb.valid = true;
			if (entity.component<CircleRadiusComponent>()) {
				// Calculate AABB based on circle
				// Because radius is already taken into account in scale, we don't need to do anything here
				aabb.AABB.min = Vector3f(-1, -1, 0);
				aabb.AABB.max = Vector3f(1, 1, 0);
			}
//			else if (entity.component<DynamicMeshComponent>()) {
//				AABBCacheSystem::calculateAABB(aabb.AABB, entity.component<DynamicMeshComponent>().get());
//			}
//			else if (entity.component<StaticMeshComponent>()) {
//				AABBCacheSystem::calculateAABB(aabb.AABB, entity.component<StaticMeshComponent>().get());
//			}
			aabb.AABB.min *= MeshRenderingSystem::getScale(entity);
			aabb.AABB.max *= MeshRenderingSystem::getScale(entity);
		}
	});
}
/*
void AABBCacheSystem::calculateAABB(Aabb3f & result, BaseMeshComponent<Pos2fColorVertex> * mesh)
{
	// Calculate AABB based on mesh vertices
	result = Aabb3f();
	for (Pos2fColorVertex &vector : mesh->vertices) {
		result.extend(Aabb3f(vector.m_x, vector.m_y, vector.m_z));
	}
}

void AABBCacheSystem::calculateAABB(Aabb3f & result, BaseMeshComponent<Pos2fColorTextureVertex> * mesh)
{
	// Calculate AABB based on mesh vertices
	result = Aabb3f();
	for (Pos2fColorTextureVertex &vector : mesh->vertices) {
		result.extend(Aabb3f(vector.m_x, vector.m_y, vector.m_z));
	}
}
*/