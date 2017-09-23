#include "GameScreen.h"

#include "../Systems/MeshRenderingSystem.h"
#include "../Systems/AABBCacheSystem.h"
#include "../Systems/VelocitySystem.h"
#include "../Systems/BounceSystem.h"
#include "../Systems/GravitySystem.h"
#include "../Systems/PlanetCollisionSystem.h"
#include "../Systems/ParticleUpdateSystem.h"
#include "../Systems/CleanupSystem.h"
#include "../Entities/EntityGenerator.h"
#include "../Rendering/MeshGenerators.h"
#include "../Components/MeshTransformCacheComponent.h"
#include "../Components/VelocityComponent.h"
#include "../Components/AABBCacheComponent.h"
#include "../Components/GravityComponent.h"
#include "../Components/MassComponent.h"
#include "../Components/PlanetComponent.h"
#include "../Components/PlanetCollisionComponent.h"
#include "../Components/ParticleEmitterComponent.h"
#include "../Events/MouseEvents.h"

#include "GameStates/IdleGameState.h"

#include "../LevelParsing/GleedLevel.h"
#include "../utilities.h"

#include <math.h>

GameScreen::GameScreen(Application* app, rapidxml::xml_document<>& document) : BaseScreen(app)
{

	GleedLevel level(*document.first_node("Level"));

	GleedLayer& objectiveLayer = GleedUtilities::getObjectByName(level.layers, "Objectives");
	GleedLayer& planetsLayer = GleedUtilities::getObjectByName(level.layers, "Planets");
	GleedLayer& texturesLayer = GleedUtilities::getObjectByName(level.layers, "Textures");

	GleedRectangle& extentsRect = GleedUtilities::getRectangle(objectiveLayer, "Bounds");
	GleedCircle& ballCircle = GleedUtilities::getCircle(objectiveLayer, "Ball");

	float gravity = std::stof(level.properties["Gravity"]);
	Aabb3f extents = GleedUtilities::rectangleToAABB(extentsRect);

	this->systems.add<MeshRenderingSystem>();
	this->systems.add<AABBCacheSystem>();
	this->systems.add<GravitySystem>(gravity);
	this->systems.add<VelocitySystem>();
	this->systems.add<BounceSystem>(extents);
	this->systems.add<PlanetCollisionSystem>();
    this->systems.add<ParticleUpdateSystem>();
    this->systems.add<CleanupSystem>();
    
	this->systems.configure();

	this->ball = entities.create();
	loadComponents(this->ball, ballCircle);

	for (auto& planet : planetsLayer.objects) {
		GleedCircle& circle = *static_cast<GleedCircle*>(&*planet);
		entityx::Entity planetEntity = entities.create();
		loadComponents(planetEntity, circle);
		planetEntity.assign<PlanetComponent>();
	}

	for (auto& textureObj : texturesLayer.objects) {
		GleedTexture& texture = *static_cast<GleedTexture*>(&*textureObj);
		entityx::Entity textureEntity = entities.create();
		loadComponents(textureEntity, texture);
	}

	/*
	this->ball = CreateCircleEntity(this->entities, Vector2f(0.5f, 0), 0.01f);
	ball.assign_from_copy(generateCircleMesh(0xffaa0000, 10));
	ball.assign<MeshTransformCacheComponent>();
	ball.assign<AABBCacheComponent>();
	ball.assign<GravityComponent>();
	ball.assign<MassComponent>(1);
	ball.assign<PlanetCollisionComponent>(true, true, 0.8f);
	ball.assign<ParticleEmitterComponent>(ParticleEmitterComponent{ 2, 0.3f, 0.003f, 100, 1.0f, false });

	entityx::Entity planet = CreateCircleEntity(this->entities, Vector2f(0, 0), 0.1f);
	planet.assign_from_copy(generateCircleMesh(0xff00aa44, 25));
	planet.assign<MeshTransformCacheComponent>();
	planet.assign<PlanetComponent>();
	planet.assign<MassComponent>(100);

	entityx::Entity planet2 = CreateCircleEntity(this->entities, Vector2f(-0.8f, 0), 0.07f);
	planet2.assign_from_copy(generateCircleMesh(0xff0044aa, 25));
	planet2.assign<MeshTransformCacheComponent>();
	planet2.assign<PlanetComponent>();
	planet2.assign<MassComponent>(150);

	*/
	this->setGameState(new IdleGameState(this));
}


GameScreen::~GameScreen()
{
}

void GameScreen::update(float timeDelta)
{
	this->systems.update_all(timeDelta);
}

void GameScreen::onLeftMouseButtonDown(const entry::MouseState & state)
{
	this->events.emit<LeftMouseDownEvent>(Vector2i(state.m_mx, state.m_my));
}

void GameScreen::onLeftMouseButtonUp(const entry::MouseState & state)
{
	this->events.emit<LeftMouseUpEvent>(Vector2i(state.m_mx, state.m_my));
}

void GameScreen::onMouseMove(Vector2f delta, Vector2f now)
{
	this->events.emit<MouseMoveEvent>(delta, now);
}
