#include "Game.h"
#include "Renderer.h"
#include "Mesh.h"
#include "LevelManager.h"
#include "BGBlock.h"

char map[][10][10] =
{
	{
		{1,2,1,2,1,2,1,2,1,2,},
		{2,1,2,1,2,1,2,1,2,1,},
		{1,2,1,2,1,2,1,2,1,2,},
		{2,1,2,1,2,1,2,1,2,1,},
		{1,2,1,2,1,2,1,2,1,2,},
		{2,1,2,1,2,1,2,1,2,1,},
		{1,2,1,2,1,2,1,2,1,2,},
		{2,1,2,1,2,1,2,1,2,1,},
		{1,2,1,2,1,2,1,2,1,2,},
		{2,1,2,1,2,1,2,1,2,1,},
	},
	{
		{2,1,2,1,2,1,2,1,2,1,},
		{1,0,0,0,0,0,1,1,1,2,},
		{2,0,0,0,0,0,0,0,0,1,},
		{1,0,0,0,0,0,0,0,0,2,},
		{2,0,0,0,0,0,0,0,0,1,},
		{1,0,0,2,1,2,0,0,1,2,},
		{2,0,0,1,2,1,0,0,2,1,},
		{1,0,0,2,1,2,0,0,1,2,},
		{2,0,0,0,0,0,0,0,0,1,},
		{1,2,1,2,1,2,1,2,1,2,},
	},
	{
		{0,1,2,1,2,1,2,1,2,1,},
		{0,0,0,0,0,0,1,2,1,2,},
		{0,0,0,0,2,0,0,0,0,1,},
		{0,0,0,0,0,0,0,0,0,2,},
		{0,0,0,0,0,0,0,0,0,1,},
		{0,0,0,1,2,1,0,0,0,2,},
		{0,0,0,0,1,2,0,0,0,1,},
		{0,0,0,0,2,1,0,0,0,2,},
		{0,0,0,0,0,0,0,0,0,1,},
		{0,2,1,2,1,2,1,2,1,2,},
	},
};

LevelManager::LevelManager()
	:mCamera(nullptr)
{
	mBlockMeshs.push_back(GAMEINSTANCE.GetRenderer()->GetMesh("assets/ForestGround01.gpmesh")); // 地面1
	mBlockMeshs.push_back(GAMEINSTANCE.GetRenderer()->GetMesh("assets/ForestGround02.gpmesh")); // 地面2
	mBlockMeshs.push_back(GAMEINSTANCE.GetRenderer()->GetMesh("assets/ForestCastle.gpmesh"));   // お城
	mBlockMeshs.push_back(GAMEINSTANCE.GetRenderer()->GetMesh("assets/ForestCoin.gpmesh"));     // コイン
	BGBlock *block;
	const float blockSize = 200.0f;
	for (int iz = 0; iz < 3; iz++)
	{
		for (int iy = 0; iy < 10; iy++)
		{
			for (int ix = 0; ix < 10; ix++)
			{
				if (map[iz][iy][ix] == 0)
				{
					// 0は空白なので飛ばす
					continue;
				}
				if (map[iz][iy][ix] < 3)
				{
					// 1～2 ブロック
					block = new BGBlock;
					block->SetMesh(mBlockMeshs[map[iz][iy][ix] - 1]); //mapからデータ参照 (-1は mapと mBlockMeshとの整合性とるため)
					block->SetPosition(Vector3(ix * blockSize, iy * blockSize, (iz - 1) * blockSize));
				}
			}
		}
	}
	block = new BGBlock;
	block->SetMesh(mBlockMeshs[1]);
	block->SetPosition(Vector3(1000, 800, 400));

	block = new BGBlock;
	block->SetMesh(mBlockMeshs[2]);
	block->SetPosition(Vector3(2000, 1200, 400));

	Quaternion q;
	q.Set(0, 0, sinf(3.14f/4.0f), cosf(3.14f / 4.0f));
	q.Normalize();
	block->SetRotation(q);
}

LevelManager::~LevelManager()
{
	mBlockMeshs.clear();
}

bool LevelManager::LoadLevel(const char * levelMapJsonFile)
{

	return true;
}

void LevelManager::SetViewRange(float width, float height)
{
	mLeftUpPos.x    = -width  * 0.5f;
	mRightDownPos.x =  width  * 0.5f;
	mLeftUpPos.y    = -height * 0.5f;
	mRightDownPos.y =  height * 0.5f;
}

void LevelManager::Update()
{

}
