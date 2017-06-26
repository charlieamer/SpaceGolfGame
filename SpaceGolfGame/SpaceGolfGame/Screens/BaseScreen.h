#pragma once

class Application;
class BaseGameState;
#include <vmath.h>
#include <bgfx_utils.h>
#include <common.h>

class BaseScreen
{
private:

	Vector2i oldMousePos;
	entry::MouseState oldState;

protected:
	Application* app;
	BaseGameState *gameState;

	void removeGameStateIfExists();

	virtual void onLeftMouseButtonDown() {};
	virtual void onLeftMouseButtonUp() {};
	virtual void onMouseMove(Vector2f delta, Vector2f now) {}

public:
	BaseScreen(Application* app);
	virtual ~BaseScreen();

	virtual void update(float timeDelta) = 0;
	void processMouse(const entry::MouseState &state);
	void setGameState(BaseGameState* newGameState);
	Vector2f camera;
};

