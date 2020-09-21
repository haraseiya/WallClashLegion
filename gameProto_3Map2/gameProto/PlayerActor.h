#pragma once
#include "Actor.h"

class PlayerActor : public Actor
{
public:
	typedef enum AnimationType
	{
		PLAYERANIM_IDLE = 0  ,   // 待機
		PLAYERANIM_RUN       ,   // 走る
		PLAYERANIM_JUMPSTART ,   // ジャンプスタート
		PLAYERANIM_JUMPLOOP  ,   // ジャンプループ    
		PLAYERANIM_JUMPEND   ,   // ジャンプ終了
		PLAYERANIM_ITEMNUM   ,   // 総アニメーション数
	}AnimationType;

	PlayerActor();
	~PlayerActor();

	void UpdateActor(float deltaTime) override;
	void StateChange();
	void FixCollision(class BoxCollider *hitPlayerBox, class BoxCollider *hitBox);

private:
	class SkeletalMeshComponent* mMeshComp;
	std::vector<const class Animation*> mAnimTypes;
	class BoxCollider* mHitBox;
	class BoxCollider* mHitGroundBox;
	class BoxCollider* mHitHeadBox;

	AnimationType mAnimState;
	bool          mIsJump;
	bool          mOnGroundChk;
	Vector3       mJumpVec;
	Vector3       mVelocityVec;

};