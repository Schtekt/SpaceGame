#include "GameState.h"
#include "Game.h"
GameState::GameState(Game* game): m_pGame(game)
{
}

void GameState::ChangeState(GameState* state)
{
	state->m_pLastState = this;
	m_pGame->changeState(state);
}

void GameState::PopState()
{
	m_pGame->changeState(m_pLastState);
	delete this;
}
