#pragma once
#include "PlayingBaseGameState.h"
#include <entityx/Event.h>
#include "../../Events/PlanetCollisionEvent.h"

class RunningGameState : public PlayingBaseGameState,
	public entityx::Receiver<RunningGameState>
{
	// Inherited via BaseGameState
	virtual void activate() override;
	virtual void deactivate() override;
	Vector2f initialVelocity;
public:
	RunningGameState(GameScreen *screen, Vector2f initialVelocity);
	void receive(const PlanetCollisionEvent& collision);
};