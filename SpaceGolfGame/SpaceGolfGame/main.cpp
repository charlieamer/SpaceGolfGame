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
#include <chrono>

#include <rapidxml.hpp>

#include "Rendering/RenderingData.h"

#include "utilities.h"
#include "main.h"
#include <iostream>

namespace bx {
    void debugOutput(const char* _out) {
        Debug::p(Debug::PrintSeverity::PRINT_SILLY, "%s", _out);
    }
}

void Application::init(int32_t _argc, const char* const* _argv, uint32_t _width, uint32_t _height) {
	Args args(_argc, _argv);

	m_width = _width;
	m_height = _height;
    m_width = 400;
    m_height = 800;
    
	m_debug = BGFX_DEBUG_TEXT;
	m_reset = BGFX_RESET_VSYNC;

	bgfx::init(bgfx::RendererType::OpenGL, args.m_pciId);
	bgfx::reset(m_width, m_height, m_reset);

	// Enable debug text.
	bgfx::setDebug(m_debug);

	// Set view 0 clear state.
	bgfx::setViewClear(0
		, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH
		, 0x000000ff
		, 1.0f
		, 0
	);

	rapidxml::xml_document<> document;
	std::string content = FileUtilities::readFile(_argv[1]);
	char xml[100000];
	strncpy(xml, content.c_str(), 99999);
	document.parse<0>(xml);

	this->currentScreen = new GameScreen(this, document);

	ceguiRenderer = new GuiBgfxRenderer("vs_textured", "fs_textured");
	CEGUI::System::create(*ceguiRenderer);

    didSetInitialResolution = false;
    entry::setWindowSize({0}, 1000, 1000);
};

ENTRY_IMPLEMENT_MAIN(Application, "Space golf game", "A golf in space");

int Application::shutdown()
{
    delete this->currentScreen;
	ceguiRenderer->destroy();
	bgfx::shutdown();

	return 0;
}

bool Application::update() {
    unsigned old_width = m_width, old_height = m_height;
    if (!didSetInitialResolution) {
        didSetInitialResolution = true;
        entry::setWindowSize({0}, m_width, m_height);
        Debug::p(Debug::PrintSeverity::PRINT_INFO, "Starting in %dx%d resolution", m_width, m_height);
    }
    
    Vector2f cameraPos;
	if (!entry::processEvents(m_width, m_height, m_debug, m_reset, &m_mouseState))
	{
        if (m_width != old_width || m_height != old_height) {
            CEGUI::System::getSingleton().notifyDisplaySizeChanged(CEGUI::Sizef(m_width, m_height));
        }
		auto start = std::chrono::steady_clock::now();
		bgfx::setViewRect(0, 0, 0, uint16_t(m_width), uint16_t(m_height));
		bgfx::touch(0);
		bgfx::dbgTextClear();

//		auto stats = bgfx::getStats();
		// bgfx::dbgTextPrintf(0, 0, 0xf, "FPS: %.0f", m_fps);
		// bgfx::dbgTextPrintf(0, 1, 0xf, "GPU: %.2fms", (float)(stats->gpuTimeEnd - stats->gpuTimeBegin) / 10000000.0f);

		float ratio = (float)m_width / (float)m_height;
		float width = std::max(ratio, 1.0f);
		float height = std::max(1.0f/ratio, 1.0f);
		float ortho[16];
		bx::mtxOrtho(ortho, width, -width, height, -height, 0, 100, 0, false);
		this->screenExtents.min = Vector3f(-width, -height, 0);
		this->screenExtents.max = Vector3f(width, height, 0);
        
        cameraPos = this->currentScreen->getCameraPosition();
		
		float at[3] = { cameraPos.x, cameraPos.y, 0.0f };
		float eye[3] = { cameraPos.x, cameraPos.y, 1.0f };
		float up[3] = { 0.0f, 1.0f, 0.0f };
		float transform[16];
		bx::mtxLookAt(transform, eye, at, up);
		bgfx::setViewTransform(0, transform, ortho);

		this->currentScreen->processMouse(m_mouseState);
		this->currentScreen->update(0.1);
		CEGUI::System::getSingleton().injectTimePulse(0.1);
		CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setPosition(CEGUI::Vector2f(m_mouseState.m_mx, m_mouseState.m_my));
		CEGUI::System::getSingleton().renderAllGUIContexts();

		bgfx::frame();

		auto end = std::chrono::steady_clock::now();
		auto diff = end - start;
		auto ns = std::chrono::nanoseconds(diff).count();
		m_fps = 1000000000.0f / (float)ns;

		return true;
	}

	return false;
}
