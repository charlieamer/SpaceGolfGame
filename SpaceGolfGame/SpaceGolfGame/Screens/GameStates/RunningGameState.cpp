#include "RunningGameState.h"
#include "../../Components/VelocityComponent.h"
#include "../../Components/PositionComponent.h"
#include "../../Components/ParticleEmitterComponent.h"
#include "../../Components/PlanetCollisionComponent.h"
#include "IdleGameState.h"
#include "../../utilities.h"

RunningGameState::RunningGameState(GameScreen* screen, Vector2f initialVelocity) : PlayingBaseGameState(screen, GameStateId::RUNNING), initialVelocity(initialVelocity) {}

void RunningGameState::activate()
{
	assert(!this->gameScreen->ball.component<VelocityComponent>());
	this->gameScreen->ball.assign<VelocityComponent>(this->initialVelocity);
	this->gameScreen->events.subscribe<PlanetCollisionEvent>(*this);
	this->gameScreen->ball.component<PlanetCollisionComponent>()->generateEvent = true;
	this->gameScreen->ball.component<ParticleEmitterComponent>()->active = true;
}

void RunningGameState::deactivate()
{
	assert(this->gameScreen->ball.component<VelocityComponent>());
	this->gameScreen->ball.component<VelocityComponent>().remove();
	this->gameScreen->events.unsubscribe<PlanetCollisionEvent>(*this);
	this->gameScreen->ball.component<PlanetCollisionComponent>()->generateEvent = false;
	this->gameScreen->ball.component<ParticleEmitterComponent>()->active = false;
}

void RunningGameState::receive(const PlanetCollisionEvent & collision)
{
	if (collision.collider == this->gameScreen->ball) {
		float speedSq = this->gameScreen->ball.component<VelocityComponent>()->v.lengthSq();
		Debug::p(Debug::PrintSeverity::PRINT_INFO, "Terminal velocity squared: %f\n", speedSq);
		if (speedSq < 0.00006f || isnan(speedSq)) {
			this->gameScreen->ball.component<PositionComponent>()->pos = collision.entry;
			this->gameScreen->setGameState(new IdleGameState(this->gameScreen));
		}
	}
}