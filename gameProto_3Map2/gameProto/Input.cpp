#include "Input.h"

Input::Input()
{
	mNowKey = 0;
	mPrevKey = 1;

	for (int i = 0; i < 256; i++)
	{
		mKey[i] = 0;
		mKeyState[mNowKey][i] = KEY_STATE_OFF;
		mKeyState[mPrevKey][i] = KEY_STATE_OFF;
	}
}

void Input::Update()
{
	// ���݂̃L�[��1�O�̃L�[�̏�Ԃ����ւ���  0���P�ɁA1��0��
	mNowKey ^= 1;
	mPrevKey = mNowKey ^ 1;

	//�L�[��Ԏ擾
	const Uint8* keys = SDL_GetKeyboardState(NULL);
	memcpy(mKeyState[mNowKey], keys, sizeof(char) * 256);

	for (int i = 0; i < 256; i++)
	{
		char nowInput  = mKeyState[mNowKey][i];
		char prevInput = mKeyState[mPrevKey][i];

		if (nowInput) //���݉�����Ă���
		{
			//�O�̃t���[����������Ă����H
			if (prevInput)
			{
				mKey[i] = KEY_STATE_PRESSED; // ��������ςȂ�
			}
			else {
				mKey[i] = KEY_STATE_PUSHDOWN;// �������ꂽ
			}

		}
		else // ���݃L�[�͉�����Ă��Ȃ�
		{
			// �O�̃t���[���ŉ�����Ă����H
			if (prevInput)
			{
				mKey[i] = KEY_STATE_PULLUP;
			}
			else {
				mKey[i] = KEY_STATE_OFF;
			}
		}
	}
}

char Input::GetInput(Uint8 SDL_SCANCODE_key)
{
	return mKey[SDL_SCANCODE_key];
}

bool Input::IsKeyPressed(Uint8 SDL_SCANCODE_key)
{
	return mKey[SDL_SCANCODE_key] == KEY_STATE_PRESSED;
}

bool Input::IsKeyPullup(Uint8 SDL_SCANCODE_key)
{
	return mKey[SDL_SCANCODE_key] == KEY_STATE_PULLUP;
}

bool Input::IsKeyPushdown(Uint8 SDL_SCANCODE_key)
{
	return mKey[SDL_SCANCODE_key] == KEY_STATE_PUSHDOWN;
}

bool Input::IsKeyOff(Uint8 SDL_SCANCODE_key)
{
	return mKey[SDL_SCANCODE_key] == KEY_STATE_OFF;
}
