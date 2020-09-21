#pragma once
#include "Game.h"

// ���̓N���X
class Input
{
public:

	enum KEY_STATE_ENUM             
	{
		KEY_STATE_OFF = 0,    // ������Ă��Ȃ�
		KEY_STATE_PUSHDOWN,   // ����
		KEY_STATE_PRESSED,    // �����ꑱ���Ă���
		KEY_STATE_PULLUP      // ������
	};

	static Input& InputInstance()                  // �C���X�^���X
	{
		static Input InputInstance;
		return InputInstance;
	}
	
	~Input() {};

	void Update();                                 // ���͏�Ԃ̍X�V
	char GetInput(Uint8 SDL_SCANCODE_key);         // ����L�[�̓��͏�Ԃ̎擾

	bool IsKeyPressed(Uint8 SDL_SCANCODE_key);     // ����L�[�������ꑱ�����Ă����Ԃ��H
	bool IsKeyPullup(Uint8 SDL_SCANCODE_key);      // ����L�[�������グ��ꂽ���H
	bool IsKeyPushdown(Uint8 SDL_SCANCODE_key);    // ����L�[�͉����ꑱ�����Ă��邩�H
	bool IsKeyOff(Uint8 SDL_SCANCODE_key);         // ����L�[�͉�����Ă��Ȃ����H

private:
	Input(); // �V���O���g��

	char mKey[256];                                // �S�L�[��Ԏ擾�p
	char mKeyState[2][256];                        // �L�[��� [����/�ߋ��t���[��][�S�L�[�R�[�h]

	int  mNowKey, mPrevKey;                        // ���t���[���A�ߋ��t���[���̃C���f�b�N�X

};

#define INPUT_INSTANCE Input::InputInstance()
