#pragma once

#include <unordered_map>
#include <string>
#include <vector>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_types.h>
#include "Math.h"

class Game
{
private:
	Game();

	void Input();			// ���͏���
	void Draw();			// �`��
	int Update();			// �X�V����
	void ActorUpdate();		// �A�N�^�[�X�V����
	void ShowActor();		// �A�N�^�[���X�g�\���i�f�o�b�O�p�j

	class Renderer* m_renderer;				// �����_�����O
	class SceneBase* m_nowScene;			// �x�[�X�V�[��
	class CameraActor* m_activeCamera;		// �V�X�e�����`��Ɏg���J����
	class PhysicsWorld* m_physicsWorld;		// �����蔻��V�X�e��

	bool m_isRunning;						// �Q�[�����[�v���񂷂��H
	bool m_isPauseMode;						// �|�[�Y���[�h

	std::vector<class Actor*> m_actors;			// �A�N�^�[�z��
	std::vector<class Actor*> m_pendingActors;	// �A�N�^�[�ǉ������p�z��

	float m_deltaTime;
	Uint32 m_tickCount;
	Matrix4 m_viewMatrix;

public:
	~Game();
	static Game& GetInstance()
	{
		static Game instance;
		return instance;
	}

	void Run();
	void ShutDown();
	bool Initialize(int _screenWidth, int _screenHeight, bool _isFullScreen = false);

	void SetFirstScene(SceneBase* _pScene) { m_nowScene = _pScene; }
	void SetShutDown() { m_isRunning = false; }

	class PhysicsWorld* const GetPhysics() { return m_physicsWorld; }

	class Renderer* GetRenderer() { m_renderer; }
	SDL_Renderer* GetSDLRenderer();

	void AddActor(class Actor* _actor);
	void RemoveActor(class Actor* _actor);

	void SetCameraActor(class CameraActor* _camera);
	void InActiveCamera(class CameraActor* _inActiveCam);
	const Matrix4& GetViewMatrix();
	const Vector3& GetViewVector();
	const float GetDeltaTime (){ return m_deltaTime; }
};

#define GAMEINSTANCE Game::GetInstance()
#define RENDERER Game::GetInstance().GetRenderer();
