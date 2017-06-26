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
#include "../Components/MassComponent.h"
#include "../Components/PlanetComponent.h"
#include "../Events/MouseEvents.h"

#include "GameStates.h"

#include <math.h>

GameScreen::GameScreen(Application* app) : BaseScreen(app)
{
	this->systems.add<MeshRenderingSystem>();
	this->systems.add<AABBCacheSystem>();
	this->systems.add<GravitySystem>(0.000001);
	this->systems.add<VelocitySystem>();
	this->systems.add<BounceSystem>(&app->screenExtents);
	this->systems.configure();

	this->ball = CreateCircleEntity(this->entities, Vector2f(0.5, 0), 0.01);
	ball.assign_from_copy(generateCircleMesh(10));
	ball.assign<MeshTransformCacheComponent>();
	ball.assign<AABBCacheComponent>();
	ball.assign<GravityComponent>();
	ball.assign<MassComponent>(10);

	entityx::Entity planet = CreateCircleEntity(this->entities, Vector2f(0, 0), 0.1);
	planet.assign_from_copy(generateCircleMesh(25));
	planet.assign<MeshTransformCacheComponent>();
	planet.assign<PlanetComponent>();
	planet.assign<MassComponent>(100);

	this->setGameState(new IdleGameState(this));
}


GameScreen::~GameScreen()
{
}

void GameScreen::update(float timeDelta)
{
	this->systems.update_all(timeDelta);
}

void GameScreen::onLeftMouseButtonDown()
{
	this->events.emit<LeftMouseDownEvent>();
}

void GameScreen::onLeftMouseButtonUp()
{
	this->events.emit<LeftMouseUpEvent>();
}

void GameScreen::onMouseMove(Vector2f delta, Vector2f now)
{
	this->events.emit<MouseMoveEvent>(delta, now);
}
