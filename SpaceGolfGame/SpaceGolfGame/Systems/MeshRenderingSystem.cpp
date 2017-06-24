#include "MeshRenderingSystem.h"
#include "../Components/MeshComponent.h"
#include "../Rendering/RenderingData.h"
#include <bgfx/bgfx.h>
#include <bgfx_utils.h>

MeshRenderingSystem::MeshRenderingSystem()
{
}


MeshRenderingSystem::~MeshRenderingSystem()
{
}

void MeshRenderingSystem::configure(entityx::EventManager & event_manager)
{
	this->program = loadProgram("vs_cubes", "fs_cubes");
}

void MeshRenderingSystem::update(entityx::EntityManager & entities, entityx::EventManager & events, entityx::TimeDelta dt)
{
	int drawn = 0;
	entities.each<MeshComponent>([this, &drawn](entityx::Entity& entity, MeshComponent& mesh) {
		drawn++;
		if (mesh.indicesHandle.idx == bgfx::kInvalidHandle) {
			mesh.indicesHandle = bgfx::createIndexBuffer(bgfx::makeRef(mesh.indices.data(), sizeof(uint16_t) * mesh.indices.size()));
			printf("MeshRenderingSystem - Created indices buffer with size of %d - %u\n", mesh.indices.size(), mesh.indicesHandle.idx);
		}
		if (mesh.verticesHandle.idx == bgfx::kInvalidHandle) {
			mesh.verticesHandle = bgfx::createVertexBuffer(bgfx::makeRef(mesh.vertices.data(), sizeof(Pos2fColorVertex) * mesh.vertices.size()), Pos2fColorVertex::ms_decl);
			printf("MeshRenderingSystem - Created vertex buffer with size of %d - %u\n", mesh.vertices.size(), mesh.verticesHandle.idx);
		}
		bgfx::setVertexBuffer(0, mesh.verticesHandle);
		bgfx::setIndexBuffer(mesh.indicesHandle);
		bgfx::setState(mesh.renderState);

		bgfx::submit(0, this->program);
	});
	bgfx::dbgTextPrintf(0, 3, 0xf, "Entities: %d", entities.size());
	bgfx::dbgTextPrintf(0, 4, 0xf, "Drawn entities: %d", drawn);
}
