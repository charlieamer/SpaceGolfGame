#pragma once
#include <entityx/System.h>
#include <bgfx/bgfx.h>
#include <vmath.h>

class MeshRenderingSystem : public entityx::System<MeshRenderingSystem>
{
	static Matrix4f calculateTransform(entityx::Entity entity);

public:
	MeshRenderingSystem();
	~MeshRenderingSystem();
	bgfx::ProgramHandle program;

	static Vector3f getScale(entityx::Entity entity);

	void configure(entityx::EventManager &event_manager);

	// Inherited via System
	virtual void update(entityx::EntityManager & entities, entityx::EventManager & events, entityx::TimeDelta dt) override;
};

