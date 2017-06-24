/*
* Copyright 2011-2017 Branimir Karadzic. All rights reserved.
* License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
*/

#include <bx/uint32_t.h>
#include <algorithm>
#include "common.h"
#include "bgfx_utils.h"
#include "Screens/BaseScreen.h"
#include "Screens/GameScreen.h"

#include "Rendering/RenderingData.h"

#include "main.h"

// Static stuff initialization, this solves some linker problems
bgfx::VertexDecl Pos2fColorVertex::ms_decl;

void Application::init(int _argc, char** _argv) {
	Args args(_argc, _argv);

	m_width = 1280;
	m_height = 720;
	m_debug = BGFX_DEBUG_TEXT;
	m_reset = BGFX_RESET_VSYNC;

	bgfx::init(args.m_type, args.m_pciId);
	bgfx::reset(m_width, m_height, m_reset);

	// Enable debug text.
	bgfx::setDebug(m_debug);

	// Set view 0 clear state.
	bgfx::setViewClear(0
		, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH
		, 0x000000
		, 1.0f
		, 0
	);

	Pos2fColorVertex::init();

	this->currentScreen = new GameScreen(this);
}

ENTRY_IMPLEMENT_MAIN(Application);

int Application::shutdown()
{
	// Shutdown bgfx.
	bgfx::shutdown();

	return 0;
}

bool Application::update() {
	if (!entry::processEvents(m_width, m_height, m_debug, m_reset))
	{
		bgfx::setViewRect(0, 0, 0, uint16_t(m_width), uint16_t(m_height));
		bgfx::touch(0);
		bgfx::dbgTextClear();

		float ratio = (float)m_width / (float)m_height;
		float width = std::max(ratio, 1.0f);
		float height = std::max(1.0f/ratio, 1.0f);
		float ortho[16];
		bx::mtxOrtho(ortho, width, -width, height, -height, 0, 100, 0, false);
		this->screenExtents.min = Vector3f(-width, -height, 0);
		this->screenExtents.max = Vector3f(width, height, 0); // miki miralem mehmedovic 
		
		float at[3] = { this->currentScreen->camera.x, this->currentScreen->camera.y, 0.0f };
		float eye[3] = { this->currentScreen->camera.x, this->currentScreen->camera.y, 1.0f };
		float transform[16];
		bx::mtxLookAt(transform, eye, at);
		bgfx::setViewTransform(0, transform, ortho);

		this->currentScreen->update(0.1);

		bgfx::frame();

		return true;
	}

	return false;
}
