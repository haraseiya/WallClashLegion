#include "PlayerActor.h"
#include "Game.h"
#include "Input.h"
#include "Mesh.h"
#include "Renderer.h"
#include "MeshComponent.h"
#include "SkeletalMeshComponent.h"
#include "Skeleton.h"
#include "Animation.h"
#include "PhysicsWorld.h"
#include "BoxCollider.h"
#include "Collision.h"

const float cAnimationSpeed = 0.5f;

PlayerActor::PlayerActor()
	:mAnimState(AnimationType::PLAYERANIM_IDLE)
	,mIsJump(false)
	,mOnGroundChk(true)
{
	//���b�V���̃��[�h
	Mesh* mesh = RENDERER->GetMesh("assets/SK_Mannequin.gpmesh");
	mMeshComp = new SkeletalMeshComponent(this);
	mMeshComp->SetMesh(mesh);

	// �X�P���g��
	mMeshComp->SetSkeleton(RENDERER->GetSkeleton("Assets/SK_Mannequin.gpskel"));
	
	// �A�j���[�V�����̎擾 & �A�j���[�V�����z��ɃZ�b�g
	mAnimTypes.resize(AnimationType::PLAYERANIM_ITEMNUM);
	mAnimTypes[PLAYERANIM_IDLE]      = RENDERER->GetAnimation("Assets/ThirdPersonIdle.gpanim", true);
	mAnimTypes[PLAYERANIM_RUN]       = RENDERER->GetAnimation("Assets/ThirdPersonRun.gpanim", true);
	mAnimTypes[PLAYERANIM_JUMPSTART] = RENDERER->GetAnimation("Assets/ThirdPersonJump_Start.gpanim", false);
	mAnimTypes[PLAYERANIM_JUMPLOOP]  = RENDERER->GetAnimation("Assets/ThirdPersonJump_Loop.gpanim", false);
	mAnimTypes[PLAYERANIM_JUMPEND]   = RENDERER->GetAnimation("Assets/ThirdPersonJump_End.gpanim", false);

	// �A�C�h����ԃA�j���[�V�������Z�b�g
	mMeshComp->PlayAnimation( mAnimTypes[PLAYERANIM_IDLE], cAnimationSpeed);

	// �����蔻��Z�b�g
	AABB playerBox = mesh->GetCollisionBox();
	mHitBox = new BoxCollider(this,PhysicsWorld::EnumPlayer);
	playerBox.mMin.x *= 0.6f;
	playerBox.mMin.y *= 0.6f;
	playerBox.mMax.x *= 0.6f;
	playerBox.mMax.y *= 0.6f;
	mHitBox->SetObjectBox(playerBox);

	// �v���[���[�̑����𒲂ׂ�{�b�N�X���쐬�@�{�b�N�X��1/4, �{�b�N�X��ʂ����_�ɗ���悤�ɂ���
	AABB groundBox;
	groundBox = playerBox;
	groundBox.mMin.x *= 0.8f;
	groundBox.mMin.y *= 0.8f;
	groundBox.mMax.x *= 0.8f;
	groundBox.mMax.y *= 0.8f;
	groundBox.mMin.z = -2.0f;  //�W�����v���Ɉ���������Ȃ�����
	groundBox.mMax.z *= 0.0f;
	mHitGroundBox = new BoxCollider(this, PhysicsWorld::EnumPlayer);
	mHitGroundBox->SetObjectBox(groundBox);

	// �v���[���[�̓���𒲂ׂ�{�b�N�X���쐬 �{�b�N�X��ʂ�����ɗ���悤�ɂ���
	AABB headBox;
	headBox = groundBox;
	headBox.mMin.z = playerBox.mMax.z;
	headBox.mMax.z = headBox.mMin.z + 2.0f;
	mHitHeadBox = new BoxCollider(this, PhysicsWorld::EnumPlayer);
	mHitHeadBox->SetObjectBox(headBox);
	
	printf("PlayerActor�쐬 id:[%5d] this : (0x%p)\n", mID, this);
	mJumpVec = Vector3(0, 0, 0);
}

PlayerActor::~PlayerActor()
{
	mAnimTypes.clear(); //�A�j���[�V�����{�̂̏����̓����_���[���ōs����
	printf("PlayerActor�j�� id:[%5d] this : (0x%p)\n", mID, this);
}

void PlayerActor::UpdateActor(float deltaTime)
{
	//�L������ԑJ��
	StateChange();

	// �W�����v�I�����̓L�[���͎󂯕t���Ȃ�
	if (mAnimState == PLAYERANIM_JUMPEND) return;

	//�L��������
	const float speed = 200.0f;
	Vector3 forwardVec = Vector3(1.0f, 0.0f, 0.0f);
	Vector3 rightVec   = Vector3(0.0f, 1.0f, 0.0f);
	Vector3 charaForwardVec = GetForward();

	// �L�����N�^�[�ړ�
	Vector3 DirVec(0.0f, 0.0f, 0.0f);
	if (INPUT_INSTANCE.IsKeyPressed(SDL_SCANCODE_UP)) DirVec += forwardVec;
	if (INPUT_INSTANCE.IsKeyPressed(SDL_SCANCODE_DOWN)) DirVec -= forwardVec;
	if (INPUT_INSTANCE.IsKeyPressed(SDL_SCANCODE_RIGHT)) DirVec += rightVec;
	if (INPUT_INSTANCE.IsKeyPressed(SDL_SCANCODE_LEFT)) DirVec -= rightVec;

	//�W�����v
	if (INPUT_INSTANCE.IsKeyPushdown(SDL_SCANCODE_SPACE) && !mIsJump)
	{
		mJumpVec.z += 320.0f * deltaTime;
		mIsJump = true;
		mMeshComp->PlayAnimation(mAnimTypes[PLAYERANIM_JUMPSTART], cAnimationSpeed);
		mAnimState = PLAYERANIM_JUMPSTART;
	}

	if (mIsJump) mJumpVec.z -= 5.0f * deltaTime;
	
	if (DirVec.LengthSq() > 0.5f)
	{
		// �����L�[����
		charaForwardVec = DirVec;

		// �i�s�����Ɍ����ĉ�]
		charaForwardVec.Normalize();
		RotateToNewForward(charaForwardVec);

		// ���݂̃X�s�[�h��ۑ�
		mSpeed = speed * deltaTime;
	}
	else
	{
		charaForwardVec = Vector3(0, 0, 0);
	}

	// �i�s�����Ɉړ�
	mPosition += mSpeed * charaForwardVec + mJumpVec;
	mRecomputeWorldTransform = true;

	// �����蔻�菈���Œn�ʃt���O��false�ɂ��A���̌�̓����蔻�菈����true�ɂȂ邩�`�F�b�N����
	mOnGroundChk = false;
}

// �L������ԑJ��
void PlayerActor::StateChange()
{
	//�O��̓����蔻�菈���ŉ��ɒn�ʂ��Ȃ�������W�����v���ֈڍs����
	if ( !mIsJump && !mOnGroundChk && mPosition.z > 0.0)
	{
		mIsJump = true;
		if (mAnimState != PLAYERANIM_JUMPLOOP)
		{
			mMeshComp->PlayAnimation(mAnimTypes[PLAYERANIM_JUMPLOOP], cAnimationSpeed);
			mAnimState = PLAYERANIM_JUMPLOOP;
		}
		return;
	}
	if(mIsJump)
	{ 
		// JUMP�J�n����JumpLoop��
		if (mAnimState == PLAYERANIM_JUMPSTART)
		{
 			if (!(mMeshComp->IsPlaying()))
			{
				mMeshComp->PlayAnimation(mAnimTypes[PLAYERANIM_JUMPLOOP], cAnimationSpeed);
				mAnimState = PLAYERANIM_JUMPLOOP;
			}
		}
		return;
	}

	// �L�[���͂���A�j���[�V������Ԃֈڍs
	bool IsIdleStart = INPUT_INSTANCE.IsKeyOff(SDL_SCANCODE_UP)    &
		               INPUT_INSTANCE.IsKeyOff(SDL_SCANCODE_RIGHT) &
		               INPUT_INSTANCE.IsKeyOff(SDL_SCANCODE_DOWN)  & 
		               INPUT_INSTANCE.IsKeyOff(SDL_SCANCODE_LEFT);

	// �ҋ@�A�j���J�n
	if (IsIdleStart)
	{
		if (mAnimState == PLAYERANIM_JUMPEND)
		{
			if (!mMeshComp->IsPlaying())
			{
				mMeshComp->PlayAnimation(mAnimTypes[PLAYERANIM_IDLE], cAnimationSpeed);
				mAnimState = PLAYERANIM_IDLE;
			}
		}
		else if ((mAnimState != PLAYERANIM_IDLE))
		{
			mMeshComp->PlayAnimation(mAnimTypes[PLAYERANIM_IDLE], cAnimationSpeed);
			mAnimState = PLAYERANIM_IDLE;
		}
	}
	else
	{
		// �W�����v�I���A�j�������RUN�J�n
		if (mAnimState == PLAYERANIM_JUMPEND)
		{
			if (!mMeshComp->IsPlaying())
			{
				mMeshComp->PlayAnimation(mAnimTypes[PLAYERANIM_RUN], cAnimationSpeed);
				mAnimState = PLAYERANIM_RUN;
			}
		}

		// RUN�A�j���J�n
		if (mAnimState != PLAYERANIM_RUN)
		{
			mMeshComp->PlayAnimation(mAnimTypes[PLAYERANIM_RUN], cAnimationSpeed);
			mAnimState = PLAYERANIM_RUN;
		}
	}

}

// �w�iAABB�Ƃ̃q�b�g�߂荞�݉��� ( ���������ۂ�PhysicsWorld����Ă΂�� �j
void PlayerActor::FixCollision(BoxCollider *hitPlayerBox, BoxCollider * hitBox)
{
	Vector3 fix;
	//���������蔻�肪�q�b�g�������H
	if (hitPlayerBox == mHitGroundBox && mJumpVec.z <= 0.0f)
	{
		mOnGroundChk = true;
		// �W�����v���Ȃ����
		if (mIsJump)
		{
			mIsJump = false;
			mJumpVec = Vector3(0, 0, -1.0f);
			mPosition += mJumpVec;
			if (mAnimState == PLAYERANIM_JUMPLOOP)
			{
				mMeshComp->PlayAnimation(mAnimTypes[PLAYERANIM_JUMPEND], cAnimationSpeed);
				mAnimState = PLAYERANIM_JUMPEND;
			}
			return;
		}
	}

	//�ǂƂԂ������Ƃ�
	AABB bgBox = hitBox->GetWorldBox();
	AABB playerBox = mHitBox->GetWorldBox();

	// �߂荞�݂��C��
	calcCollisionFixVec(playerBox, bgBox, fix);

	// �␳�x�N�g�����߂�
	mPosition += fix;

	// �W�����v�A�N�V�������ɓ����ǂɓ��������Ƃ�
	if (hitPlayerBox == mHitHeadBox && mIsJump)
	{
		//�W�����v������ɍs���������t�]������
		mJumpVec = Vector3(0, 0, -1.0f);
		mPosition += mJumpVec; // ��������ɓ�����Ȃ��l�ɗ���
	}

	// �ʒu���ς�����̂Ń{�b�N�X�Čv�Z
	mHitBox->OnUpdateWorldTransform();

}
