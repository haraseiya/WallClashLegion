#pragma once
#include "Game.h"

class PhysicsWorld
{
public:
	typedef enum {
		EnumEnemy,                // �G�L����
		EnumPlayer,				  // �v���[���[
		EnumBG,					  // �w�i�u���b�N
		EnumCoin,				  // �R�C��
		EnumHitCheck			  // �q�b�g�`�F�b�N�p�i�����Ԃ��Ȃ�)
	}EnumPhysicsType;

	PhysicsWorld();
	~PhysicsWorld();
	void AddBoxCollider(EnumPhysicsType type, class BoxCollider* box); // BoxCollider(AABB)�ǉ�
	void RemoveBoxCollider(class BoxCollider* box);                    // BoxCollider�폜
	void DebugShowBoxLists();                                          // �{�b�N�X���X�g�\���i�f�o�b�O�p)
	void Collision();                                                  // �R���W����
	void DebugShowBox();                                               // �f�o�b�O�p�{�b�N�X�\���i�������j
	void ToggleDebugMode() { mBoolDebugMode = !mBoolDebugMode; }       // �f�o�b�O���[�h

private:
	bool                              mBoolDebugMode ;                 // �f�o�b�O���[�h
	std::vector<class BoxCollider*>   mBGBoxs        ;                 // �w�i������f�[�^
	std::vector<class BoxCollider*>   mPlayerBoxs    ;                 // �v���[���[������f�[�^
	std::vector<class BoxCollider*>   mCoins         ;                 // �R�C��������f�[�^

	void PlayerAndBGTest(); // �v���[���[�ƕǂƂ̂����蔻��

};