#include "BaseScreen.h"
#include "GameStates/BaseGameState.h"
#include <CEGUI/System.h>
#include <CEGUI/GUIContext.h>
#include <CEGUI/WindowManager.h>
#include "../Components/PositionComponent.h"
#include "../Rendering/RenderManager.h"

void BaseScreen::setGameState(BaseGameState * newGameState)
{
	newGameState->activate();
	this->removeGameStateIfExists();
	this->gameState = newGameState;
}

void BaseScreen::removeGameStateIfExists()
{
	if (this->gameState) {
		this->gameState->deactivate();
		delete this->gameState;
		this->gameState = NULL;
	}
}

BaseScreen::BaseScreen(Application * app) : app(app), gameState(NULL)
{
    camera = entities.create();
    camera.assign<PositionComponent>();
}

BaseScreen::~BaseScreen()
{
	this->removeGameStateIfExists();
    entities.reset();
    RenderManager::get().destroy();
    if (CEGUI::System::getSingletonPtr()) {
        CEGUI::WindowManager::getSingleton().destroyAllWindows();
    }
}

void BaseScreen::processMouse(const entry::MouseState & state)
{
	if (state.m_buttons[1] && !oldState.m_buttons[1]) {
		this->onLeftMouseButtonDown(state);
        if (CEGUI::System::getSingletonPtr()) {
            CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonDown(CEGUI::MouseButton::LeftButton);            
        }
	}
	if (!state.m_buttons[1] && oldState.m_buttons[1]) {
		this->onLeftMouseButtonUp(state);
        if (CEGUI::System::getSingletonPtr()) {
            CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonUp(CEGUI::MouseButton::LeftButton);
        }
	}

	this->oldState = state;

	Vector2i newMousePos(state.m_mx, state.m_my);
	if (oldMousePos != newMousePos) {
		this->onMouseMove(newMousePos - oldMousePos, newMousePos);
		this->oldMousePos = newMousePos;
	}
}

Vector2f BaseScreen::getCameraPosition() {
    return this->camera.component<PositionComponent>()->pos;
}