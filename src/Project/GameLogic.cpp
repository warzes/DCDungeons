#include "stdafx.h"
#include "GameLogic.h"
//-----------------------------------------------------------------------------
//rlFPCamera cam;
float offset = 2.0f;
bool ret = false;
bool stopAnim = true;
float maxY = 0.0f;
static const Vector2 posModel = { 3.0f, 3.0f };
//-----------------------------------------------------------------------------
GameLogic::GameLogic()
{
	//cam.Setup(45, Vector3{ 0, 10, 0 });
	//cam.MoveSpeed.z = 10;
	//cam.MoveSpeed.x = 5;
	//cam.FarPlane = 5000;

	m_playerCamera.Init({ 5.0f, 0.0f, 10.0f }, 180, 90);
	m_playerAnimation.Init();
	m_world.Init();
}
//-----------------------------------------------------------------------------
void GameLogic::Start()
{
}
//-----------------------------------------------------------------------------
void GameLogic::Frame()
{
	ClearBackground({ 50, 100, 200 });

	//cam.BeginMode3D();
	BeginMode3D(m_playerCamera.GetCamera());
	{
		DrawPlane(Vector3{ 0, 0, 0 }, Vector2{ 50, 50 }, BEIGE);
		m_world.Frame();
	}
	EndMode3D();
	//cam.EndMode3D();
	m_playerAnimation.Draw2D();

	DrawFPS(0, 0);
}
//-----------------------------------------------------------------------------
void GameLogic::Update()
{
	if (!stopAnim)
	{
		offset += 0.5 * GetFrameTime() * (ret ? 1 : -1);
		if (offset < -2 || offset > 2)
			ret = !ret;
	}

	Matrix matScale = MatrixScale(1.0f, 1.0f, 1.0f);
	Matrix matRotation = MatrixRotate({ 0.0f, 1.0f, 0.0f }, 0.0f * DEG2RAD);
	Matrix matTranslation = MatrixTranslate(posModel.x, 0.2f, posModel.y);
	Matrix matTransform = MatrixMultiply(MatrixMultiply(matScale, matRotation), matTranslation);
	Matrix world = MatrixTranspose(matTransform);

	matScale = MatrixScale(0.3f, 0.3f, 0.3f);
	matRotation = MatrixRotate({ 0.0f, 1.0f, 0.0f }, 0.0f * DEG2RAD);
	matTranslation = MatrixTranslate(posModel.x + offset, 1.0f, posModel.y);
	matTransform = MatrixMultiply(MatrixMultiply(matScale, matRotation), matTranslation);
	world = MatrixTranspose(matTransform);
	
	/*auto pos = m_playerCamera.GetPosition();
	pos.y = 10;
	cam.SetCameraPosition(pos);
	cam.Update();*/

	// Player logic
	m_playerCamera.Update(m_world, GetFrameTime());
	m_playerAnimation.Update(GetFrameTime());

	// Player Attack Events
	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
	{
		m_playerAnimation.StartAnimationAttacking();
	}

	// Attack logic
	if (m_playerAnimation.IsEndAnimationAttack())
	{
		const Vector2 rayMousePos = { static_cast<float>(GetScreenWidth() / 2), static_cast<float>(GetScreenHeight() / 2) };
		const Ray ray = GetMouseRay(rayMousePos, m_playerCamera.GetCamera());
	}
}
//-----------------------------------------------------------------------------
void GameLogic::Stop()
{
	m_playerAnimation.Close();
	m_world.Close();
}
//-----------------------------------------------------------------------------