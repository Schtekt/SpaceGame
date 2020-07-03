#include "GameState.h"
#include "Game.h"
GameState::GameState(Game* game): m_pGame(game)
{
}

GameState::~GameState()
{
}

void GameState::ChangeState(GameState* state)
{
	state->m_pLastState = this;
	m_pGame->ChangeState(state);
}

void GameState::PopState()
{
	m_pGame->ChangeState(m_pLastState);
	delete this;
}
