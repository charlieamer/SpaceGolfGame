#pragma once

#include <bgfx_utils.h>
#include <common.h>
#include "Screens/BaseScreen.h"
#include "termcolor.hpp"
#include <iostream>
#include <bgfx/bgfx.h>

class Application : public entry::AppI
{
	BaseScreen* currentScreen;
    BaseScreen* nextScreen;

	void init(int32_t _argc, const char* const* _argv, uint32_t _width, uint32_t _height);

	virtual int shutdown();

	bool update();
    
    // should screen be initialised next frame
    bool shouldInitScreen;

public:

	uint32_t m_width;
	uint32_t m_height;
	uint32_t m_debug;
	uint32_t m_reset;
	float m_fps;
	Aabb3f screenExtents;
    bool didSetInitialResolution;

	entry::MouseState m_mouseState;
    
	Application(const char* _name, const char* _description)
		: entry::AppI(_name, _description)
	{
	}
    void loadNewScreen(BaseScreen* newScreen);
};