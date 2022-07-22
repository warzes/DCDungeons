#include "stdafx.h"
#include "Engine.h"
//-----------------------------------------------------------------------------
Engine* gEngine = nullptr;
//-----------------------------------------------------------------------------
Engine::Engine()
{
	gEngine = this;
}
//-----------------------------------------------------------------------------
Engine::~Engine()
{
	gEngine = nullptr;
}
//-----------------------------------------------------------------------------
bool Engine::Init(const EngineCreateInfo& createInfo)
{
	const int screenWidth = 1024;
	const int screenHeight = 768;
	InitWindow(screenWidth, screenHeight, "Game");
	SetTargetFPS(60);
	SetWindowState(FLAG_WINDOW_RESIZABLE);
	//SetExitKey(0);

	return true;
}
//-----------------------------------------------------------------------------
void Engine::Close()
{
	rCloseWindow();
}
//-----------------------------------------------------------------------------
bool Engine::BeginUpdate()
{
	if (WindowShouldClose()) return false;

	BeginDrawing();

	return true;
}
//-----------------------------------------------------------------------------
void Engine::EndUpdate()
{
	EndDrawing();
}
//-----------------------------------------------------------------------------
float Engine::GetDeltaTime() const
{
	return 0.0f;
}
//-----------------------------------------------------------------------------