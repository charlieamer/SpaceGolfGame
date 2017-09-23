#include "AimingGameState.h"
#include "RunningGameState.h"

#include "../../Components/PositionComponent.h"
#include "../../Components/MeshTransformCacheComponent.h"
#include "../../Components/VelocityComponent.h"
#include "../../Components/MassComponent.h"
#include "../../Components/GravityComponent.h"
#include "../../Components/AimLineComponent.h"

Vector2f AimingGameState::calculateDirection(Vector2i mouse)
{
	Vector2f diff(mouse - this->startingMousePos);
	diff.x *= -1.0f;
	diff.y *= -1.0f;
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

    std::vector<Pos2fColorVertex> vertices;
    std::vector<uint16_t> indices;
    uint64_t renderState = 0 | BGFX_STATE_DEFAULT | BGFX_STATE_PT_LINESTRIP;
	for (int i = 0; i < 50; i++) {
		vertices.push_back(Pos2fColorVertex(ballPos));
		indices.push_back(i);
	}
    auto backend = new SolidRenderingBackend<bgfx::IndexBufferHandle, bgfx::DynamicVertexBufferHandle>(indices, vertices, renderState);
	this->mesh = this->aimingEntity.assign<MeshComponent>((RenderingBackendBase*)backend);

	this->aimingEntity.assign<MeshTransformCacheComponent>();
	this->aimingEntity.assign<VelocityComponent>(0, 0);
    this->aimingEntity.assign<AimLineComponent>();
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
