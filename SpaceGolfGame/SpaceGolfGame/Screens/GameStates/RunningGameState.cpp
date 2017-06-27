#include "RunningGameState.h"
#include "../../Components/VelocityComponent.h"

RunningGameState::RunningGameState(GameScreen* screen, Vector2f initialVelocity) : PlayingBaseGameState(screen, GameStateId::RUNNING), initialVelocity(initialVelocity) {}

void RunningGameState::activate()
{
	assert(!this->gameScreen->ball.component<VelocityComponent>());
	this->gameScreen->ball.assign<VelocityComponent>(this->initialVelocity);
}

void RunningGameState::deactivate()
{
	assert(this->gameScreen->ball.component<VelocityComponent>());
	this->gameScreen->ball.component<VelocityComponent>().remove();
}