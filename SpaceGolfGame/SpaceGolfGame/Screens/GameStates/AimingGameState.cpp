#include "AimingGameState.h"
#include "RunningGameState.h"

#include "../../Components/PositionComponent.h"
#include "../../Components/MeshTransformCacheComponent.h"
#include "../../Components/VelocityComponent.h"
#include "../../Components/MassComponent.h"
#include "../../Components/GravityComponent.h"

Vector2f AimingGameState::calculateDirection(Vector2i mouse)
{
	Vector2f diff(mouse - this->startingMousePos);
	diff.x *= -1.0f;
	diff /= 5000.0f;
	return diff;
}

AimingGameState::AimingGameState(GameScreen* screen, Vector2i mousePos) : PlayingBaseGameState(screen, GameStateId::AIMING), startingMousePos(mousePos), ballPos(screen->ball.component<PositionComponent>().get()->pos)
{
}


AimingGameState::~AimingGameState()
{
}

void AimingGameState::activate()
{
	this->aimingEntity = this->gameScreen->entities.create();

	this->mesh = this->aimingEntity.assign<DynamicMeshComponent>();
	for (int i = 0; i < 50; i++) {
		this->mesh->vertices.push_back(Pos2fColorVertex(ballPos));
		this->mesh->indices.push_back(i);
	}
	this->mesh->renderState = 0 | BGFX_STATE_DEFAULT | BGFX_STATE_PT_LINESTRIP;

	this->aimingEntity.assign<MeshTransformCacheComponent>();
	this->aimingEntity.assign<VelocityComponent>(0, 0);
	this->aimingEntity.assign_from_copy<MassComponent>(*this->gameScreen->ball.component<MassComponent>());
	this->aimingEntity.assign_from_copy<GravityComponent>(*this->gameScreen->ball.component<GravityComponent>());
	
	this->gameScreen->events.subscribe<MouseMoveEvent>(*this);
	this->gameScreen->events.subscribe<LeftMouseUpEvent>(*this);
}

void AimingGameState::deactivate()
{
	this->gameScreen->events.unsubscribe<MouseMoveEvent>(*this);
	this->gameScreen->events.unsubscribe<LeftMouseUpEvent>(*this);
	this->aimingEntity.destroy();
}

void AimingGameState::receive(const MouseMoveEvent & move)
{
	Vector2f diff = this->calculateDirection(move.now);
	this->aimingEntity.component<VelocityComponent>()->v = diff;
}

void AimingGameState::receive(const LeftMouseUpEvent & move)
{
	Vector2f velocity = this->calculateDirection(move.position);
	this->gameScreen->setGameState(new RunningGameState(this->gameScreen, velocity));
}
