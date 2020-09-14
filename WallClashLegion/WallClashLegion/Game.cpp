#include "Game.h"
#include "Input.h"

Game::Game()
	: m_renderer(nullptr)
	, m_nowScene(nullptr)
	, m_isRunning(true)
	, m_isPauseMode(false)
	, m_activeCamera(nullptr)
	, m_physicsWorld(nullptr)
{
}

Game::~Game()
{
}

void Game::Input()
{
	// 終了イベント
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			m_isRunning = false;
			break;
		}
	}

	// キーボードの入力更新
	INPUT_INSTANCE.Update();

	// ESCが押されたら終了
	if (INPUT_INSTANCE.IsKeyPullUp(SDL_SCANCODE_ESCAPE)) m_isRunning = false;

	// F12が押されたらアクターデバッグ
	if (INPUT_INSTANCE.IsKeyPullUp(SDL_SCANCODE_F12))	 ShowActor();

	if (INPUT_INSTANCE.IsKeyPullUp(SDL_SCANCODE_BACKSPACE))
	{
		// ポーズモード切替
		m_isPauseMode = !m_isPauseMode;
	}
}

void Game::Draw()
{
	if (!m_nowScene) return;
}

int Game::Update()
{
	// 16ミリ秒になるように前のフレームから16ミリ秒以上経過するまで待つ
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), m_tickCount + 16));

	// 前のフレームから現在時刻までの経過時間算出(秒単位）
	m_deltaTime = (SDL_GetTicks() - m_tickCount + 16) / 1000.0f;

	// このフレームの開始時間保存(次のフレームまでの経過時間図るため）
	m_tickCount = SDL_GetTicks();

	// フレーム時間があまりにも経過している場合は0.05 → 20fps固定
	if (m_deltaTime > 0.05f) m_deltaTime = 0.05f;
}

void Game::ActorUpdate()
{
}

void Game::ShowActor()
{
}


void Game::Run()
{
}

void Game::ShutDown()
{
}

bool Game::Initialize(int _screenWidth, int _screenHeight, bool _isFullScreen)
{
	return false;
}

SDL_Renderer* Game::GetSDLRenderer()
{
	return nullptr;
}

void Game::AddActor(Actor* _actor)
{
}

void Game::RemoveActor(Actor* _actor)
{
}

void Game::SetCameraActor(CameraActor* _camera)
{
}

void Game::InActiveCamera(CameraActor* _inActiveCam)
{
}

const Matrix4& Game::GetViewMatrix()
{
	// TODO: return ステートメントをここに挿入します
}

const Vector3& Game::GetViewVector()
{
	// TODO: return ステートメントをここに挿入します
}
