#pragma once
#include "PlayingBaseGameState.h"
#include "../../Events/MouseEvents.h"
class GameScreen;

class IdleGameState : public PlayingBaseGameState,
	public entityx::Receiver<IdleGameState>
{
	// Inherited via BaseGameState
	virtual void activate() override;
	virtual void deactivate() override;
public:
	IdleGameState(GameScreen *screen);
	void receive(const LeftMouseDownEvent&);
};
