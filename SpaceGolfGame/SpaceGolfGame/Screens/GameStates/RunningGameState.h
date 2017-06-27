#pragma once
#include "PlayingBaseGameState.h"

class RunningGameState : public PlayingBaseGameState
{
	// Inherited via BaseGameState
	virtual void activate() override;
	virtual void deactivate() override;
	Vector2f initialVelocity;
public:
	RunningGameState(GameScreen *screen, Vector2f initialVelocity);
};