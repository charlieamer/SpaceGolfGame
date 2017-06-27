#include "IdleGameState.h"
#include "AimingGameState.h"

void IdleGameState::activate()
{
	this->gameScreen->events.subscribe<LeftMouseDownEvent>(*this);
}

void IdleGameState::deactivate()
{
	this->gameScreen->events.unsubscribe<LeftMouseDownEvent>(*this);
}

void IdleGameState::receive(const LeftMouseDownEvent &mouse)
{
	this->gameScreen->setGameState(new AimingGameState(this->gameScreen, mouse.position));
}

IdleGameState::IdleGameState(GameScreen * screen) : PlayingBaseGameState(screen, GameStateId::IDLE)
{
}