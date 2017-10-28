#include "guiLoaders.h"
#include "GameCompletition.h"

CEGUI::Window* loadSingleLevelWidget(GameLevel level) {
    CEGUI::Window* window = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("levelselect.layout");
    window->setName("Level-" + level.level);
    window->setMargin(CEGUI::UBox(CEGUI::UDim(0, 0), CEGUI::UDim(0.02, 0), CEGUI::UDim(0, 0), CEGUI::UDim(0.02, 0)));
    window->setSize(CEGUI::USize(CEGUI::UDim(0.25, 0), CEGUI::UDim(0, 150)));
    window->setUserString("Level", level.level);
    
    // Set level number
    std::stringstream ss;
    ss << level.levelNumber;
    window->setText(ss.str());
    
    // Enable/disable appropriate stars for the level based on completition
    LevelCompletition completition = getCompletitionForLevel(level);
    switch (completition.stars) {
        case 0:
        window->getChildRecursive("LevelStar1")->disable();
        case 1:
        window->getChildRecursive("LevelStar2")->disable();
        case 2:
        window->getChildRecursive("LevelStar3")->disable();
        case 3:
        break;
        default:
        throw new std::runtime_error("Unknown number of stars for level");
    }
    
    return window;
}