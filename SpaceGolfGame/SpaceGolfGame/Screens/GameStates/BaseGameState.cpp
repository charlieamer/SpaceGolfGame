#include "BaseGameState.h"
#include "../GameScreen.h"
#include "../../Components/VelocityComponent.h"
#include "../../Events/MouseEvents.h"

BaseGameState::BaseGameState(BaseScreen* screen, GameStateId stateType) : screen(screen), stateType(stateType)
{
}


BaseGameState::~BaseGameState()
{
}