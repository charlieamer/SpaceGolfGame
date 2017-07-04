#pragma once
#include "PlayingBaseGameState.h"
#include <entityx/Entity.h>
#include "../../Components/DynamicMeshComponent.h"
#include "../../Events/MouseEvents.h"
#include <vmath.h>

class AimingGameState :
	public PlayingBaseGameState,
	public entityx::Receiver<AimingGameState>
{
	entityx::Entity aimingEntity;
	entityx::ComponentHandle<DynamicMeshComponent> mesh;

	Vector2i startingMousePos;
	Vector2f &ballPos;

	Vector2f calculateDirection(Vector2i mouse);


public:
	AimingGameState(GameScreen* screen, Vector2i mousePos);
	~AimingGameState();

	// Inherited via PlayingBaseGameState
	virtual void activate() override;
	virtual void deactivate() override;

	void receive(const MouseMoveEvent& move);
	void receive(const LeftMouseUpEvent& move);
};

