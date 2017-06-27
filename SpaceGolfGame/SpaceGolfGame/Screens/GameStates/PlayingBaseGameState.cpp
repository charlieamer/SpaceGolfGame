#include "PlayingBaseGameState.h"

PlayingBaseGameState::PlayingBaseGameState(GameScreen * screen, GameStateId id) : BaseGameState::BaseGameState(screen, id), gameScreen(screen)
{
}