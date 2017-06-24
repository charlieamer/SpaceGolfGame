#pragma once

#include <bgfx_utils.h>
#include <common.h>
#include "Screens/BaseScreen.h"

class Application : public entry::AppI
{
	BaseScreen* currentScreen;

	void init(int _argc, char** _argv) BX_OVERRIDE;

	virtual int shutdown();

	bool update() BX_OVERRIDE;

public:

	uint32_t m_width;
	uint32_t m_height;
	uint32_t m_debug;
	uint32_t m_reset;
};