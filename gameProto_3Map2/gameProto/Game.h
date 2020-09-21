#pragma once

#include <unordered_map>
#include <string>
#include <vector>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_types.h>
#include "math.h"


class Game
{
private:
	Game();   // �V���O���g��

	void Input();                                  // ���͏���
	void Draw();                                   // �`��
	int  Update();                                 // �t���[���X�V����
	void ActorUpdate();                            // �A�N�^�[�A�b�v�f�[�g
	void ShowActor();                              // �A�N�^�[���X�g�\���i�f�o�b�O�p�j
								                  
	class Renderer*     mRenderer;                 // �����_�����O�G���W��
	class SceneBase*    mNowScene;                 // �x�[�X�V�[���N���X
	class CameraActor*  mActiveCamera;             // �V�X�e�����`��Ɏg���J���� 
	class PhysicsWorld* mPhysicsWorld;             // �����蔻��V�X�e��

	bool  mIsRunning;                              // �Q�[�����[�v�񂷂��H
	bool  mIsPauseMode;                            // �|�[�Y���[�h

	std::vector<class Actor*> mActors;             // �A�N�^�[�z��
	std::vector<class Actor*> mPendingActors;      // �A�N�^�[�ǉ������p�z��

	float    mDeltaTime;                             // 1�t���[���̌o�ߎ��ԁi�b�P�ʁj
	Uint32   mTicksCount;                            // �o�ߎ��ԁi�~���b�P�ʁj
	Matrix4  mViewMatrix;

public:
	~Game();                                     
	static Game& GetInstance()                     // �C���X�^���X
	{
		static Game instance;
		return instance;
	}

	void Run();                                                                    // �Q�[���{�̎��s
	void Shutdown();                                                               // �I����
	bool Initialize(int screenWidth, int screenHeight, bool fullScreen = false);   // ��ʏ������ݒ�

	void setFirstScene(SceneBase* pScene) { mNowScene = pScene; }                  // �J�n�V�[���̃Z�b�g
	void setShutDown() { mIsRunning = false; }                                     // �V���b�g�_�E��
	
	class PhysicsWorld* const GetPhysics()
	                  { return mPhysicsWorld; }

	class Renderer* GetRenderer() { return mRenderer; }                            // �����_���[�V�X�e���̎擾
	SDL_Renderer* GetSDLRenderer();                                                // 2D��SDL�����_���[�̎擾

	void AddActor(class Actor* actor);                                             // �A�N�^�[�̒ǉ�
	void RemoveActor(class Actor* actor);                                          // �A�N�^�[�̍폜

	void SetCameraActor(class CameraActor* camera);      // �J�����A�N�^�[���V�X�e���ɓo�^
	void InActiveCamera(class CameraActor* inActiveCam); // �J�����̓o�^������
	const Matrix4& GetViewMatrix();                                                      // ���݃Z�b�g����Ă���J�����̃r���[�s���Ԃ�
	const Vector3& GetViewVector();
	const float    GetDeltaTime() { return mDeltaTime; }
};

#define GAMEINSTANCE Game::GetInstance()
#define RENDERER Game::GetInstance().GetRenderer()

