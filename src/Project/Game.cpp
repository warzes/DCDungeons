#include "stdafx.h"
#include "Game.h"

Game* gGame = nullptr;

Game::Game()
{
	gGame = this;
	m_logic.Start();
}

void Game::Close()
{
	m_logic.Stop();
}

void Game::Frame()
{
	m_logic.Frame();
}

void Game::Update()
{
	m_logic.Update();
}
