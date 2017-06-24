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

#include <math.h>

GameScreen::GameScreen(Application* app) : BaseScreen(app)
{
	this->systems.add<MeshRenderingSystem>();
	this->systems.add<AABBCacheSystem>();
	this->systems.add<GravitySystem>(2);
	this->systems.add<VelocitySystem>();
	this->systems.add<BounceSystem>(&app->screenExtents);
	this->systems.configure();
	for (int i = 0; i < 1000; i++) {
		entityx::Entity circle = CreateCircleEntity(this->entities, Vector2f(0, 0), 0.1);
		circle.assign_from_copy(generateCircleMesh(30));
		circle.assign<MeshTransformCacheComponent>();
		circle.assign<VelocityComponent>(Vector2f(float(rand()) / float(RAND_MAX), float(rand()) / float(RAND_MAX)));
		circle.assign<AABBCacheComponent>();
		circle.assign<GravityComponent>();
	}
}


GameScreen::~GameScreen()
{
}

void GameScreen::update(float timeDelta)
{
	this->systems.update_all(timeDelta);
}
