#pragma once
#include "BaseScreen.h"
#include "CEGUI/EventArgs.h"

class LevelSelectScreen : public BaseScreen
{
public:
    virtual void init();
    virtual void update(float timeDelta);
    LevelSelectScreen(Application *app);
    ~LevelSelectScreen();
    void levelClicked(const CEGUI::EventArgs &e);
};
