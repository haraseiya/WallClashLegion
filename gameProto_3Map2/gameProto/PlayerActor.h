#pragma once
#include "Actor.h"

class PlayerActor : public Actor
{
public:
	typedef enum AnimationType
	{
		PLAYERANIM_IDLE = 0  ,   // �ҋ@
		PLAYERANIM_RUN       ,   // ����
		PLAYERANIM_JUMPSTART ,   // �W�����v�X�^�[�g
		PLAYERANIM_JUMPLOOP  ,   // �W�����v���[�v    
		PLAYERANIM_JUMPEND   ,   // �W�����v�I��
		PLAYERANIM_ITEMNUM   ,   // ���A�j���[�V������
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