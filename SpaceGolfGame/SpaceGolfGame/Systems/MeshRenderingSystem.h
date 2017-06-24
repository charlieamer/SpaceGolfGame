#pragma once
#include <entityx/System.h>
#include <bgfx/bgfx.h>

class MeshRenderingSystem : public entityx::System<MeshRenderingSystem>
{
public:
	MeshRenderingSystem();
	~MeshRenderingSystem();
	bgfx::ProgramHandle program;

	void configure(entityx::EventManager &event_manager);

	// Inherited via System
	virtual void update(entityx::EntityManager & entities, entityx::EventManager & events, entityx::TimeDelta dt) override;
};

