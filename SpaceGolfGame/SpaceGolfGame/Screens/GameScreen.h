#pragma once
#include "BaseScreen.h"
#include <entityx/entityx.h>
#include "../main.h"
#include <rapidxml.hpp>

class GameScreen :
	public BaseScreen, public entityx::EntityX
{
public:
	GameScreen(Application* app, rapidxml::xml_document<>& document);
	~GameScreen();

	// Inherited via BaseScreen
	virtual void update(float timeDelta) override;
	
	virtual void onLeftMouseButtonDown(const entry::MouseState & state) override;
	virtual void onLeftMouseButtonUp(const entry::MouseState & state) override;
	virtual void onMouseMove(Vector2f delta, Vector2f now) override;

	entityx::Entity ball;
};

