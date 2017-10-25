#include "LoadingScreen.h"
#include <CEGUI/CEGUI.h>
#include "../Gui/GuiBgfxRenderer.h"
#include "../utilities.h"
#include "../Systems/MeshRenderingSystem.h"
#include "../Systems/CleanupSystem.h"
#include "../Rendering/MeshGenerators.h"
#include "GameScreen.h"
#include <entityx/entityx.h>

LoadingScreen::LoadingScreen(Application* app) : BaseScreen(app)
{
    frameCount = 0;
    systems.add<MeshRenderingSystem>();
    systems.add<CleanupSystem>();
    systems.configure();
}

LoadingScreen::~LoadingScreen()
{
}

void LoadingScreen::update(float timeDelta)
{
    frameCount++;
    systems.update_all(1);
    if (frameCount == 1) {
        entityx::Entity background = entities.create();
        background.assign_from_copy<MeshComponent>(generateTexturedRectangleMesh(Aabb3f(0, 0, 0, 1, 1, 1), "Assets/Backgrounds/Loading.png", Utilities::abgr((unsigned char)255, 255, 255, 255)));
    } else if (frameCount == 2) {
        Debug::p(Debug::PrintSeverity::PRINT_INFO, "Initializing CEGUI");
        GuiBgfxRenderer::create("vs_textured", "fs_textured");
        CEGUI::System::create(GuiBgfxRenderer::getSingleton());
        CEGUI::SchemeManager::getSingleton().createFromFile("TaharezLook.scheme");
        CEGUI::Window *text = CEGUI::WindowManager::getSingleton().createWindow("TaharezLook/Label", "Text");
        text->setText("Please wait ...");
        text->setPosition(CEGUI::UVector2(CEGUI::UDim(0.5, 0), CEGUI::UDim(0.5, 0)));
        CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(text);
    } else if (frameCount == 3) {
        Debug::p(Debug::PrintSeverity::PRINT_INFO, "Loading new screen");
        this->app->loadNewScreen(new GameScreen(this->app, "levels/test-2.gleed"));
    }
}

