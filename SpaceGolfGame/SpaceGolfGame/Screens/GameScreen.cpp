#include "GameScreen.h"

#include "../Systems/MeshRenderingSystem.h"
#include "../Systems/AABBCacheSystem.h"
#include "../Systems/VelocitySystem.h"
#include "../Systems/BounceSystem.h"
#include "../Systems/GravitySystem.h"
#include "../Entities/CircleEntity.h"
#include "../Rendering/MeshGenerators.h"
#include "../Components/MeshTransformCacheComponent.h"
#include "../Components/VelocityComponent.h"
#include "../Components/AABBCacheComponent.h"
#include "../Components/GravityComponent.h"

GameScreen::GameScreen(Application* app) : BaseScreen(app)
{
	this->systems.add<MeshRenderingSystem>();
	this->systems.add<AABBCacheSystem>();
	this->systems.add<GravitySystem>(2);
	this->systems.add<VelocitySystem>();
	this->systems.add<BounceSystem>(&app->screenExtents);
	this->systems.configure();
	entityx::Entity circle = CreateCircleEntity(this->entities, Vector2f(0, 0), 0.1);
	circle.assign_from_copy(generateCircleMesh(30));
	circle.assign<MeshTransformCacheComponent>();
	circle.assign<VelocityComponent>(Vector2f(1, 1));
	circle.assign<AABBCacheComponent>();
	circle.assign<GravityComponent>();
}


GameScreen::~GameScreen()
{
}

void GameScreen::update(float timeDelta)
{
	this->systems.update_all(timeDelta);
}
