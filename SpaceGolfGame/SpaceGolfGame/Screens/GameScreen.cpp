#include "GameScreen.h"

#include "../Systems/MeshRenderingSystem.h"
#include "../Systems/AABBCacheSystem.h"
#include "../Systems/VelocitySystem.h"
#include "../Systems/BounceSystem.h"
#include "../Systems/GravitySystem.h"
#include "../Systems/PlanetCollisionSystem.h"
#include "../Systems/ParticleUpdateSystem.h"
#include "../Systems/CleanupSystem.h"
#include "../Systems/FollowSystem.h"
#include "../Systems/LightUpdateSystem.h"
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
#include "../Components/FollowComponent.h"
#include "../Events/MouseEvents.h"

#include "GameStates/IdleGameState.h"

#include "../LevelParsing/GleedLevel.h"
#include "../utilities.h"

#include <math.h>

GameScreen::GameScreen(Application* app, std::string levelPath) : BaseScreen(app), levelPath(levelPath) {}

void GameScreen::init() {
	rapidxml::xml_document<> document;
	std::string content = FileUtilities::readFile(levelPath);
	char xml[100000];
	strncpy(xml, content.c_str(), 99999);
	document.parse<0>(xml);
    
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
	this->systems.add<GravitySystem>(gravity, extents);
	this->systems.add<VelocitySystem>();
	this->systems.add<BounceSystem>(extents);
	this->systems.add<PlanetCollisionSystem>();
    this->systems.add<ParticleUpdateSystem>();
    this->systems.add<CleanupSystem>();
    this->systems.add<FollowSystem>();
    this->systems.add<LightUpdateSystem>();
    
	this->systems.configure();

	this->ball = entities.create();
	loadComponents(this->ball, ballCircle);
    
    camera.assign<FollowComponent>(this->ball, 0.03);

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
