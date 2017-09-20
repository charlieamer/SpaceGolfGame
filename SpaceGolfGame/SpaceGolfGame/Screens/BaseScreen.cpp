#include "BaseScreen.h"
#include "GameStates/BaseGameState.h"
#include <CEGUI/System.h>
#include <CEGUI/GUIContext.h>

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
}

BaseScreen::~BaseScreen()
{
	this->removeGameStateIfExists();
}

void BaseScreen::processMouse(const entry::MouseState & state)
{
	if (state.m_buttons[1] && !oldState.m_buttons[1]) {
		this->onLeftMouseButtonDown(state);
        CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonDown(CEGUI::MouseButton::LeftButton);
	}
	if (!state.m_buttons[1] && oldState.m_buttons[1]) {
		this->onLeftMouseButtonUp(state);
        CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonUp(CEGUI::MouseButton::LeftButton);
	}

	this->oldState = state;

	Vector2i newMousePos(state.m_mx, state.m_my);
	if (oldMousePos != newMousePos) {
		this->onMouseMove(newMousePos - oldMousePos, newMousePos);
		this->oldMousePos = newMousePos;
	}
}
