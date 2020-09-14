#pragma once
#include "Game.h"

class Input
{
public:
	enum KEY_STATE
	{
		KEY_STATE_OFF = 0,	// ������Ă��Ȃ�
		KEY_STATE_PUSHDOWN,	// �����ꂽ�u��
		KEY_STATE_PRESSED,	// �����ꑱ���Ă���
		KEY_STATE_PULLUP	// �������u��
	};

	// �C���X�^���X
	static Input& InputInstance()
	{
		static Input InputInstance;
		return InputInstance;
	}

	~Input() {};

	// ���͏�Ԃ̍X�V
	void Update();

	// �L�[�̓��͏�Ԃ̎擾
	char GetInput(Uint8 _SDL_SCANCODE_key);

	// �L�[�������ꑱ�����Ă����Ԃ��H
	bool IsKeyPressed(Uint8 _SDL_SCANCODE_key);

	// �L�[�������ꂽ���H
	bool IsKeyPullUp(Uint8 _SDL_SCANCODE_key);

	// �L�[�������ꂽ���H
	bool IsKeyPushDown(Uint8 _SDL_SCANCODE_key);

	// �L�[��������Ă������H
	bool IsKeyOff(Uint8 _SDL_SCANCODE_key);

private:
	Input();

	char m_key[256];			// �S�L�[�̏�Ԏ擾�p
	char m_keyState[2][256];	// �L�[���[����/�ߋ��t���[��][�S�L�[�R�[�h]

	int m_nowKey, m_prevKey;	// ���t���[���A�ߋ��t���[��
};

#define INPUT_INSTANCE Input::InputInstance()