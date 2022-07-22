#pragma once

struct EngineCreateInfo
{
	int width = 1024;
	int height = 768;
	const char* title = "Game";
};

class Engine
{
public:
	Engine();
	~Engine();

	bool Init(const EngineCreateInfo& createInfo);
	void Close();

	bool BeginUpdate();
	void EndUpdate();

	float GetDeltaTime() const;
};

extern Engine* gEngine;