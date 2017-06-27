#pragma once

#include "../BaseScreen.h"

enum GameStateId {
	RUNNING,
	IDLE,
	AIMING
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