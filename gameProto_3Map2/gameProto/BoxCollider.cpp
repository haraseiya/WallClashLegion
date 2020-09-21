#include "BoxCollider.h"
#include "Game.h"
#include "PhysicsWorld.h"
#include "Actor.h"

// BoxCollider�R���X�g���N�^
BoxCollider::BoxCollider(Actor * owner, PhysicsWorld::EnumPhysicsType physicsType, int updateOrder)
	:Component(owner, updateOrder)
	,mObjectBox(Vector3::Zero, Vector3::Zero)                    // �����l�͑傫���Ȃ��̃{�b�N�X��
	,mWorldBox(Vector3::Zero, Vector3::Zero)
	,mRotatable(true)
{
	GAMEINSTANCE.GetPhysics()->AddBoxCollider(physicsType, this); // �{�b�N�X�R���C�_�[��PhysicsWirld�ɓo�^
}

BoxCollider::~BoxCollider()
{
	printf("remove BoxCollider : [%5d] owner->( 0x%p )\n", GetID(), mOwner);
	GAMEINSTANCE.GetPhysics()->RemoveBoxCollider(this);
}

void BoxCollider::OnUpdateWorldTransform()
{
	// �I�u�W�F�N�g��Ԃ̃{�b�N�X�Ƀ��Z�b�g
	mWorldBox = mObjectBox;

	// �X�P�[�����O
	mWorldBox.mMin *= mOwner->GetScale();
	mWorldBox.mMax *= mOwner->GetScale();

	// ��]
	if (mRotatable)
	{
		mWorldBox.Rotate(mOwner->GetRotation());
	}
	//���s�ړ�
	mWorldBox.mMin += mOwner->GetPosition();
	mWorldBox.mMax += mOwner->GetPosition();
}
