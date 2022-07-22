#include "stdafx.h"
#include "Engine.h"
#include "Game.h"
//-----------------------------------------------------------------------------
#if defined(_MSC_VER)
#	pragma comment( lib, "winmm.lib" )
#	pragma comment( lib, "3rdparty.lib" )
#endif
//-----------------------------------------------------------------------------
#if defined(_MSC_VER)
extern "C"
{
	// NVIDIA: Force usage of NVidia GPU in case there is an integrated graphics unit as well, if we don't do this we risk getting the integrated graphics unit and hence a horrible performance
	// -> See "Enabling High Performance Graphics Rendering on Optimus Systems" http://developer.download.nvidia.com/devzone/devcenter/gamegraphics/files/OptimusRenderingPolicies.pdf
	_declspec(dllexport) auto NvOptimusEnablement = 0x00000001UL;

	// AMD: Force usage of AMD GPU in case there is an integrated graphics unit as well, if we don't do this we risk getting the integrated graphics unit and hence a horrible performance
	// -> Named "Dynamic Switchable Graphics", found no official documentation, only https://community.amd.com/message/1307599#comment-1307599 - "Can an OpenGL app default to the discrete GPU on an Enduro system?"
	__declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}
#endif
//-----------------------------------------------------------------------------
#if defined(__EMSCRIPTEN__)
void UpdateFrame()
{
	if (!gEngine->BeginUpdate())
	{
		emscripten_cancel_main_loop();
		return;
	}
	gGame->Frame();
	gGame->Update();
	gEngine->EndUpdate();
}
#endif
//-----------------------------------------------------------------------------
int main(
	[[maybe_unused]] int   argc,
	[[maybe_unused]] char* argv[])
{
	constexpr auto getConfig = []() { return EngineCreateInfo {
			.width = 1024,
			.height = 768,
			.title = "Game",
		};
	};

	Engine engine;

	if (engine.Init(getConfig()))
	{
		Game game;
#if defined(__EMSCRIPTEN__)
		emscripten_set_main_loop(UpdateFrame, 0, 1);
#else
		while (engine.BeginUpdate())
		{
			game.Frame();
			game.Update();
			engine.EndUpdate();
		}
#endif
	}
	engine.Close();
}
//-----------------------------------------------------------------------------