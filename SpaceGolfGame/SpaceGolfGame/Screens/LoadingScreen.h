#pragma once
#include "BaseScreen.h"

class LoadingScreen : public BaseScreen
{
    int frameCount;
    void loadCeguiResources();
public:
    virtual void update(float timeDelta);
    LoadingScreen(Application* app);
    ~LoadingScreen();
};
