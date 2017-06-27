#pragma once
#include "../GameScreen.h"
#include "BaseGameState.h"

class PlayingBaseGameState : public BaseGameState
{
protected:
	GameScreen *gameScreen;
public:
	PlayingBaseGameState(GameScreen *screen, GameStateId id);
};