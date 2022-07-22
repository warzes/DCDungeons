#pragma once

#include "GameLogic.h"

class Game
{
public:
	Game();

	void Close();

	void Frame();
	void Update();
private:
	GameLogic m_logic;
};

extern Game* gGame;