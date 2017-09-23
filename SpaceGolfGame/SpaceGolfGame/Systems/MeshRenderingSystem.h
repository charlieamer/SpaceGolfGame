#pragma once
#include <entityx/System.h>
#include <entityx/Event.h>
#include <bgfx/bgfx.h>
#include <vmath.h>
#include <map>
#include <vector>
#include <string>
#include "../Rendering/RenderingData.h"
#include "../Components/MeshComponent.h"
#include "../utilities.h"

class MeshRenderingSystem : public entityx::System<MeshRenderingSystem>
{
	static Matrix4f calculateTransform(entityx::Entity entity);
public:
	MeshRenderingSystem();
	~MeshRenderingSystem();

	static Vector3f getScale(entityx::Entity entity);

	void configure(entityx::EventManager &event_manager);

	void setTransform(entityx::Entity & entity, int & nonStatic, int & notCached);

	// Inherited via System
	virtual void update(entityx::EntityManager & entities, entityx::EventManager & events, entityx::TimeDelta dt) override;
};

