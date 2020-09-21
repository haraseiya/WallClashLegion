#include "game.h"
#include "Math.h"
#include "Renderer.h"
#include "TestScene.h"
#include "PlayerActor.h"
#include "DebugGrid.h"
#include "LookDownCamera.h"
#include "LevelManager.h"

TestScene::TestScene()
{ 
	// プレーヤー
	PlayerActor *player = new PlayerActor;
	player->SetPosition(Vector3(250, 200, 0));

	GAMEINSTANCE.GetRenderer()->SetAmbientLight(Vector3(0.2f, 0.2f, 0.2f));
	DirectionalLight& dir = GAMEINSTANCE.GetRenderer()->GetDirectionalLight();
	dir.mDirection    = Vector3(0.7f, -0.7f, -0.7f);
	dir.mDiffuseColor = Vector3(0.78f, 0.88f, 1.0f);
	dir.mSpecColor    = Vector3(0.8f, 0.8f, 0.8f);

	Vector3 color(0, 1, 0);
	mGrid = new DebugGrid( 1000.0f, 30, color );

	LookDownCamera* c = new LookDownCamera(player);
	c->Init(Vector3(-300, 0, 300), Vector3(0, 0, 0), Vector3(0, 0, 1));

	// マップgpmesh読み込み
	GAMEINSTANCE.GetRenderer()->GetMesh("assets/ForestGround01.gpmesh");
	GAMEINSTANCE.GetRenderer()->GetMesh("assets/ForestGround02.gpmesh");
	GAMEINSTANCE.GetRenderer()->GetMesh("assets/ForestCastle.gpmesh"  );
	GAMEINSTANCE.GetRenderer()->GetMesh("assets/ForestCoin.gpmesh"    );

	mLevel = new LevelManager;

}

TestScene::~TestScene()
{
	delete mLevel;
}

SceneBase *TestScene::update()
{
	float radius = 160.0f;
	static float anim = 0.0f;
	anim += 0.01f;
	Matrix4 view;
	view = GAMEINSTANCE.GetViewMatrix();
	GAMEINSTANCE.GetRenderer()->SetViewMatrix(view);

	return this;
}

void TestScene::draw()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	//画面クリア
	GAMEINSTANCE.GetRenderer()->WindowClear();

	//ゲームシステム関連描画
	GAMEINSTANCE.GetRenderer()->Draw();
	//mGrid->Draw();

	//画面のフリップ
	GAMEINSTANCE.GetRenderer()->WindowFlip();
}