#pragma once

#include "BaseScreen.h"
#include "../Events/MouseEvents.h"
#include <entityx/Event.h>
class GameScreen;

enum GameStateId {
	RUNNING,
	IDLE
};

class BaseGameState
{
protected:
	BaseScreen *screen;
public:
	BaseGameState(BaseScreen *screen, GameStateId stateType);
	virtual ~BaseGameState();
	virtual void activate() = 0;
	virtual void deactivate() = 0;

	GameStateId stateType;
};

class PlayingBaseGameState : public BaseGameState
{
protected:
	GameScreen *gameScreen;
public:
	PlayingBaseGameState(GameScreen *screen, GameStateId id);
};

class RunningGameState : public PlayingBaseGameState
{
	// Inherited via BaseGameState
	virtual void activate() override;
	virtual void deactivate() override;
public:
	RunningGameState(GameScreen *screen);
};

class IdleGameState : public PlayingBaseGameState,
	public entityx::Receiver<LeftMouseDownEvent>
{
	// Inherited via BaseGameState
	virtual void activate() override;
	virtual void deactivate() override;
public:
	IdleGameState(GameScreen *screen);
	void receive(const LeftMouseDownEvent&);
};
