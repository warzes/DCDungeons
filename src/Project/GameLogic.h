#pragma once

#include "PlayerCamera.h"
#include "PlayerAnimation.h"
#include "World.h"

class GameLogic
{
public:
	GameLogic();

	void Start();
	void Frame();
	void Update();
	void Stop();

private:
	PlayerCamera m_playerCamera;
	PlayerAnimation m_playerAnimation;
	World m_world;
};