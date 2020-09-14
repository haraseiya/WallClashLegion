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

	void Input();			// 入力処理
	void Draw();			// 描画
	int Update();			// 更新処理
	void ActorUpdate();		// アクター更新処理
	void ShowActor();		// アクターリスト表示（デバッグ用）

	class Renderer* m_renderer;				// レンダリング
	class SceneBase* m_nowScene;			// ベースシーン
	class CameraActor* m_activeCamera;		// システムが描画に使うカメラ
	class PhysicsWorld* m_physicsWorld;		// 当たり判定システム

	bool m_isRunning;						// ゲームループを回すか？
	bool m_isPauseMode;						// ポーズモード

	std::vector<class Actor*> m_actors;			// アクター配列
	std::vector<class Actor*> m_pendingActors;	// アクター追加準備用配列

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
