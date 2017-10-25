#pragma once
#include "BaseScreen.h"
#include <entityx/entityx.h>
#include "../main.h"
#include <rapidxml.hpp>

class GameScreen :
	public BaseScreen
{
    std::string levelPath;
public:
	GameScreen(Application* app, std::string levelPath);
	~GameScreen();
	
	virtual void onLeftMouseButtonDown(const entry::MouseState & state) override;
	virtual void onLeftMouseButtonUp(const entry::MouseState & state) override;
	virtual void onMouseMove(Vector2f delta, Vector2f now) override;
    
	// Inherited via BaseScreen
	virtual void update(float timeDelta) override;
    virtual void init() override;

	entityx::Entity ball;
};

