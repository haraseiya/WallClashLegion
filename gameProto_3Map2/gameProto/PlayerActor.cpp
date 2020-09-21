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
	//メッシュのロード
	Mesh* mesh = RENDERER->GetMesh("assets/SK_Mannequin.gpmesh");
	mMeshComp = new SkeletalMeshComponent(this);
	mMeshComp->SetMesh(mesh);

	// スケルトン
	mMeshComp->SetSkeleton(RENDERER->GetSkeleton("Assets/SK_Mannequin.gpskel"));
	
	// アニメーションの取得 & アニメーション配列にセット
	mAnimTypes.resize(AnimationType::PLAYERANIM_ITEMNUM);
	mAnimTypes[PLAYERANIM_IDLE]      = RENDERER->GetAnimation("Assets/ThirdPersonIdle.gpanim", true);
	mAnimTypes[PLAYERANIM_RUN]       = RENDERER->GetAnimation("Assets/ThirdPersonRun.gpanim", true);
	mAnimTypes[PLAYERANIM_JUMPSTART] = RENDERER->GetAnimation("Assets/ThirdPersonJump_Start.gpanim", false);
	mAnimTypes[PLAYERANIM_JUMPLOOP]  = RENDERER->GetAnimation("Assets/ThirdPersonJump_Loop.gpanim", false);
	mAnimTypes[PLAYERANIM_JUMPEND]   = RENDERER->GetAnimation("Assets/ThirdPersonJump_End.gpanim", false);

	// アイドル状態アニメーションをセット
	mMeshComp->PlayAnimation( mAnimTypes[PLAYERANIM_IDLE], cAnimationSpeed);

	// あたり判定セット
	AABB playerBox = mesh->GetCollisionBox();
	mHitBox = new BoxCollider(this,PhysicsWorld::EnumPlayer);
	playerBox.mMin.x *= 0.6f;
	playerBox.mMin.y *= 0.6f;
	playerBox.mMax.x *= 0.6f;
	playerBox.mMax.y *= 0.6f;
	mHitBox->SetObjectBox(playerBox);

	// プレーヤーの足元を調べるボックスを作成　ボックス高1/4, ボックス上面が原点に来るようにする
	AABB groundBox;
	groundBox = playerBox;
	groundBox.mMin.x *= 0.8f;
	groundBox.mMin.y *= 0.8f;
	groundBox.mMax.x *= 0.8f;
	groundBox.mMax.y *= 0.8f;
	groundBox.mMin.z = -2.0f;  //ジャンプ時に引っかからない高さ
	groundBox.mMax.z *= 0.0f;
	mHitGroundBox = new BoxCollider(this, PhysicsWorld::EnumPlayer);
	mHitGroundBox->SetObjectBox(groundBox);

	// プレーヤーの頭上を調べるボックスを作成 ボックス底面が頭上に来るようにする
	AABB headBox;
	headBox = groundBox;
	headBox.mMin.z = playerBox.mMax.z;
	headBox.mMax.z = headBox.mMin.z + 2.0f;
	mHitHeadBox = new BoxCollider(this, PhysicsWorld::EnumPlayer);
	mHitHeadBox->SetObjectBox(headBox);
	
	printf("PlayerActor作成 id:[%5d] this : (0x%p)\n", mID, this);
	mJumpVec = Vector3(0, 0, 0);
}

PlayerActor::~PlayerActor()
{
	mAnimTypes.clear(); //アニメーション本体の消去はレンダラー側で行われる
	printf("PlayerActor破棄 id:[%5d] this : (0x%p)\n", mID, this);
}

void PlayerActor::UpdateActor(float deltaTime)
{
	//キャラ状態遷移
	StateChange();

	// ジャンプ終了時はキー入力受け付けない
	if (mAnimState == PLAYERANIM_JUMPEND) return;

	//キャラ入力
	const float speed = 200.0f;
	Vector3 forwardVec = Vector3(1.0f, 0.0f, 0.0f);
	Vector3 rightVec   = Vector3(0.0f, 1.0f, 0.0f);
	Vector3 charaForwardVec = GetForward();

	// キャラクター移動
	Vector3 DirVec(0.0f, 0.0f, 0.0f);
	if (INPUT_INSTANCE.IsKeyPressed(SDL_SCANCODE_UP)) DirVec += forwardVec;
	if (INPUT_INSTANCE.IsKeyPressed(SDL_SCANCODE_DOWN)) DirVec -= forwardVec;
	if (INPUT_INSTANCE.IsKeyPressed(SDL_SCANCODE_RIGHT)) DirVec += rightVec;
	if (INPUT_INSTANCE.IsKeyPressed(SDL_SCANCODE_LEFT)) DirVec -= rightVec;

	//ジャンプ
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
		// 方向キー入力
		charaForwardVec = DirVec;

		// 進行方向に向けて回転
		charaForwardVec.Normalize();
		RotateToNewForward(charaForwardVec);

		// 現在のスピードを保存
		mSpeed = speed * deltaTime;
	}
	else
	{
		charaForwardVec = Vector3(0, 0, 0);
	}

	// 進行方向に移動
	mPosition += mSpeed * charaForwardVec + mJumpVec;
	mRecomputeWorldTransform = true;

	// 当たり判定処理で地面フラグをfalseにし、この後の当たり判定処理でtrueになるかチェックする
	mOnGroundChk = false;
}

// キャラ状態遷移
void PlayerActor::StateChange()
{
	//前回の当たり判定処理で下に地面がなかったらジャンプ中へ移行する
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
		// JUMP開始からJumpLoopへ
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

	// キー入力からアニメーション状態へ移行
	bool IsIdleStart = INPUT_INSTANCE.IsKeyOff(SDL_SCANCODE_UP)    &
		               INPUT_INSTANCE.IsKeyOff(SDL_SCANCODE_RIGHT) &
		               INPUT_INSTANCE.IsKeyOff(SDL_SCANCODE_DOWN)  & 
		               INPUT_INSTANCE.IsKeyOff(SDL_SCANCODE_LEFT);

	// 待機アニメ開始
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
		// ジャンプ終了アニメからのRUN開始
		if (mAnimState == PLAYERANIM_JUMPEND)
		{
			if (!mMeshComp->IsPlaying())
			{
				mMeshComp->PlayAnimation(mAnimTypes[PLAYERANIM_RUN], cAnimationSpeed);
				mAnimState = PLAYERANIM_RUN;
			}
		}

		// RUNアニメ開始
		if (mAnimState != PLAYERANIM_RUN)
		{
			mMeshComp->PlayAnimation(mAnimTypes[PLAYERANIM_RUN], cAnimationSpeed);
			mAnimState = PLAYERANIM_RUN;
		}
	}

}

// 背景AABBとのヒットめり込み解消 ( 当たった際にPhysicsWorldから呼ばれる ）
void PlayerActor::FixCollision(BoxCollider *hitPlayerBox, BoxCollider * hitBox)
{
	Vector3 fix;
	//足元当たり判定がヒットしたか？
	if (hitPlayerBox == mHitGroundBox && mJumpVec.z <= 0.0f)
	{
		mOnGroundChk = true;
		// ジャンプ中なら解除
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

	//壁とぶつかったとき
	AABB bgBox = hitBox->GetWorldBox();
	AABB playerBox = mHitBox->GetWorldBox();

	// めり込みを修正
	calcCollisionFixVec(playerBox, bgBox, fix);

	// 補正ベクトル分戻す
	mPosition += fix;

	// ジャンプアクション中に頭が壁に当たったとき
	if (hitPlayerBox == mHitHeadBox && mIsJump)
	{
		//ジャンプ上向きに行く方向を逆転させる
		mJumpVec = Vector3(0, 0, -1.0f);
		mPosition += mJumpVec; // もう頭上に当たらない様に離す
	}

	// 位置が変わったのでボックス再計算
	mHitBox->OnUpdateWorldTransform();

}
