#pragma once

#include <entityx/System.h>
#include <vmath.h>
#include "../Components/BaseMeshComponent.h"

class AABBCacheSystem
	: public entityx::System<AABBCacheSystem>
{
	static void calculateAABB(Aabb3f &result, BaseMeshComponent<Pos2fColorVertex> *mesh);
	static void calculateAABB(Aabb3f &result, BaseMeshComponent<Pos2fColorTextureVertex> *mesh);
public:
	AABBCacheSystem();
	~AABBCacheSystem();

	// Inherited via System
	virtual void update(entityx::EntityManager & entities, entityx::EventManager & events, entityx::TimeDelta dt) override;
};

