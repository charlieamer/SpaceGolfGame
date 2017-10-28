#include "LevelSelectScreen.h"
#include "GameScreen.h"
#include <CEGUI/CEGUI.h>
#include "../GameLevel.h"
#include "../guiLoaders.h"
#include "../utilities.h"

LevelSelectScreen::LevelSelectScreen(Application* app) : BaseScreen(app)
{
}

LevelSelectScreen::~LevelSelectScreen()
{
}

void LevelSelectScreen::init()
{
    auto root = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("levelselect-menu.layout");
    auto levelsContainer = dynamic_cast<CEGUI::GridLayoutContainer*>(root->getChildElementRecursive("LevelsContainer"));
    auto levels = getAllGameLevels();
    for (auto& level : levels) {
        auto levelWindow = loadSingleLevelWidget(level);
        levelsContainer->addChild(levelWindow);
        levelWindow->subscribeEvent(CEGUI::DefaultWindow::EventMouseClick, CEGUI::Event::Subscriber(&levelClicked, this));
    }
    CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(root);
}

void LevelSelectScreen::update(float timeDelta)
{
}

void LevelSelectScreen::levelClicked(const CEGUI::EventArgs &e) {
    const CEGUI::MouseEventArgs m = dynamic_cast<const CEGUI::MouseEventArgs&>(e);
    if (m.window->isUserStringDefined("Level")) {
        const char* lvl = m.window->getUserString("Level").c_str();
        app->loadNewScreen(new GameScreen(app, lvl));
    }
}

