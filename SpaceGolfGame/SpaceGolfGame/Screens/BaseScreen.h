#pragma once

class Application;
class BaseGameState;
#include <vmath.h>
#include <bgfx_utils.h>
#include <common.h>
#include <entityx/entityx.h>

class BaseScreen : public entityx::EntityX
{
private:

	Vector2i oldMousePos;
	entry::MouseState oldState;

protected:
	Application* app;
	BaseGameState *gameState;
    entityx::Entity camera;

	void removeGameStateIfExists();

	virtual void onLeftMouseButtonDown(const entry::MouseState & state) {};
	virtual void onLeftMouseButtonUp(const entry::MouseState & state) {};
	virtual void onMouseMove(Vector2f delta, Vector2f now) {}

public:
	BaseScreen(Application* app);
	virtual ~BaseScreen();

	virtual void update(float timeDelta) = 0;
    virtual void init() {}
	void processMouse(const entry::MouseState &state);
	void setGameState(BaseGameState* newGameState);
    Vector2f getCameraPosition();
};

