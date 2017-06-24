#pragma once

class Application;
#include <vmath.h>

class BaseScreen
{
	Application* app;

public:
	BaseScreen(Application* app);
	~BaseScreen();

	virtual void update(float timeDelta) = 0;
	Vector2f camera;
};

