#include <typeinfo>
#include <algorithm>

#include "PhysicsWorld.h"
#include "Actor.h"
#include "playerActor.h"
#include "BoxCollider.h"
#include "Collision.h"

// PhysicsWorld�R���X�g���N�^
PhysicsWorld::PhysicsWorld()
	: mBoolDebugMode(false)
{
	// �����R���|�[�l���g�z��̊m��
	mBGBoxs.reserve(256);

	printf("PysicsWorld �쐬\n");

}

// �f�X�g���N�^
PhysicsWorld::~PhysicsWorld()
{
	printf("PysicsWorld �j��\n");
	mBGBoxs.clear();
}

// BoxCollider�̒ǉ�
void PhysicsWorld::AddBoxCollider(EnumPhysicsType type, BoxCollider *box)
{
	// �v���[���[�����蔻��ǉ�
	if (type == EnumPlayer)
	{
		mPlayerBoxs.push_back(box);
	}

	// �w�i�����蔻��ǉ�
	if (type == EnumBG)
	{
		mBGBoxs.push_back(box);
	}

}

// boxCollider�̍폜
void PhysicsWorld::RemoveBoxCollider(BoxCollider* box)
{
	// BackGround���ɂ���H
	auto iterBG = std::find(mBGBoxs.begin(), mBGBoxs.end(), box);
	if (iterBG != mBGBoxs.end())
	{
		mBGBoxs.erase(iterBG);
		return;
	}
}

// �f�o�b�O�p�@�{�b�N�X���X�g�\��
void PhysicsWorld::DebugShowBoxLists()
{

	if (mBGBoxs.size())
	{
		printf("\n-----------------PhysicsList--BGLists---------------\n");
		for (auto m : mBGBoxs)
		{
			Vector3 pos = m->GetOwner()->GetPosition();
			printf("%6d ", m->mGlobalID);
			printf("(% 7.2f,% 7.2f % 7.2f)-", pos.x, pos.y, pos.z);
			printf("[%p]\n", m->GetOwner());
		}
	}
}

void PhysicsWorld::Collision()
{
	// �v���[���[�Ɣw�i�Փ�
	PlayerAndBGTest();

}

void PhysicsWorld::DebugShowBox()
{

}

void PhysicsWorld::PlayerAndBGTest()
{
	//�w�i�ƃv���[���[�̏Փˌ��o
	for (auto p : mPlayerBoxs)
	{
		for (auto b : mBGBoxs)
		{
			BoxCollider *player = p;
			BoxCollider *box = b;
			if (Intersect(player->GetWorldBox(), b->GetWorldBox()))
			{
				//�v���[���[�̕ǂ߂荞�ݏC��������
				dynamic_cast<PlayerActor *>(player->GetOwner())->FixCollision( player, box );
			}
		}
	}

}

