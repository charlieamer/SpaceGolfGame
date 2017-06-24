#include "GameScreen.h"

#include "../Systems/MeshRenderingSystem.h"
#include "../Entities/CircleEntity.h"
#include "../Rendering/MeshGenerators.h"

#include <bgfx/bgfx.h>
#include <bx/fpumath.h>

GameScreen::GameScreen(Application* app) : BaseScreen(app)
{
	this->systems.add<MeshRenderingSystem>();
	this->systems.configure();
	entityx::Entity circle = CreateCircleEntity(this->entities, Vector2f(0, 0), 0.5);
	circle.assign_from_copy(generateCircle());
}


GameScreen::~GameScreen()
{
}

void GameScreen::update(float timeDelta)
{
	this->systems.update_all(timeDelta);
}
