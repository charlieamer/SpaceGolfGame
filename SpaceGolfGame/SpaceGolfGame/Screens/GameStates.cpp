#include "GameStates.h"
#include "GameScreen.h"
#include "../Components/VelocityComponent.h"
#include "../Events/MouseEvents.h"

BaseGameState::BaseGameState(BaseScreen* screen, GameStateId stateType) : screen(screen), stateType(stateType)
{
}


BaseGameState::~BaseGameState()
{
}

PlayingBaseGameState::PlayingBaseGameState(GameScreen * screen, GameStateId id) : BaseGameState::BaseGameState(screen, id), gameScreen(screen)
{
}

RunningGameState::RunningGameState(GameScreen* screen) : PlayingBaseGameState(screen, GameStateId::RUNNING) {}

void RunningGameState::activate()
{
	assert(!this->gameScreen->ball.component<VelocityComponent>());
	this->gameScreen->ball.assign<VelocityComponent>(Vector2f(0, 0.1));
}

void RunningGameState::deactivate()
{
	assert(this->gameScreen->ball.component<VelocityComponent>());
	this->gameScreen->ball.component<VelocityComponent>().remove();
}

void IdleGameState::activate()
{
	this->gameScreen->events.subscribe<LeftMouseDownEvent>(*this);
}

void IdleGameState::deactivate()
{
	this->gameScreen->events.unsubscribe<LeftMouseDownEvent>(*this);
}

void IdleGameState::receive(const LeftMouseDownEvent &)
{
	printf("Mouse down\n");
	this->gameScreen->setGameState(new RunningGameState(this->gameScreen));
}

IdleGameState::IdleGameState(GameScreen * screen) : PlayingBaseGameState(screen, GameStateId::IDLE)
{
}