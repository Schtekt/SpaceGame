#include "GameState.h"
#include "Game.h"
GameState::GameState(Game* game): m_pGame(game)
{
}

void GameState::ChangeState(GameState* state)
{
	m_pLastState = state;
	m_pGame->changeState(state);
}
