#pragma once
#include "BaseScreen.h"
#include "GameStates.h"
#include <entityx/entityx.h>
#include "../main.h"

class GameScreen :
	public BaseScreen, public entityx::EntityX
{
public:
	GameScreen(Application* app);
	~GameScreen();

	// Inherited via BaseScreen
	virtual void update(float timeDelta) override;
	
	virtual void onLeftMouseButtonDown() override;
	virtual void onLeftMouseButtonUp() override;
	virtual void onMouseMove(Vector2f delta, Vector2f now) override;

	entityx::Entity ball;
};

