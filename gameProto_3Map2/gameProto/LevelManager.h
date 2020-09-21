#pragma once
#include "Game.h"

class LevelManager
{
public:
	LevelManager();
	~LevelManager();
	bool LoadLevel(const char* levelMapJsonFile);
	void SetCamera(class LookDownCamera* cam) { mCamera = cam; }
	void SetViewRange(float width, float height);
	void Update();

private:
	Vector3 mLeftUpPos, mRightDownPos;
	Vector3 mNowRangeMin, mNowRangeMax;
	class LookDownCamera *mCamera;
	std::vector<class Mesh*> mBlockMeshs;
	friend class PhysicsWorld;

	int mMapXNum;
	int mMapYNum;

	float mBlockSize;
};