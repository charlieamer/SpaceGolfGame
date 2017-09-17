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
        std::cout << termcolor::yellow << _out << termcolor::reset;
    }
}

void Application::init(int32_t _argc, const char* const* _argv, uint32_t _width, uint32_t _height) {
	Args args(_argc, _argv);

	m_width = 1280;
	m_height = 720;
	m_debug = BGFX_DEBUG_TEXT;
	m_reset = BGFX_RESET_VSYNC;

	bgfx::init(bgfx::RendererType::OpenGL, args.m_pciId);
	bgfx::reset(m_width, m_height, m_reset);

	// Enable debug text.
	bgfx::setDebug(m_debug);

	// Set view 0 clear state.
	bgfx::setViewClear(0
		, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH
		, 0x222222ff
		, 1.0f
		, 0
	);

	rapidxml::xml_document<> document;
	std::string content = FileUtilities::readFile(_argv[1]);
	char* xml = new char[content.length() + 2];
	strcpy(xml, content.c_str());
	document.parse<0>(xml);

	this->currentScreen = new GameScreen(this, document);
	delete[] xml;

	ceguiRenderer = new GuiBgfxRenderer("vs_textured", "fs_textured");
	CEGUI::System::create(*ceguiRenderer);

	CEGUI::SchemeManager::getSingleton().createFromFile("TaharezLook.scheme");

	CEGUI::Window *gJumpBtnWindow = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("gui/test/test.layout");
	CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(gJumpBtnWindow);
};

ENTRY_IMPLEMENT_MAIN(Application, "Space golf game", "A golf in space");

int Application::shutdown()
{
	// Shutdown bgfx.
	ceguiRenderer->destroy();

	bgfx::shutdown();

	return 0;
}

bool Application::update() {
	if (!entry::processEvents(m_width, m_height, m_debug, m_reset, &m_mouseState))
	{
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
		
		float at[3] = { this->currentScreen->camera.x, this->currentScreen->camera.y, 0.0f };
		float eye[3] = { this->currentScreen->camera.x, this->currentScreen->camera.y, 1.0f };
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
