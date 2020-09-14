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
	// �I���C�x���g
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

	// �L�[�{�[�h�̓��͍X�V
	INPUT_INSTANCE.Update();

	// ESC�������ꂽ��I��
	if (INPUT_INSTANCE.IsKeyPullUp(SDL_SCANCODE_ESCAPE)) m_isRunning = false;

	// F12�������ꂽ��A�N�^�[�f�o�b�O
	if (INPUT_INSTANCE.IsKeyPullUp(SDL_SCANCODE_F12))	 ShowActor();

	if (INPUT_INSTANCE.IsKeyPullUp(SDL_SCANCODE_BACKSPACE))
	{
		// �|�[�Y���[�h�ؑ�
		m_isPauseMode = !m_isPauseMode;
	}
}

void Game::Draw()
{
	if (!m_nowScene) return;
}

int Game::Update()
{
	// 16�~���b�ɂȂ�悤�ɑO�̃t���[������16�~���b�ȏ�o�߂���܂ő҂�
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), m_tickCount + 16));

	// �O�̃t���[�����猻�ݎ����܂ł̌o�ߎ��ԎZ�o(�b�P�ʁj
	m_deltaTime = (SDL_GetTicks() - m_tickCount + 16) / 1000.0f;

	// ���̃t���[���̊J�n���ԕۑ�(���̃t���[���܂ł̌o�ߎ��Ԑ}�邽�߁j
	m_tickCount = SDL_GetTicks();

	// �t���[�����Ԃ����܂�ɂ��o�߂��Ă���ꍇ��0.05 �� 20fps�Œ�
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
	// TODO: return �X�e�[�g�����g�������ɑ}�����܂�
}

const Vector3& Game::GetViewVector()
{
	// TODO: return �X�e�[�g�����g�������ɑ}�����܂�
}
