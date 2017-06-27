#include "AimingGameState.h"
#include "RunningGameState.h"

#include "../../Components/PositionComponent.h"
#include "../../Components/MeshTransformCacheComponent.h"

Vector2f AimingGameState::calculateDirection(Vector2i mouse)
{
	Vector2f diff(mouse - this->startingMousePos);
	diff.x *= -1.0f;
	diff /= 500.0f;
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
	this->mesh->vertices.push_back(Pos2fColorVertex(ballPos));
	this->mesh->vertices.push_back(Pos2fColorVertex(ballPos));
	this->mesh->indices.push_back(0);
	this->mesh->indices.push_back(1);
	this->mesh->renderState = 0 | BGFX_STATE_DEFAULT | BGFX_STATE_PT_LINES;

	this->aimingEntity.assign<MeshTransformCacheComponent>();
	
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
	this->mesh->vertices[1] = Pos2fColorVertex(this->ballPos + diff);
	this->mesh->verticesValid = false;
}

void AimingGameState::receive(const LeftMouseUpEvent & move)
{
	Vector2f velocity = this->calculateDirection(move.position);
	this->gameScreen->setGameState(new RunningGameState(this->gameScreen, velocity));
}
