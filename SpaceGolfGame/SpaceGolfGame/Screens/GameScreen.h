#pragma once
#include "BaseScreen.h"
#include <entityx/entityx.h>
#include "../main.h"

class GameScreen :
	public BaseScreen, entityx::EntityX
{
public:
	GameScreen(Application* app);
	~GameScreen();

	// Inherited via BaseScreen
	virtual void update(float timeDelta) override;
};

