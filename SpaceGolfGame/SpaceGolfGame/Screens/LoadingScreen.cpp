#include "LoadingScreen.h"
#include <CEGUI/CEGUI.h>
#include "../Gui/GuiBgfxRenderer.h"
#include "../utilities.h"
#include "../Systems/MeshRenderingSystem.h"
#include "../Systems/CleanupSystem.h"
#include "../Rendering/MeshGenerators.h"
#include "LevelSelectScreen.h"
#include <entityx/entityx.h>
#include "../main.h"

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
        loadCeguiResources();
        CEGUI::SchemeManager::getSingleton().createFromFile("spacegolf.scheme");
        CEGUI::Window *text = CEGUI::WindowManager::getSingleton().createWindow("Spacegolf/Label", "Text");
        text->setFont("StarJedi-Small");
        text->setText("Please wait ...");
        text->setVerticalAlignment(CEGUI::VerticalAlignment::VA_CENTRE);
        text->setHorizontalAlignment(CEGUI::HorizontalAlignment::HA_CENTRE);
        CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(text);
    } else if (frameCount == 3) {
        Debug::p(Debug::PrintSeverity::PRINT_INFO, "Loading new screen");
        this->app->loadNewScreen(new LevelSelectScreen(app));
    }
}

void LoadingScreen::loadCeguiResources() {
    // initialise the required dirs for the DefaultResourceProvider
    CEGUI::DefaultResourceProvider* rp =
        static_cast<CEGUI::DefaultResourceProvider*>
            (CEGUI::System::getSingleton().getResourceProvider());
    CEGUI::String dataPathPrefix("gui");

    /* for each resource type, set a resource group directory. We cast strings
       to "const CEGUI::utf8*" in order to support general Unicode strings,
       rather than only ASCII strings (even though currently they're all ASCII).
       */
    rp->setResourceGroupDirectory("schemes",
      dataPathPrefix +reinterpret_cast<const CEGUI::utf8*>("/schemes/"));
    rp->setResourceGroupDirectory("imagesets",
      dataPathPrefix +reinterpret_cast<const CEGUI::utf8*>("/imagesets/"));
    rp->setResourceGroupDirectory("fonts",
      dataPathPrefix +reinterpret_cast<const CEGUI::utf8*>("/fonts/"));
    rp->setResourceGroupDirectory("layouts",
      dataPathPrefix +reinterpret_cast<const CEGUI::utf8*>("/layouts/"));
    rp->setResourceGroupDirectory("looknfeels",
      dataPathPrefix +reinterpret_cast<const CEGUI::utf8*>("/looknfeel/"));
    rp->setResourceGroupDirectory("lua_scripts",
      dataPathPrefix +reinterpret_cast<const CEGUI::utf8*>("/lua_scripts/"));
    rp->setResourceGroupDirectory("schemas",
      dataPathPrefix +reinterpret_cast<const CEGUI::utf8*>("/xml_schemas/"));   
    rp->setResourceGroupDirectory("animations",
      dataPathPrefix +reinterpret_cast<const CEGUI::utf8*>("/animations/"));
    
    // set the default resource groups to be used
    CEGUI::ImageManager::setImagesetDefaultResourceGroup("imagesets");
    CEGUI::Font::setDefaultResourceGroup("fonts");
    CEGUI::Scheme::setDefaultResourceGroup("schemes");
    CEGUI::WidgetLookManager::setDefaultResourceGroup("looknfeels");
    CEGUI::WindowManager::setDefaultResourceGroup("layouts");
    CEGUI::ScriptModule::setDefaultResourceGroup("lua_scripts");
    CEGUI::AnimationManager::setDefaultResourceGroup("animations");

    // setup default group for validation schemas
    CEGUI::XMLParser* parser = CEGUI::System::getSingleton().getXMLParser();
    if (parser->isPropertyPresent("SchemaDefaultResourceGroup"))
        parser->setProperty("SchemaDefaultResourceGroup", "schemas");
}